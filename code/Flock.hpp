#ifndef __Flock__
#define __Flock__

#include "Header.hpp"
#include "Chromosome.hpp"
#include "PVector.hpp"
#include "Prey.hpp"

class Prey;

class Flock
{
private:
public:
    //* Constructor & Destructor *//
    Flock() {}
    ~Flock() {}

    //* Main body *//
    vector<shared_ptr<Prey>> flock; // To modify

    //* Public Variables *//
    int NumAlive;
    // Distance Matrix
    vector<vector<double>> MatDistance;
    vector<vector<PVector>> MatDiffPos;

    //* Public Methods *//
    void AddAgent(shared_ptr<Prey> &a);
    void PreFlocking(mt19937_64 &mt);
    void Flocking(mt19937_64 &mt);
    void Update();
    void CalcDistance();
};

#endif