#include "Simulation.hpp"

#pragma region Constructors
Simulation::Simulation(const int &_N)
{
    generalSeed = _N;
    mt.seed(_N);
    uniform_int_distribution<int> uid_Seed(0, INT32_MAX);
    int NewRandomSeed = uid_Seed(mt);
    mt.seed(NewRandomSeed);

    forID = 0;
}
#pragma endregion

#pragma region PublicMethods
void Simulation::RunSimulation()
{
    // Initialization
    Init_PlacePreys();

    // Simulate for free running
    PreFlocking();

    // Place Predators into the environment
    Init_PlacePredators();

    // Main Loop
}

void Simulation::TestSimulation()
{
    vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto rmv = remove_if(v1.begin(), v1.end(), [](int i)
                         { return i % 2 == 1; });
    v1.erase(rmv, v1.end());

    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}
#pragma endregion

#pragma region PrivateMethods
void Simulation::Init_PlacePreys()
{
    SimulateFlock.Init();
    Chromosome chr_preys/* fileName */;
    for(int n=0; n<N_INIT_PREYS; n++)
    {
        shared_ptr<Prey> p = make_shared<Prey>(mt, chr_preys, forID);
        SimulateFlock.AddNewPrey(p);
        forID++;
    }
}

void Simulation::Init_PlacePredators()
{
    Predators = vector<Predator>();
    Chromosome chr_predator/*fileName*/;
    for (int n = 0; n < N_PREDATOR; n++)
    {
        long long id = -(n + 1);
        Predator p(mt, chr_predator, id);
        Predators.emplace_back(move(p));
    }
}

void Simulation::PreFlocking()
{
}
#pragma endregion