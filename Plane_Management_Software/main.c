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
	int planeNum = 0, flightNum = 0, exitNum = -1;
	const char* originalFileName = "flightData.txt";						// saved the file names as const chars
	const char* newFileName = "flightDataUpdated.txt";
	FILE* originalFile;														// made temp files to create them
	FILE* newFile;

	originalFile = fopen(originalFileName, "r");							// creates and adds new file
	if (originalFile == NULL) {
		originalFile = fopen(originalFileName, "w");
	}
	fclose(originalFile);

	if (originalFile == NULL) {
		fprintf(stderr, "system was unable to create file\n");
		exit(EXIT_FAILURE);
	}

	newFile = fopen(newFileName, "w");										// creates and adds new files
	if (newFile == NULL) {													// (also error checks)
		fprintf(stderr, "system was unable to create file\n");
		exit(EXIT_FAILURE);
	}

	fclose(originalFile);
	fclose(newFile);

	PLANESEAT seatTracker[PLANE_SIZE];										// no longer a global variable
	DefaultSeats(seatTracker);

	ReadPassengersFromFile(originalFileName, seatTracker);

	do {
		printf("\n|======================================================|\n");
		printf("|This is the main menu for managing flight assignments |\n");
		printf("|======================================================|\n");
		printf("|Enter 1 for the first plane's assignments             |\n");
		printf("|Enter 2 for the second plane's assignments            |\n");
		printf("|Enter 0 to exit the program and save the assignments  |\n");
		printf("|======================================================|\n");
		printf("Selection: ");
		scanf_s("%d", &exitNum);
		printf("\n");

		if (exitNum > 2 || exitNum < 0) {
			printf("Invalid input\n");
		}

		else if (exitNum == 1) {
			planeNum = 1;
			printf("|======================================================|\n");
			printf("|Enter 1 for flight 102                                |\n");
			printf("|Enter 2 for flight 311                                |\n");
			printf("|Enter 0 to cancel                                     |\n");
			printf("|======================================================|\n");
			printf("Selection: ");
			scanf_s("%d", &exitNum);
			printf("\n");

			if (exitNum == 1) {
				flightNum = 102;
				PlaneInterface(originalFileName, newFileName, seatTracker, planeNum, flightNum);
			}
			else if (exitNum == 2) {
				flightNum = 311;
				PlaneInterface(originalFileName, newFileName, seatTracker, planeNum, flightNum);
			}
			else
				printf("Invalid input\n");
		}

		else if (exitNum == 2) {
			planeNum = 2;
			printf("|======================================================|\n");
			printf("|Enter 1 for flight 444                                |\n");
			printf("|Enter 2 for flight 519                                |\n");
			printf("|Enter 0 to cancel                                     |\n");
			printf("|======================================================|\n");
			printf("Selection: ");
			scanf_s("%d", &exitNum);
			printf("\n");

			if (exitNum == 1) {
				flightNum = 444;
				PlaneInterface(originalFileName, newFileName, seatTracker, planeNum, flightNum);
			}
			else if (exitNum == 2) {
				flightNum = 519;
				PlaneInterface(originalFileName, newFileName, seatTracker, planeNum, flightNum);
			}
			else
				printf("Invalid input\n");
		}

	} while (exitNum != 0);

	WritePassengersToFile(newFileName, seatTracker);

	return 0;
}