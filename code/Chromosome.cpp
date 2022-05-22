#include "Chromosome.hpp"

#pragma region Constructor
Chromosome::Chromosome(mt19937_64 &mt, const bool &_Fpredator)
{
    uniform_real_distribution<double> udd_pm1(-1, 1);

    // Init Genotype
    int stateSize = (_Fpredator) ? N_SENSOR + N_MEMORY + N_ACTUATOR : 3 * N_SENSOR + N_MEMORY + N_ACTUATOR;
    int size = (stateSize + 1 /* bias */) * N_MEMORY + (N_MEMORY + 1 /* bias */) * N_ACTUATOR;
    Genotype.resize(size);
    for (int i = 0; i < Genotype.size(); i++)
    {
        Genotype[i] = udd_pm1(mt);
    }
}

Chromosome::Chromosome(const string &fileName, const bool &_Fpredator)
{
    ifstream fin(fileName);
    if(!fin)
    {
        cout << "Cannot opening the file" << endl;
        abort();
    }

    int stateSize = (_Fpredator) ? N_SENSOR + N_MEMORY + N_ACTUATOR : N_SENSOR_LAYER_PREY * N_SENSOR + N_MEMORY + N_ACTUATOR;
    int size = (stateSize + 1 /* bias */) * N_MEMORY + (N_MEMORY + 1 /* bias */) * N_ACTUATOR;
    Genotype.resize(size);
    int i = 0;
    while(true)
    {
        fin >> Genotype[i];
        i++;
        if(fin.eof())
        {
            break;
        }
    }
    fin.close();

    if(i != size)
    {
        cout << "Size is not matching" << endl;
        abort();
    }

    F_Threat = false;
}
#pragma endregion

#pragma region PublicMethods
void Chromosome::InitTakeEnergyRate(const double &_val)
{
    TakeEnergyRate = _val;
}

void Chromosome::Mutation(mt19937_64 &mt)
{
    GeneMutation(mt);
    F_ThreatMutation(mt);
    TakeEnergyRate_Mutation(mt);
}
#pragma endregion

#pragma region PrivateMethods
void Chromosome::GeneMutation(mt19937_64 &mt)
{
    uniform_real_distribution<double> udd(0, 1);
    normal_distribution<double> nd_mutation(0, GENE_MUTATION_STD);
    for(int i=0; i<Genotype.size(); i++)
    {
        double rand = udd(mt);
        if(rand < GENE_MUTATION_RATE)
        {
            Genotype[i] += nd_mutation(mt);
            if(Genotype[i] > 1.0)
            {
                Genotype[i] = 1.0;
            }
            if(Genotype[i] < -1.0)
            {
                Genotype[i] = -1.0;
            }
        }
    }
}

void Chromosome::F_ThreatMutation(mt19937_64 &mt)
{
    uniform_real_distribution<double> udd(0, 1);
    double rand = udd(mt);
    if(rand < THREAT_MUTATION_RATE)
    {
        F_Threat = !F_Threat;
    }
}

void Chromosome::TakeEnergyRate_Mutation(mt19937_64 &mt)
{
    uniform_real_distribution<double> udd(0, 1);
    normal_distribution<double> nd_mutation(0, TAKEENERGYRATE_MUTATION_STD);
    double rand = udd(mt);
    if(rand < TAKEENERGYRATE_MUTATION_RATE)
    {
        TakeEnergyRate += nd_mutation(mt);
        if(TakeEnergyRate > 1.0)
        {
            TakeEnergyRate = 1.0;
        }
        if(TakeEnergyRate < 0.0)
        {
            TakeEnergyRate = 0.0;
        }
    }
}
#pragma endregion