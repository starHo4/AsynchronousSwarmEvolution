#ifndef __Simulation__
#define __Simulation__

#include "Header.hpp"
#include "DataManager.hpp"
#include "Flock.hpp"
#include "Predator.hpp"

class Simulation
{
private:
    //* Private Variables *//
    // Global random generator
    mt19937_64 mt;
    int generalSeed;

    //* For Paramter Search *//
    double INIT_TAKEENERGYRATE;

    // For Iteration of ID
    long long forID;
    // Flock of preys
    Flock SimulateFlock;
    // Flock of predators
    vector<Predator> Predators;

    DataManager DManager;

    //* Priavte Methods *//
    // Initialization
    void Init_PlacePreys();
    void Init_PlacePredators();
    // Free running for preys
    void PreFlocking();
    // Main Loop
    void MainLoop();
    // Predator's Update
    void PredatorsRun(mt19937_64 &mt);
    void PredatorsUpdate();
    void PredatorsPredation(mt19937_64 &mt);

public:
    //* Constructor & Destructor *//
    Simulation() {}
    Simulation(const int &_N);
    ~Simulation() {}

    //* Public Methods *//
    void RunSimulation();
    void TestSimulation();
};

#endif