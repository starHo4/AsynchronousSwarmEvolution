#ifndef __Flock__
#define __Flock__

#include "Header.hpp"
#include "Chromosome.hpp"
#include "Predator.hpp"
#include "Prey.hpp"

class Predator;
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
    int NumThreat;
    // Distance Matrix
    MatrixDistance MatDistance;
    MatrixDiffPos MatDiffPos;

    // Measures
    double Density;
    double Dispersion;

    //* Public Methods *//
    void Init();
    void AddOnlyNewPreys(shared_ptr<Prey> &a);
    void AddNewPrey(shared_ptr<Prey> &a, vector<Predator> &_preds);
    void PreFlocking(mt19937_64 &mt);
    // Interaction between preys
    bool CheckExtinctOrExplosion(const double &_N, const int &_t, const int _iteNum);
    void Flocking(mt19937_64 &mt);
    void Update();
    void CalcEnergy(mt19937_64 &mt);
    void GenerateNewPreys(mt19937_64 &mt, ll &forID, vector<Predator> &_preds);
    void RemoveDeadPreys();
    void CalcMeasures();
    void CalcPreysDistances();
    void CalcPredatorDistances(const vector<Predator> &_preds);
    void CalcEachDistance(const ll &_firstID, const ll &_secondID);
    void CalcEachPredDistance(const ll &_predID, const ll &_preyID, const vector<Predator> &_preds);
};

#endif