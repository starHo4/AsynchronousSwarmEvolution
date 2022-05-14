#ifndef __Simulation__
#define __Simulation__

#include "Header.hpp"
#include  "Flock.hpp"

class Simulation
{
private:
    //* Private Variables *//
    // Global random generator
    mt19937_64 mt;
    int generalSeed;

    //* Priavte Methods *//
    // Initialization
    void Initialize();

    // Flock of preys
    Flock SimulateFlock;

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