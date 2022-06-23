#include "Flock.hpp"
#include "PreyThreat.hpp"

#pragma region PublicMethods
void Flock::Init()
{
    flock.clear();
    NumAlive = 0;
    NumThreat = 0;

    //* To Add processing!! *//
    MatDistance.clear();
    MatDiffPos.clear();
}

void Flock::AddOnlyNewPreys(shared_ptr<Prey> &a)
{
    flock.emplace_back(a);
    NumAlive++;

    // Add new distances and differences of Pos between "a" and others
    for (int i = 0; i < flock.size(); i++)
    {
        ll firstID = flock[i]->ID;
        ll secondID = a->ID;
        if (firstID != secondID)
        {
            if (firstID > secondID)
            {
                swap(firstID, secondID);
            }
            MatDistance.insert(make_pair(make_pair(firstID, secondID), 0));
            MatDiffPos.insert(make_pair(make_pair(firstID, secondID), PVector(0, 0)));
            CalcEachDistance(firstID, secondID);
        }
    }
    a.reset();
}

void Flock::AddNewPrey(shared_ptr<Prey> &a, vector<Predator> &_preds)
{
    flock.emplace_back(a);
    NumAlive++;
    if (a->F_threat)
    {
        NumThreat++;
    }

    // Add new distances and differences of Pos between "a" and others
    for (int i = 0; i < flock.size(); i++)
    {
        ll firstID = flock[i]->ID;
        ll secondID = a->ID;
        if (firstID != secondID)
        {
            if (firstID > secondID)
            {
                swap(firstID, secondID);
            }
            MatDistance.insert(make_pair(make_pair(firstID, secondID), 0));
            MatDiffPos.insert(make_pair(make_pair(firstID, secondID), PVector(0, 0)));
            CalcEachDistance(firstID, secondID);
        }
    }
    for (int i = 0; i < _preds.size(); i++)
    {
        ll firstID = _preds[i].ID;
        ll secondID = a->ID;
        if (firstID != secondID)
        {
            if (firstID > secondID)
            {
                swap(firstID, secondID);
            }
            MatDistance.insert(make_pair(make_pair(firstID, secondID), 0));
            MatDiffPos.insert(make_pair(make_pair(firstID, secondID), PVector(0, 0)));
            CalcEachPredDistance(firstID, secondID, _preds);
        }
    }
    a.reset();
}

void Flock::PreFlocking(mt19937_64 &mt)
{
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->Run(mt, *this);
    }
}

bool Flock::CheckExtinctOrExplosion(const double &_N, const int &_t, const int _iteNum)
{
    if (NumAlive <= 1)
    {
        cout << endl;
        cout << "Extinct!" << endl;
        cout << "Iteration : " << _iteNum << ", N : " << _N << ", t : " << _t << endl;
        cout << endl;
        return true;
        // exit(0);
    }
    if (NumAlive >= N_EXPLOSION)
    {
        cout << endl;
        cout << "Explosion!" << endl;
        cout << "Iteration : " << _iteNum << "N : " << _N << ", t : " << _t << endl;
        cout << endl;
        return true;
        // exit(0);
    }
    return false;
}

void Flock::Flocking(mt19937_64 &mt)
{
    for (int i = 0; i < flock.size(); i++)
    {
        if (flock[i]->F_live)
        {
            flock[i]->Run(mt, *this);
        }
    }
}

void Flock::Update()
{
    for (int i = 0; i < flock.size(); i++)
    {
        if (flock[i]->F_live)
        {
            flock[i]->Update();
        }
    }
}

void Flock::CalcEnergy(mt19937_64 &mt)
{
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->TakeFood(*this);
        if (flock[i]->F_threat)
        {
            flock[i]->RobEnergy(mt, *this);
        }
    }
}

void Flock::GenerateNewPreys(mt19937_64 &mt, ll &forID, vector<Predator> &_preds)
{
    vector<ll> parents = vector<ll>();
    vector<int> parents_index = vector<int>();
    vector<Chromosome> parents_chroms = vector<Chromosome>();
    for (int i = 0; i < flock.size(); i++)
    {
        if (flock[i]->Energy >= DIVISION_ENERGY)
        {
            flock[i]->F_live = false;
            parents.push_back(flock[i]->ID);
            parents_index.push_back(i);
            parents_chroms.push_back(flock[i]->Genome);
        }
    }
    for (int i = 0; i < parents.size(); i++)
    {
        Chromosome NewGenome1 = parents_chroms[i];
        PVector parentPos = flock[parents_index[i]]->getPos();
        NewGenome1.Mutation(mt);
        shared_ptr<Prey> p;
        if (NewGenome1.F_Threat)
        {
            p = make_shared<PreyThreat>(mt, NewGenome1, parentPos, forID);
        }
        else
        {
            p = make_shared<Prey>(mt, NewGenome1, parentPos, forID);
        }
        AddNewPrey(p, _preds);
        forID++;
        Chromosome NewGenome2 = parents_chroms[i];
        NewGenome2.Mutation(mt);
        if (NewGenome1.F_Threat)
        {
            p = make_shared<PreyThreat>(mt, NewGenome2, parentPos, forID);
        }
        else
        {
            p = make_shared<Prey>(mt, NewGenome2, parentPos, forID);
        }
        AddNewPrey(p, _preds);
        forID++;
    }

    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->Detect(*this);
    }
}

