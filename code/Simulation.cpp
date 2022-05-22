#include "Simulation.hpp"

#pragma region Constructors
Simulation::Simulation(const int &_N)
{
    generalSeed = 0;
    mt.seed(generalSeed);
    uniform_int_distribution<int> uid_Seed(0, INT32_MAX);
    int NewRandomSeed = uid_Seed(mt);
    mt.seed(NewRandomSeed);

    INIT_TAKEENERGYRATE = (double)_N / 10;
    if(_N < 0 || _N > 10)
    {
        abort();
    }

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
    MainLoop();
}

void Simulation::TestSimulation()
{
    Init_PlacePreys();
    Init_PlacePredators();
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
    chr_preys.InitTakeEnergyRate(INIT_TAKEENERGYRATE);
    cout << chr_preys.TakeEnergyRate << endl;
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
    SimulateFlock.PreFlocking(mt);
}

void Simulation::MainLoop()
{
    for (int t = 0; t < MAX_TIMESTEPS; t++)
    {
    }
}
#pragma endregion