#ifndef __Agent__
#define __Agent__

#include "Header.hpp"
// #include "RNN.hpp"
#include "PVector.hpp"

class Flock;

class Agent
{
    private:
    //* Private Methods *//
    void Borders();

    protected:
    //* Protected Variables *//
    // Common properties //
    int ID;
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
    // RNN Brain;
};

#endif