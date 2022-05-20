#ifndef __Predator__
#define __Predator__

#include "Header.hpp"
#include "Agent.hpp"
#include "Flock.hpp"

class Predator : public Agent
{
private:
    //* Private Variables *//
    double Radius_kill;
    // Kill Delay;
    int Delay;

    //* Private Methods *//
    virtual void Detect(const Flock &f);
    void TryPredation(mt19937_64 &mt, Flock &f);

public:
    //* Constructors *//
    Predator() {}
    Predator(mt19937_64 &mt, const Chromosome _chr);
    //* Destructor *//
    virtual ~Predator() {}

    //* Public Methods *//
    virtual void Run(mt19937_64 &mt, Flock &f);
};

#endif