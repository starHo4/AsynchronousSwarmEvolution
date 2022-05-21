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
}

void Flock::PreFlocking(mt19937_64 &mt)
{
}

void Flock::Flocking(mt19937_64 &mt)
{
}

void Flock::Update()
{
}

void Flock::RemoveDeadPreys()
{
    // Extract ID for removing dead preys
    vector<long long> rmvID = vector<long long>();
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
        auto rmv_MD = remove_if(MatDistance.begin(), MatDistance.end(), [&rmvID, &i](pair<long long, long long> &p)
                                { return p.first == rmvID[i]; });
        MatDistance.erase(rmv_MD, MatDistance.end());
    }

    // Remove Difference of Pos related to the dead preys
    for (int i = 0; i < rmvID.size(); i++)
    {
        auto rmv_MDP = remove_if(MatDiffPos.begin(), MatDiffPos.end(), [&rmvID, &i](pair<long long, long long> &p)
                                 { return p.first == rmvID[i]; });
        MatDiffPos.erase(rmv_MDP, MatDiffPos.end());
    }
}

void Flock::CalcDistance()
{
    // for(int i=0; i<flock.size(); i++)
    // {
    //     for(int j=i; j<flock.size(); j++)
    //     {
    //         if(i == j)
    //         {

    //         }
    //     }
    // }
}
#pragma endregion