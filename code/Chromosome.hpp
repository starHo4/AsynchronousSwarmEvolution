#ifndef __Chromosome__
#define __Chromosome__

#include "Header.hpp"

class Chromosome
{
private:
    //* Private Methods *//
    void GeneMutation(mt19937_64 &mt);
    void F_ThreatMutation(mt19937_64 &mt);
    void TakeEnergyRate_Mutation(mt19937_64 &mt);

public:
    //* Constructors *//
    Chromosome() {}
    Chromosome(mt19937_64 &mt, const bool &_Fpredator);
    Chromosome(const string &fileName, const bool &_Fpredator);
    //* Destructor *//
    ~Chromosome() {}

    //* Main body *//
    // For RNN
    vector<double> Genotype;
    // For Threat
    bool F_Threat;
    double TakeEnergyRate;  // Initial value is parameter

    //* Public Methods *//
    void InitTakeEnergyRate(const double &_val);
    void Mutation(mt19937_64 &mt);
};

#endif