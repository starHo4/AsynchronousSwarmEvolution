OBJS = main.o Simulation.o
CC = g++
STD = -std=c++17

all : main

main : $(OBJS)
	$(CC) $(OBJS) $(STD) -g -o ../test
main.o : main.cpp
	$(CC) $(STD) -g -c main.cpp
Simulation.o : Simulation.cpp
	$(CC) $(STD) -g -c Simulation.cpp
clean :
	rm *.o