#include "Neuron.hpp"

#pragma region Constructor
Neuron::Neuron(const vector<double> &_genotype, const int &_startIndex, const int &_NOfPreLayer)
{
    // Init
    OutValue = 0;
    NetValue = 0;

    // Init Weights
    Weights.resize(_NOfPreLayer);
    for(int i=0; i<Weights.size(); i++)
    {
        Weights[i] = _genotype[_startIndex + i];
    }
}
#pragma endregion

#pragma region PublicMethods
void Neuron::F()
{
    int o = (NetValue > 0) ? 1 : 0;
    OutValue = o;
}
#pragma endregion