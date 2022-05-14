#include "Simulation.hpp"

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        int _N = atoi(argv[1]);

        Simulation simulation(_N);
        // simulation.RunSimulation();
        simulation.TestSimulation();
    }
}