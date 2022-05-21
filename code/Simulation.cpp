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
    map<ll, double> m1;
    m1.insert(make_pair(100, 0.01));
    m1.insert(make_pair(1000, 0.001));
    m1.insert(make_pair(1, 1));
    m1.insert(make_pair(10, 0.1));

    auto itr = m1.begin();
    auto endItr = m1.end();

    for (; itr != endItr;)
    {
        if(itr->first <= 10)
        {
            itr = m1.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    itr = m1.begin();
    for(; itr != endItr; itr++)
    {
        cout << "key = " << itr->first << " ";
        cout << "value = " << itr->second << endl;
    }
}
#pragma endregion

#pragma region PrivateMethods
void Simulation::Init_PlacePreys()
{
    SimulateFlock.Init();
    string fileName = FILEPATH_GENOME;
    fileName += "Preys/Chromosome.csv";
    Chromosome chr_preys(fileName);
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
    string fileName = FILEPATH_GENOME;
    fileName += "Predators/Chromosome.csv";
    Chromosome chr_predator(fileName);
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