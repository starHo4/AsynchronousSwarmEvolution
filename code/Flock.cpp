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
    flock.emplace_back(move(a));
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
}

void Flock::PreFlocking(mt19937_64 &mt)
{
}

void Flock::Flocking(mt19937_64 &mt)
{
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

void Flock::RemoveDeadPreys()
{
    // Extract ID for removing dead preys
    vector<ll> rmvID = vector<ll>();
    for (int i = 0; i < flock.size(); i++)
    {
        if (!flock[i]->F_live)
        {
            rmvID.push_back(flock[i]->ID);
        }
    }

    // Remove dead Preys
    auto rmv = remove_if(flock.begin(), flock.end(), [](shared_ptr<Prey> &a)
                         { return !a->F_live; });
    flock.erase(rmv, flock.end());

    // Remove distances related to the dead preys
    for (int i = 0; i < rmvID.size(); i++)
    {

        auto itr = MatDistance.begin();
        auto endItr = MatDistance.end();
        for (; itr != endItr;)
        {
            if (itr->first.first == rmvID[i])
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
            if (itr->first.first == rmvID[i])
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

void Flock::CalcAllDistances()
{
    if(MatDistance.size() != MatDiffPos.size())
    {
        abort();
    }
    auto begin = MatDistance.begin();
    auto end = MatDistance.end();
    for(auto itr = begin; itr != end; itr++)
    {
        ll firstID = itr->first.first;
        ll secondID = itr->first.second;
        CalcEachDistance(firstID, secondID);
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
        abort();
    }

    shared_ptr<Prey> firstPrey = *itr_firstPrey;
    shared_ptr<Prey> secondPrey = *itr_secondPrey;
    PVector diff = firstPrey->getPos().TroidalShortest(secondPrey->getPos(), FIELD_W, FIELD_H);
    double dist = diff.Norm();
    MatDistance[make_pair(_firstID, _secondID)] = dist;
    MatDiffPos[make_pair(_firstID, _secondID)] = diff;
}
#pragma endregion