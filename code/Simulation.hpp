#ifndef __Simulation__
#define __Simulation__

#include "Header.hpp"
#include "Flock.hpp"
#include "Predator.hpp"

class Simulation
{
private:
    //* Private Variables *//
    // Global random generator
    mt19937_64 mt;
    int generalSeed;

    // Flock of preys
    Flock SimulateFlock;
    // Flock of predators
    vector<Predator> Predators;

    //* Priavte Methods *//
    // Initialization
    void Init_PlacePreys();
    void Init_PlacePredators();
    // Free running for preys
    void PreFlocking();

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