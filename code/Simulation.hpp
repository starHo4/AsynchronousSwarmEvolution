#ifndef __Simulation__
#define __Simulation__

#include "Header.hpp"
#include "Flock.hpp"

class Simulation
{
private:
    //* Private Variables *//
    // Global random generator
    mt19937_64 mt;
    int generalSeed;

    // Flock of preys
    Flock SimulateFlock;

    //* Priavte Methods *//
    // Initialization
    void Initialize();
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