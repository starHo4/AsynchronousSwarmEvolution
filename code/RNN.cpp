#include "RNN.hpp"

#pragma region Constructor
RNN::RNN(const vector<double> &_genotype, const int &_NSensor, const int &_NHidden, const int &_NOutput)
{
    NSensor = _NSensor;
    NHidden = _NHidden;
    NOutput = _NOutput;

    // Init State
    State = vector<int>(NSensor + NHidden + NOutput, 0);
    NewState = vector<int>(NSensor + NHidden + NOutput, 0);

    // Init Hidden and Output Neurons
    HiddenNeurons.resize(NHidden);
    OutputNeurons.resize(NOutput);
    int index = 0;
    int size = NSensor + NHidden + NOutput + 1 /* bias */;
    for (int i = 0; i < HiddenNeurons.size(); i++)
    {
        HiddenNeurons[i] = Neuron(_genotype, index, size);
        index += size;
    }
    size = NHidden + 1;
    for (int i = 0; i < OutputNeurons.size(); i++)
    {
        OutputNeurons[i] = Neuron(_genotype, index, size);
        index += size;
    }
}
#pragma endregion

#pragma region PublicMethods
void RNN::ClearSensor()
{
    for (int i = 0; i < NSensor; i++)
    {
        State[i] = 0;
    }
}

void RNN::FeedForward()
{
    for (int i = 0; i < HiddenNeurons.size(); i++)
    {
        for (int j = 0; j < HiddenNeurons[i].Weights.size() - 1; j++)
        {
            HiddenNeurons[i].NetValue += HiddenNeurons[i].Weights[j] * State[j];
        }
        HiddenNeurons[i].NetValue += HiddenNeurons[i].Weights[HiddenNeurons[i].Weights.size() - 1]; /* bias */
        HiddenNeurons[i].F();
        NewState[NSensor + i] = HiddenNeurons[i].OutValue;
    }

    for (int i = 0; i < OutputNeurons.size(); i++)
    {
        for (int j = 0; j < HiddenNeurons.size(); j++)
        {
            OutputNeurons[i].NetValue += OutputNeurons[i].Weights[j] * NewState[NSensor + j];
        }
        OutputNeurons[i].NetValue += OutputNeurons[i].Weights[OutputNeurons[i].Weights.size() - 1]; /* bias */
        OutputNeurons[i].F();
        NewState[NSensor + NHidden + i] = OutputNeurons[i].OutValue;
    }
    ClearNeuronValues();

    // Update States from NewState & Clear NewState
    for (int i = NSensor; i < State.size(); i++)
    {
        State[i] = NewState[i];
        NewState[i] = 0;
    }
}
#pragma endregion

#pragma region PrivateMethods
void RNN::ClearNeuronValues()
{
    for (int i = 0; i < HiddenNeurons.size(); i++)
    {
        HiddenNeurons[i].NetValue = 0;
        HiddenNeurons[i].OutValue = 0;
    }

    for (int i = 0; i < OutputNeurons.size(); i++)
    {
        OutputNeurons[i].NetValue = 0;
        OutputNeurons[i].OutValue = 0;
    }
}
#pragma endregion