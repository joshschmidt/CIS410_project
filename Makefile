all: sim

sim: universe.h univese.cpp galaxy.h galaxy.cpp planet.cpp planet.h main.cpp
	icpc -g -std=c++11 -o sim universe.h univese.cpp galaxy.h galaxy.cpp planet.cpp planet.h main.cpp -Wall -Wextra -lcilkrts 
clean:
	rm sim
