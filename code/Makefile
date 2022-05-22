OBJS = main.o Agent.o Chromosome.o Flock.o Neuron.o Predator.o Prey.o PreyThreat.o PVector.o RNN.o Simulation.o
CC = g++
STD = -std=c++17

all : main

main : $(OBJS)
	$(CC) $(OBJS) $(STD) -g -o ../test
main.o : main.cpp
	$(CC) $(STD) -g -c main.cpp
Agent.o : Agent.cpp
	$(CC) $(STD) -g -c Agent.cpp
Chromosome.o : Chromosome.cpp
	$(CC) $(STD) -g -c Chromosome.cpp
Flock.o : Flock.cpp
	$(CC) $(STD) -g -c Flock.cpp
Neuron.o : Neuron.cpp
	$(CC) $(STD) -g -c Neuron.cpp
Predator.o : Predator.cpp
	$(CC) $(STD) -g -c Predator.cpp
Prey.o : Prey.cpp
	$(CC) $(STD) -g -c Prey.cpp
PreyThreat.o : PreyThreat.cpp
	$(CC) $(STD) -g -c PreyThreat.cpp
PVector.o : PVector.cpp
	$(CC) $(STD) -g -c PVector.cpp
RNN.o : RNN.cpp
	$(CC) $(STD) -g -c RNN.cpp
Simulation.o : Simulation.cpp
	$(CC) $(STD) -g -c Simulation.cpp
clean :
	rm *.o