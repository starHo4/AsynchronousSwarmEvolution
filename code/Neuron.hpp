#ifndef __Neuron__
#define __Neuron__

#include "Header.hpp"

class Neuron
{
    private:
    public:
    //* Constructor & Destructor *//
    Neuron(){}
    Neuron(const vector<double> &_genotype, const int &_startIindex, const int &_NOfPreLayer);
    ~Neuron(){}

    //* Main body *//
    int OutValue;
    double NetValue;
    vector<double> Weights;

    //* Public Methods *//
    void F();
};

#endif