all: sim

sim: population.h population.cpp universe.h universe.cpp galaxy.h galaxy.cpp planet.cpp planet.h event.h event.cpp galaxyManager.h galaxyManager.cpp main.cpp
	icpc -g -std=c++11 -o sim population.h population.cpp universe.h universe.cpp galaxy.h galaxy.cpp planet.cpp event.h event.cpp planet.h galaxyManager.h galaxyManager.cpp main.cpp -Wall -Wextra -lcilkrts 
clean:
	rm sim
