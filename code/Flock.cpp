#include "Flock.hpp"

#pragma region PublicMethods
void Flock::Init()
{
    flock.clear();
    NumAlive = 0;

    //* To Add processing!! *//
}

void Flock::AddAgent(shared_ptr<Prey> &a)
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
    auto rmv = remove_if(flock.begin(), flock.end(), [](shared_ptr<Prey> &a)
                         { return !a->F_live; });
    flock.erase(rmv, flock.end());
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