void Flock::RemoveDeadPreys()
{
    // Extract ID for removing dead preys
    vector<ll> rmvID = vector<ll>();
    int numRemoveThreat = 0;
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->Lifespan--;
        flock[i]->CheckDead();
        if (!flock[i]->F_live)
        {
            rmvID.push_back(flock[i]->ID);
            if (flock[i]->F_threat)
            {
                numRemoveThreat++;
            }
        }
    }

    // Remove dead Preys
    auto rmv = remove_if(flock.begin(), flock.end(), [](shared_ptr<Prey> &a)
                         { return !a->F_live; });
    flock.erase(rmv, flock.end());
    NumAlive = flock.size();
    NumThreat -= numRemoveThreat;

    // Remove distances related to the dead preys
    for (int i = 0; i < rmvID.size(); i++)
    {
        auto itr = MatDistance.begin();
        auto endItr = MatDistance.end();
        for (; itr != endItr;)
        {
            if (itr->first.first == rmvID[i] || itr->first.second == rmvID[i])
            {
                itr = MatDistance.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }

    // Remove Difference of Pos related to the dead preys
    for (int i = 0; i < rmvID.size(); i++)
    {
        auto itr = MatDiffPos.begin();
        auto endItr = MatDiffPos.end();
        for (; itr != endItr;)
        {
            if (itr->first.first == rmvID[i] || itr->first.second == rmvID[i])
            {
                itr = MatDiffPos.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }
}

void Flock::CalcMeasures()
{
    // Density
    Density = 0;
    for (int i = 0; i < flock.size(); i++)
    {
        if (flock[i]->F_live)
        {
            Density += flock[i]->NearbyCount;
        }
    }
    Density /= NumAlive;

    // Dispersion
    Dispersion = 0;
    for (int i = 0; i < flock.size(); i++)
    {
        if (flock[i]->F_live)
        {
            Dispersion += flock[i]->NearestDistance;
        }
    }
    Dispersion /= NumAlive;
}

void Flock::CalcPreysDistances()
{
    if (MatDistance.size() != MatDiffPos.size())
    {
        cout << "MatDistance.size is not matching MatDiffPos.size" << endl;
        abort();
    }
    auto begin = MatDistance.begin();
    auto end = MatDistance.end();
    for (auto itr = begin; itr != end; itr++)
    {
        ll firstID = itr->first.first;
        ll secondID = itr->first.second;
        if (firstID >= 0)
        {
            CalcEachDistance(firstID, secondID);
        }
    }
}

void Flock::CalcPredatorDistances(const vector<Predator> &_preds)
{
    if (MatDistance.size() != MatDiffPos.size())
    {
        cout << "MatDistance.size is not matching MatDiffPos.size" << endl;
        abort();
    }
    auto begin = MatDistance.begin();
    auto end = MatDistance.end();
    for (auto itr = begin; itr != end; itr++)
    {
        ll firstID = itr->first.first;
        ll secondID = itr->first.second;
        if (firstID < 0)
        {
            CalcEachPredDistance(firstID, secondID, _preds);
        }
    }
}

void Flock::CalcEachDistance(const ll &_firstID, const ll &_secondID)
{
    auto itr_firstPrey = find_if(flock.begin(), flock.end(), [&_firstID](shared_ptr<Prey> &a)
                                 { return a->ID == _firstID; });
    auto itr_secondPrey = find_if(flock.begin(), flock.end(), [&_secondID](shared_ptr<Prey> &a)
                                  { return a->ID == _secondID; });
    if (itr_firstPrey == flock.end() || itr_secondPrey == flock.end())
    {
        cout << _firstID << ", " << _secondID << endl;
        cout << "ID is not found in CalcEachDistance" << endl;
        abort();
    }

    shared_ptr<Prey> firstPrey = *itr_firstPrey;
    shared_ptr<Prey> secondPrey = *itr_secondPrey;
    PVector diff = secondPrey->getPos().TroidalShortest(firstPrey->getPos(), FIELD_W, FIELD_H);
    double dist = diff.Norm();
    MatDistance[make_pair(_firstID, _secondID)] = dist;
    MatDiffPos[make_pair(_firstID, _secondID)] = diff;
}

void Flock::CalcEachPredDistance(const ll &_predID, const ll &_preyID, const vector<Predator> &_preds)
{
    auto itr_Pred = find_if(_preds.begin(), _preds.end(), [&_predID](Predator p)
                            { return p.ID == _predID; });
    auto itr_Prey = find_if(flock.begin(), flock.end(), [&_preyID](shared_ptr<Prey> &a)
                            { return a->ID == _preyID; });
    if (itr_Pred == _preds.end() || itr_Prey == flock.end())
    {
        cout << "ID is not found in CalcEachPredDistance" << endl;
        abort();
    }

    Predator pred = *itr_Pred;
    shared_ptr<Prey> prey = *itr_Prey;
    PVector diff = prey->getPos().TroidalShortest(pred.getPos(), FIELD_W, FIELD_H);
    double dist = diff.Norm();
    MatDistance[make_pair(_predID, _preyID)] = dist;
    MatDiffPos[make_pair(_predID, _preyID)] = diff;
}
#pragma endregion