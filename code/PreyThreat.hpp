#ifndef __PreyThreat__
#define __PreyThreat__

#include "Header.hpp"
#include "Prey.hpp"
#include "Flock.hpp"

class PreyThreat : public Prey
{
private:
    //* Private Methods *//
    void RobEnergy(mt19937_64 &mt, Flock &f);

public:
    //* Constructors *//
    PreyThreat() {}
    PreyThreat(mt19937_64 &mt, Chromosome &_chr, const long long &_id);
    //* Destructor *//
    ~PreyThreat() {}

    //* Public Variables *//
    double TakeEnergyRate;

    //* Public Methods *//
    virtual void Run(mt19937_64 &mt, Flock &f);
};

#endif