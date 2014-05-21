all: sim

sim: population.h population.cpp universe.h universe.cpp galaxy.h galaxy.cpp planet.cpp planet.h main.cpp
	icpc -g -std=c++11 -o sim population.h population.cpp universe.h universe.cpp galaxy.h galaxy.cpp planet.cpp planet.h main.cpp -Wall -Wextra -lcilkrts 
clean:
	rm sim
