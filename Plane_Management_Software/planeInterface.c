#include "main.h"
#include "planeSeating.h"
#include <stdio.h>

// mattr - 71990f24 - assignment4

// class to setup the interface and create array of seats

int PlaneInterface(const char* oldFile, const char* newFile) {

	int inputNum = -1;

	while (inputNum != 0) {

		inputNum = -1;

		printf("\n|======================================================|\n");
		printf("|This is the interface for managing seating assignments|\n");
		printf("|======================================================|\n");
		printf("|Enter 1 for a list of all passengers                  |\n");
		printf("|Enter 2 for the number of empty seats                 |\n");
		printf("|Enter 3 for a list of all empty seats                 |\n");
		printf("|Enter 4 to assign a new passenger to this assignment  |\n");
		printf("|Enter 5 to delete passenger from this assignment      |\n");
		printf("|Enter 0 to quit                                       |\n");
		printf("|======================================================|\n\n");
		printf("Selection: ");
		scanf_s("%d", &inputNum);
		printf("\n");

		if (inputNum < 0 || inputNum > 5) {													// checks if input number is less than 0 or greater than 5
			printf("Invalid Input Value\n");
		}

		else {

			if (inputNum == 0) {															// Quit
				return 0;
			}

			else if (inputNum == 1) {														// Show alphabetical list of seats
				PrintPassengers();
			}

			else if (inputNum == 2) {														// Show number of empty seats
				int printNum = NumOfFREESeats();
				printf("Their are %d free seats.\n", printNum);
			}

			else if (inputNum == 3) {														// Show list of empty seats
				PrintFreeSeats();
			}

			else if (inputNum == 4) {														// Assign a customer to a seat assignment
				printf("Enter seat number: ");
				scanf_s("%d", &inputNum);
				if (inputNum > 12 || inputNum < 0 || seatTracker[inputNum - 1].seatStatus == FULL)
					printf("Error this seat is already full or doesnt exist. \n");
				else {
					AddPassenger(inputNum);
					printf("\nPassenger added successfully\n");
				}
			}

			else if (inputNum == 5) {														// Delete a seat assignment
				printf("Enter which passenger you wish to remove: ");
				scanf_s("%d", &inputNum);
				if (inputNum > 12 || inputNum < 0 || seatTracker[inputNum - 1].seatStatus == FREE)
					printf("Error this seat is already empty or doesnt exist. \n");
				else {
					RemovePassenger(inputNum);
					printf("\nPassenger removed successfully\n");
				}

			}

		}

	}


	return 0;

}