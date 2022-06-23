#ifndef __DataManager__
#define __DataManager__

#include "Header.hpp"
#include "Flock.hpp"
#include "Predator.hpp"

class DataManager
{
    private:
    //* Private Methods *//
    void MakeDirectory(const string &_s, const int &_val);

    public:
    //* Constructor & Destructor *//
    DataManager(){}
    ~DataManager(){}

    //* Main body *//
    filesystem::path filePath;

    //* Public Methods *//
    void SaveFlock_Timestep(const double &_N, const int &_ts, const Flock &f, const vector<Predator> &_preds);
    void SaveFlock_N_Nthreat(const double &_N, const int &_ts, const Flock &f);
    void SaveFlock_FlockMeasures(const double &_N, const int &_ts, const Flock &f);
};

#endif