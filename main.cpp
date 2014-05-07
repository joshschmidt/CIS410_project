#include "planet.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <cilk/cilk.h>


int main() {


	cilk_for(int i = 0; i < 1000; i++) {
		Planet p = Planet(i);
		p.printPlanet();
	}











}
