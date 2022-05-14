OBJS = main.o
CC = g++
STD = -std=c++17

all : main

main : $(OBJS)
	$(CC) $(OBJS) $(STD) -g -o ../test
main.o : main.cpp
	$(CC) $(STD) -g -c main.cpp
clean :
	rm *.o