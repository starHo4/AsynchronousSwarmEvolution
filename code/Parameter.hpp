#ifndef __Parameter__
#define __Parameter__

// The const. for simulation
#define FIELD_W 2048
#define FIELD_H 2048
#define FREE_TIMESTEPS 1000
#define MAX_TIMESTEPS 100000000 // 100 M

// Parameters for GA
#define GENE_MUTATION_RATE 0.005

// Parameters for an agent (common properties)
#define N_SEGMENT_SENSOR 12
#define EACH_SEGMENT_ANGLE 15 // degree

// Parameters for preys
#define N_INIT_PREYS 200
#define RADIUS_PREY 100
#define SPEED_PREY 1.0
#define ANGELESPEED_PREY 8.0 // degree
#define SAFETY_DIST 30.0
#define INIT_MEAN_ENERGY 2000.0
#define INIT_STD_ENERGY 100.0

// Parameters for predator
#define N_PREDATOR 5
#define RADIUS_PREDATOR 200
#define SPEED_PREDATOR 3.0
#define ANGLESPEED_PREDATOR 6.0 // degree
#define RADIUS_KILL 5.0
#define KILL_DELAY 10

// For Recurrent Neural Network
#define N_SENSOR N_SEGMENT_SENSOR
#define N_MEMORY 6
#define N_ACTUATOR 2

#endif