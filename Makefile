all: population.o galaxy.o galaxyManager.o  planet.o universe.o universeManager.o event.o  main.o sim

population.o: Population/population.cpp Population/population.h 
	icpc -g -std=c++11 -c Population/population.cpp -Wall -Wextra -lcilkrts

galaxyManager.o: Galaxy/galaxyManager.cpp Galaxy/galaxyManager.h
	icpc -g -std=c++11 -c Galaxy/galaxyManager.cpp -Wall -Wextra -lcilkrts

galaxy.o: Galaxy/galaxy.cpp Galaxy/galaxy.h
	icpc -g -std=c++11 -c Galaxy/galaxy.cpp -Wall -Wextra -lcilkrts

planet.o: Planet/planet.cpp Planet/planet.h
	icpc -g -std=c++11 -c Planet/planet.cpp -Wall -Wextra -lcilkrts

universe.o: Universe/universe.cpp Universe/universe.h
	icpc -g -std=c++11 -c Universe/universe.cpp -Wall -Wextra -lcilkrts

universeManager.o: Universe/universeManager.cpp Universe/universeManager.h
	icpc -g -std=c++11 -c Universe/universeManager.cpp -Wall -Wextra -lcilkrts

event.o: Event/event.cpp Event/event.h
	icpc -g -std=c++11 -c Event/event.cpp -Wall -Wextra -lcilkrts

main.o: main.cpp
	icpc -g -std=c++11 -c main.cpp -Wall -Wextra -lcilkrts

test.o: test.cpp
	icpc -g -std=c++11 -c test.cpp -Wall -Wextra -lcilkrts

simtest: test.o universe.o planet.o galaxy.o population.o event.o galaxyManager.o universeManager.o
	icpc -g -std=c++11 galaxy.o universe.o planet.o population.o galaxyManager.o universeManager.o event.o test.o -o simtest

sim:    main.o universe.o planet.o galaxy.o population.o event.o galaxyManager.o universeManager.o
	icpc -g -std=c++11 galaxy.o universe.o planet.o population.o galaxyManager.o universeManager.o event.o main.o -o sim -L/home/users/mknowle2/sdl/lib -lSDL2 -lSDL2_ttf

clean:
	rm simtest sim *.o
