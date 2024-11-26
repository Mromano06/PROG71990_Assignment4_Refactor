#include "main.h"
#include "planeSeating.h"
#include <stdio.h>

// mattr - 71990f24 - assignment4

// main class for question 2

// param 1: "listOfPassengers.txt", param 2: "newList.txt"

int main(int argc, char** argv) {

	if (argc < 2) {															// checks if both files were sent
		fprintf(stderr, "usage: missing command line paramater\n");
		exit(EXIT_FAILURE);
	}

	DefaultSeats();

	ReadPassengersFromFile(argv[1]);

	int returnValue = PlaneInterface(argv[1], argv[2]);

	WritePassengersToFile(argv[2]);

	return returnValue;
}