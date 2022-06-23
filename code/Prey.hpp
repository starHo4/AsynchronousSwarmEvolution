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
    bool JudgeThreat(const ll &_detectID);

public:
    //* Constructors *//
    Prey() {}
    Prey(mt19937_64 &mt, const Chromosome &_chr, const ll &_id);
    Prey(mt19937_64 &mt, const Chromosome &_chr, const PVector &_parentPos, const ll &_id);
    //* Destructor *//
    virtual ~Prey() {}

    //* Public Variables *//
    // Energy
    double Energy;
    // Lifespan
    int Lifespan;
    // For Threat
    vector<ll> ListOfThreat;
    // For Measures
    int NearbyCount;
    int NearestDistance;

    //* Public Methods *//
    virtual void Run(mt19937_64 &mt, Flock &f);
    void Detect(const Flock &f);
    virtual void RobEnergy(mt19937_64 &mt, Flock &f);
    void TakeFood(const Flock &f);
    void CheckDead();
};

#endif