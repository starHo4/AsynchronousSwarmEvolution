#include "Flock.hpp"

#pragma region PublicMethods
void Flock::AddAgent(shared_ptr<Prey> &a)
{
    flock.emplace_back(move(a));
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