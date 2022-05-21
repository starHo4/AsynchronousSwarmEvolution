#ifndef __Prey__
#define __Prey__

#include "Header.hpp"
#include "Agent.hpp"
#include "Flock.hpp"

class Prey : public Agent
{
private:

protected:
    //* Protected Methods *//
    virtual void Detect(const Flock &f);
    void CheckDead();

public:
    //* Constructors *//
    Prey() {}
    Prey(mt19937_64 &mt, const Chromosome &_chr, const long long &_id);
    //* Destructor *//
    virtual ~Prey() {}

    //* Public Variables *//
    // Energy
    double Energy;
    // For Measures
    int NearbyCount;
    int NearestDistance;

    //* Public Methods *//
    virtual void Run(mt19937_64 &mt, Flock &f);
};

#endif