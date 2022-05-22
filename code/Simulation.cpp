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
    if (_N < 0 || _N > 10)
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
    PreFlocking();
    Init_PlacePredators();

    for (int t = 0; t < 1000; t++)
    {
        SimulateFlock.Flocking(mt);
        SimulateFlock.Update();
        SimulateFlock.CalcEnergy(mt);
        SimulateFlock.RemoveDeadPreys();
        SimulateFlock.CalcPreysDistances();

        PredatorsRun(mt);
        PredatorsUpdate();
        PredatorsPredation(mt);
        SimulateFlock.RemoveDeadPreys();
        SimulateFlock.CalcPredatorDistances(Predators);

        DManager.SaveFlock_Timestep(INIT_TAKEENERGYRATE, t, SimulateFlock, Predators);
    }
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

        for (int i = 0; i < SimulateFlock.flock.size(); i++)
        {
            ll pID = SimulateFlock.flock[i]->ID;
            SimulateFlock.MatDistance.insert(make_pair(make_pair(id, pID), 0));
            SimulateFlock.MatDiffPos.insert(make_pair(make_pair(id, pID), PVector(0, 0)));
        }
    }
}

void Simulation::PreFlocking()
{
    for (int t = 0; t < FREE_TIMESTEPS; t++)
    {
        SimulateFlock.PreFlocking(mt);
        SimulateFlock.Update();
        SimulateFlock.CalcPreysDistances();
    }
}

void Simulation::MainLoop()
{
    for (int t = 0; t < MAX_TIMESTEPS; t++)
    {
#pragma region InteractionPreys
        SimulateFlock.Flocking(mt);
        SimulateFlock.Update();
        SimulateFlock.CalcEnergy(mt);
        SimulateFlock.RemoveDeadPreys();
        SimulateFlock.CalcPreysDistances();
#pragma endregion InteractionPreys

#pragma region PredatorsAttack
        PredatorsRun(mt);
        PredatorsUpdate();
        PredatorsPredation(mt);
        SimulateFlock.RemoveDeadPreys();
        SimulateFlock.CalcPredatorDistances(Predators);
#pragma endregion PredatorsAttack
    }
}

void Simulation::PredatorsRun(mt19937_64 &mt)
{
    for (int i = 0; i < Predators.size(); i++)
    {
        Predators[i].Run(mt, SimulateFlock);
    }
}

void Simulation::PredatorsUpdate()
{
    for (int i = 0; i < Predators.size(); i++)
    {
        Predators[i].Update();
    }
}

void Simulation::PredatorsPredation(mt19937_64 &mt)
{
    for (int i = 0; i < Predators.size(); i++)
    {
        Predators[i].TryPredation(mt, SimulateFlock);
    }
}
#pragma endregion