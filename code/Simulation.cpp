#include "Simulation.hpp"

#pragma region Constructors
Simulation::Simulation(const int &_N)
{
    generalSeed = _N;
    mt.seed(_N);
    uniform_int_distribution<int> uid_Seed(0, INT32_MAX);
    int NewRandomSeed = uid_Seed(mt);
    mt.seed(NewRandomSeed);
}
#pragma endregion

#pragma region PublicMethods
void Simulation::RunSimulation()
{
    // Initialization
    Initialize();

    // Simulate for free running
    PreFlocking();

    // 
}

void Simulation::TestSimulation()
{
    Initialize();
    cout << "HIROYUKI HOSHI" << endl;
    cout << (long long)10000000000 << endl;
}
#pragma endregion

#pragma region PrivateMethods
void Simulation::Initialize()
{
}

void Simulation::PreFlocking()
{
}
#pragma endregion