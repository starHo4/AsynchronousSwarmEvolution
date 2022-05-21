#ifndef __Agent__
#define __Agent__

#include "Header.hpp"
#include "Chromosome.hpp"
#include "RNN.hpp"

class Flock;

class Agent
{
private:
    //* Private Methods *//
    void Borders();

protected:
    //* Protected Variables *//
    // Physical states //
    PVector Pos;
    PVector Vel;
    double Angle;
    // Action state
    int Action;
    // Physical capasity of agents //
    double Radius;
    double VisionAngle;
    double Speed;
    double AngleSpeed;
    // Brain
    RNN Brain;

    //* Protected Methods *//
    virtual void Detect(const Flock &f);
    void TakeAction(const int &a);

public:
    //* Constructors & Destructor *//
    Agent() {}
    Agent(mt19937_64 &mt, const Chromosome &_chr, const long long &_id);
    virtual ~Agent() {}

    //* Public Variables *//
    long long ID;
    bool F_live;
    bool F_predator;

    //* Public Methods *//
    virtual void Run(mt19937_64 &mt, Flock &f);
    void Update();

    //* Getter *//
    PVector getPos() const { return Pos; };
    PVector getVel() const { return Vel; };
    double getAngle() const { return Angle; };
    int getAction() const { return Action; };
};

#endif