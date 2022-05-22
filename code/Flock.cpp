#include "Flock.hpp"

#pragma region PublicMethods
void Flock::Init()
{
    flock.clear();
    NumAlive = 0;

    //* To Add processing!! *//
    MatDistance.clear();
    MatDiffPos.clear();
}

void Flock::AddNewPrey(shared_ptr<Prey> &a)
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

void Flock::PreFlocking(mt19937_64 &mt)
{
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->Run(mt, *this);
    }
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
        if (flock[i]->F_threat)
        {
            flock[i]->RobEnergy(mt, *this);
        }
    }
}

void Flock::RemoveDeadPreys()
{
    // Extract ID for removing dead preys
    vector<ll> rmvID = vector<ll>();
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i]->CheckDead();
        if (!flock[i]->F_live)
        {
            rmvID.push_back(flock[i]->ID);
        }
    }

    // Remove dead Preys
    auto rmv = remove_if(flock.begin(), flock.end(), [](shared_ptr<Prey> &a)
                         { return !a->F_live; });
    flock.erase(rmv, flock.end());
    NumAlive = flock.size();

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
        cout << "ID is not found in CalcEachDistance" << endl;
        abort();
    }

    shared_ptr<Prey> firstPrey = *itr_firstPrey;
    shared_ptr<Prey> secondPrey = *itr_secondPrey;
    PVector diff = firstPrey->getPos().TroidalShortest(secondPrey->getPos(), FIELD_W, FIELD_H);
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
    PVector diff = pred.getPos().TroidalShortest(prey->getPos(), FIELD_W, FIELD_H);
    double dist = diff.Norm();
    MatDistance[make_pair(_predID, _preyID)] = dist;
    MatDiffPos[make_pair(_predID, _preyID)] = diff;
}
#pragma endregion