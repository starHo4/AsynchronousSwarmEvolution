#ifndef __Flock__
#define __Flock__

#include "Header.hpp"
#include "Agent.hpp"
#include "Chromosome.hpp"
#include "PVector.hpp"

class Flock
{
    private:
    public:
    //* Constructor & Destructor *//
    Flock(){}
    ~Flock(){}

    //* Main body *//
    vector<shared_ptr<Agent>> flock;    // To modify

    //* Public Variables *//
    int NumAlive;
    // Distance Matrix
    vector<vector<double>> MatDistance;
    vector<vector<PVector>> MatDiffPos;

    //* Public Methods *//
    // void AddAgent(shared_ptr<Agent> &a);
    void PreFlocking(mt19937_64 &mt);
    void Flocking(mt19937_64 &mt);
    void Update();
    void CalcDistance();
};

#endif