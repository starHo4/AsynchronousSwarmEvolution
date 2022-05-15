#ifndef __Chromosome__
#define __Chromosome__

#include "Header.hpp"

class Chromosome
{
private:
    //* Private Methods *//
    void GeneMutation(mt19937_64 &mt);

public:
    //* Constructors *//
    Chromosome() {}
    Chromosome(mt19937_64 &mt, const bool &_Fpredator);
    Chromosome(const string &fileName);
    //* Destructor *//
    ~Chromosome() {}

    vector<double> genotype;

    //* Public Methods *//
    void Mutation(mt19937_64 &mt);
};

#endif