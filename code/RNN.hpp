#ifndef __RNN_hoshi__
#define __RNN_hoshi__

#include "Header.hpp"
#include "Neuron.hpp"

class RNN
{
private:
    //* Private Variables *//
    int NSensor;
    int NHidden;
    int NOutput;

    //* Private Methods *//
    void ClearNeuronValues();

public:
    //* Constructors *//
    RNN() {}
    RNN(const vector<double> &_genotype, const int &_NSensor, const int &_NHidden, const int &_NOutput);
    //* Destructor *//
    ~RNN() {}

    //* Main body *//
    vector<int> State;
    vector<int> NewState;
    vector<Neuron> HiddenNeurons;
    vector<Neuron> OutputNeurons;

    //* Public Methods *//
    void ClearSensor();
    void FeedForward();
};

#endif