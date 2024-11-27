#define _CRT_SECURE_NO_WARNINGS

#include "planeSeating.h"
#include <stdio.h>
#include <stdlib.h>

// mattr - 71990f24 - assignment4 (refactor)

/*

Modeling a(single) airline / airplane reservation system

o Specifications : 3.00 / 8.00 (The program is producing incorrect results
or the following issues were noted : )

--File I / O incomplete or not working
--Listing of guests in alphabetical order incomplete or not working
--Datafile must exist to run program(unable to test any functionality)

o Readability + Design : 6.00 / 8.00 (The code has some elements of good design and layout,
but is lacking in some respects or the following issues were noted.)

--All variables must have descriptive names

o Reusability : 2.00 / 4.00 (Some parts of the code could be reused in other programs
or the following issues were noted : )

—Having hard coded(magic) values in function limits reusability
—Globally scoped variables should be avoided unless absolutely required

o Documentation : 4.00 / 4.00 (The documentation is well written and clearly explains what the code is accomplishing and how.)

*/

// main implementation for plane data management

// param 1: "listOfPassengers.txt", param 2: "newList.txt"

int main(void) {

	const char* originalFileName = "listOfPassengers.txt";					// saved the file names as const chars
	const char* newFileName = "newList.txt";
	FILE* originalFile;														// made temp files to create them
	FILE* newFile;

	originalFile = fopen(originalFileName, "w");							// creates and adds new files
	if (originalFile == NULL) {
		fprintf(stderr, "system was unable to create file\n");
		exit(EXIT_FAILURE);
	}

	newFile = fopen(newFileName, "w");										// creates and adds new files
	if (originalFile == NULL) {												// (also error checks)
		fprintf(stderr, "system was unable to create file\n");
		exit(EXIT_FAILURE);
	}

	fclose(originalFile);
	fclose(newFile);

	PLANESEAT seatTracker[PLANE_SIZE];										// no longer a global variable
	DefaultSeats(seatTracker);

	ReadPassengersFromFile(originalFileName, seatTracker);

	int returnValue = PlaneInterface(originalFileName, newFileName, seatTracker);

	WritePassengersToFile(newFileName, seatTracker);

	return 0;
}