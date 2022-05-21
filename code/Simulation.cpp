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
    cout << "hoshi" << endl;
    Init_PlacePreys();
    cout << "hoshi" << endl;
    Init_PlacePredators();
    cout << "hoshi" << endl;
}
#pragma endregion

#pragma region PrivateMethods
void Simulation::Init_PlacePreys()
{
    SimulateFlock.Init();
    filesystem::path filePath = filesystem::current_path();
    filePath += FILEPATH_GENOME;
    filePath += "Preys/Chromosome.csv";
    Chromosome chr_preys(filePath.string(), false);
    for (int n = 0; n < N_INIT_PREYS; n++)
    {
        shared_ptr<Prey> p = make_shared<Prey>(mt, chr_preys, forID);
        SimulateFlock.AddNewPrey(p);
        forID++;
    }
}

void Simulation::Init_PlacePredators()
{
    Predators = vector<Predator>();
    filesystem::path filePath = filesystem::current_path();
    filePath += FILEPATH_GENOME;
    filePath += "Predators/Chromosome.csv";
    Chromosome chr_predator(filePath.string(), true);
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