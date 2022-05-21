#ifndef __Flock__
#define __Flock__

#include "Header.hpp"
#include "Chromosome.hpp"
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
    MatrixDistance MatDistance;
    MatrixDiffPos MatDiffPos;

    //* Public Methods *//
    void Init();
    void AddNewPrey(shared_ptr<Prey> &a);
    void PreFlocking(mt19937_64 &mt);
    void Flocking(mt19937_64 &mt);
    void Update();
    void RemoveDeadPreys();
    void CalcEachDistance(const ll &_firstID, const ll &_secondID);
};

#endif