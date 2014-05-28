all: population.o galaxy.o planet.o universe.o main.o sim

population.o: population.cpp population.h 
	icpc -g -std=c++11 -c population.cpp -Wall -Wextra -lcilkrts

galaxy.o: galaxy.cpp galaxy.h
	icpc -g -std=c++11 -c galaxy.cpp -Wall -Wextra -lcilkrts

planet.o: planet.cpp planet.h
	icpc -g -std=c++11 -c planet.cpp -Wall -Wextra -lcilkrts

universe.o: universe.cpp universe.h
	icpc -g -std=c++11 -c universe.cpp -Wall -Wextra -lcilkrts

main.o: main.cpp
	icpc -g -std=c++11 -c main.cpp -Wall -Wextra -lcilkrts

sim:    main.o universe.o planet.o galaxy.o population.o
	icpc -g -std=c++11 galaxy.o universe.o planet.o population.o main.o -o sim

clean:
	rm sim *.o
