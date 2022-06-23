#ifndef __Parameter__
#define __Parameter__

// The const. for simulation
#define FIELD_W 512
#define FIELD_H 512
#define FREE_TIMESTEPS 250
#define MAX_TIMESTEPS 1000000 // 1 M

// Parameters for GA
#define GENE_MUTATION_RATE 0.01
#define GENE_MUTATION_STD 0.05
#define THREAT_MUTATION_RATE 0.01
#define TAKEENERGYRATE_MUTATION_RATE 0.01
#define TAKEENERGYRATE_MUTATION_STD 0.001

// Parameters for an agent (common properties)
#define N_SEGMENT_SENSOR 12
#define EACH_SEGMENT_ANGLE 15 // degree

// Parameters for preys
#define N_INIT_PREYS 50
#define N_EXTINCT 1
#define N_EXPLOSION 200
#define INIT_MEAN_ENERGY 2000.0
#define INIT_STD_ENERGY 200.0
#define DIVISION_ENERGY 4000.0
#define FOOD_SUMENERGY 100.0
#define RADIUS_PREY 100
#define SPEED_PREY 1.0
#define ANGLESPEED_PREY 8.0 // degree
#define SAFETY_DIST 30.0
#define N_SENSOR_LAYER_PREY 3
#define LIFESPAN 3000

// Parameters for predator
#define N_PREDATOR 1
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