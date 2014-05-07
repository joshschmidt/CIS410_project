all: sim

sim: planet.cpp planet.h main.cpp
	icpc -g -std=c++11 -o sim planet.cpp planet.h main.cpp -Wall -Wextra -lcilkrts 
clean:
	rm sim
