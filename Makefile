all: population.o galaxy.o planet.o universe.o main.o sim

population.o: Population/population.cpp Population/population.h 
	icpc -g -std=c++11 -c Population/population.cpp -Wall -Wextra -lcilkrts

galaxyManager.o: Galaxy/galaxyManager.cpp Galaxy/galaxyManager.h
	icpc -g -std=c++11 -c Galaxy/galaxyManager.cpp -Wall -Wextra -lcilkrts

galaxy.o: Galaxy/galaxy.cpp Galaxy/galaxy.h
	icpc -g -std=c++11 -c Galaxy/galaxy.cpp -Wall -Wextra -lcilkrts

planet.o: Planet/planet.cpp Planet/planet.h
	icpc -g -std=c++11 -c Planet/planet.cpp -Wall -Wextra -lcilkrts

universe.o: Universe/universe.cpp Universe/universe.h
	icpc -g -std=c++11 -c universe.cpp -Wall -Wextra -lcilkrts

event.o: Event/event.cpp Event/event.h
	icpc -g -std=c++11 -c Event/event.cpp -Wall -Wextra -lcilkrts

main.o: main.cpp
	icpc -g -std=c++11 -c main.cpp -Wall -Wextra -lcilkrts

sim:    main.o universe.o planet.o galaxy.o population.o event.o galaxyManager.o
	icpc -g -std=c++11 galaxy.o universe.o planet.o population.o galaxyManager.o event.o main.o -o sim

clean:
	rm sim *.o
