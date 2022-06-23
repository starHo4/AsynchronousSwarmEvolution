#include "Simulation.hpp"

#pragma region Constructors
Simulation::Simulation(const int &_N)
{
    generalSeed = _N;
    mt.seed(generalSeed);
    uniform_int_distribution<int> uid_Seed(0, INT32_MAX);
    int NewRandomSeed = uid_Seed(mt);
    mt.seed(NewRandomSeed);

    INIT_TAKEENERGYRATE = (double)_N / 100;
    if (_N < 0 || _N > 100)
    {
        cout << "Please set a seed as a range between 0 to 10" << endl;
        abort();
    }

    forID = 1;
}
#pragma endregion

#pragma region PublicMethods
void Simulation::RunSimulation()
{
    SurviveNum = 0;
    for (int i = 0; i < 100; i++)
    {
        // Initialization
        Init_PlacePreys();

        // Simulate for free running
        PreFlocking();

        // Place Predators into the environment
        Init_PlacePredators();

        // Main Loop
        MainLoop(i);
        SurviveNum++;
    }
    filesystem::path filePath = filesystem::current_path();
    filePath += FILEPATH;
    filePath += "N" + to_string((int)(INIT_TAKEENERGYRATE * 1000)) + "/";
    filePath += "SurviveNum.txt";
    ofstream ofs(filePath.string(), ios::app);
    ofs << SurviveNum << endl;
    ofs.close();
}

void Simulation::TestSimulation()
{
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
    for (int n = 0; n < N_INIT_PREYS; n++)
    {
        shared_ptr<Prey> p = make_shared<Prey>(mt, chr_preys, forID);
        SimulateFlock.AddOnlyNewPreys(p);
        forID++;
    }
    SimulateFlock.CalcPreysDistances();
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
    SimulateFlock.CalcPredatorDistances(Predators);
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

void Simulation::MainLoop(const int _iteNum)
{
    for (int t = 0; t < MAX_TIMESTEPS; t++)
    {
#pragma region CheckExtinctOrExplosion
        if (SimulateFlock.CheckExtinctOrExplosion(INIT_TAKEENERGYRATE, t, _iteNum))
        {
            return;
        }
#pragma endregion CheckExtinctOrExplosion

#pragma region InteractionPreys
        SimulateFlock.Flocking(mt);                           // Determine the action
        SimulateFlock.Update();                               // Move the direction which is determined in the previous processing
        SimulateFlock.CalcEnergy(mt);                         // TakeFood() and RobEnergy() (RobEnergy() is processing PreyThreat only)
        SimulateFlock.GenerateNewPreys(mt, forID, Predators); // Generate new preys with division of parent preys whose energy is beyond threshold
        SimulateFlock.RemoveDeadPreys();                      // Lifespan is decreasing and the dead preys are removed; the dead prey is the prey whose energy or lifespan is below 0.
        SimulateFlock.CalcPreysDistances();
#pragma endregion InteractionPreys

#pragma region PredatorsAttack
        PredatorsRun(mt);
        PredatorsUpdate();
        PredatorsPredation(mt);
        SimulateFlock.RemoveDeadPreys();
        SimulateFlock.CalcPredatorDistances(Predators);
#pragma endregion PredatorsAttack

#pragma region SaveData
        if (SAVEMOVIE)
        {
            DManager.SaveFlock_Timestep(INIT_TAKEENERGYRATE, t, SimulateFlock, Predators);
        }

        if (t == 0 || t % SAVEDATA_INTERVAL == SAVEDATA_INTERVAL - 1)
        {
            SimulateFlock.CalcMeasures();
            DManager.SaveFlock_N_Nthreat(INIT_TAKEENERGYRATE, t, SimulateFlock);
            DManager.SaveFlock_FlockMeasures(INIT_TAKEENERGYRATE, t, SimulateFlock);
        }
#pragma endregion SaveData

#pragma region OutputResult
        if (t == 0 || t % 10000 == 9999)
        {
            cout << "Seed : " << INIT_TAKEENERGYRATE << ", timestep : " << t << endl;
            cout << "N : " << SimulateFlock.NumAlive << ", N_threat : " << SimulateFlock.NumThreat << endl;
            cout << "Density : " << SimulateFlock.Density << ", Dispersion : " << SimulateFlock.Dispersion << endl;
        }
#pragma endregion OutputResult
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