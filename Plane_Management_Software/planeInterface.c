#include "planeSeating.h"
#include <stdio.h>
#include <stdbool.h>

// mattr - 71990f24 - assignment4 (refactor)

// class to setup the interface and create array of seats

void PlaneInterface(const char* oldFile, const char* newFile, PLANESEAT seatTracker[]) {

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
		printf("|Enter 6 for a list of all passengers (alphebetical)   |\n");				// still havent figured this out
		printf("|Enter 7 to confirm seating assignment                 |\n");
		printf("|Enter 0 to quit to main menu                          |\n");
		printf("|======================================================|\n\n");
		printf("Selection: ");
		scanf_s("%d", &inputNum);
		printf("\n");

		if (inputNum < 0 || inputNum > 7) {													// checks if input number is less than 0 or greater than 5
			printf("Invalid Input Value\n");
		}

		else {

			if (inputNum == 0) {															// Quit
				return 0;
			}

			else if (inputNum == 1) {														// Show alphabetical list of seats
				PrintPassengers(seatTracker);
			}

			else if (inputNum == 2) {														// Show number of empty seats
				int printNum = NumOfFREESeats(seatTracker);
				printf("Their are %d free seats.\n", printNum);
			}

			else if (inputNum == 3) {														// Show list of empty seats
				PrintFreeSeats(seatTracker);
			}

			else if (inputNum == 4) {														// Assign a customer to a seat assignment
				printf("Enter seat number: ");
				scanf_s("%d", &inputNum);
				if (inputNum > 12 || inputNum < 0 || seatTracker[inputNum - 1].seatStatus == FULL)
					printf("Error this seat is already full or doesnt exist. \n");
				else {
					AddPassenger(inputNum, seatTracker);
					printf("\nPassenger added successfully\n");
				}
			}

			else if (inputNum == 5) {														// Delete a seat assignment
				printf("Enter which passenger you wish to remove: ");
				scanf_s("%d", &inputNum);
				if (inputNum > 12 || inputNum < 0 || seatTracker[inputNum - 1].seatStatus == FREE)
					printf("Error this seat is already empty or doesnt exist. \n");
				else {
					RemovePassenger(inputNum, seatTracker);
					printf("\nPassenger removed successfully\n");
				}

			}

			else if (inputNum == 6) {
				printf("Do you want to sort by first or last name? (1 for first 2 for last): ");
				scanf_s("%d", &inputNum);
				if (inputNum != 1 && inputNum != 2)
					printf("Invalid input.\n");
				else {
					SortNames(&inputNum, seatTracker);
					printf("\nPassengers sorted successfully\n");
				}
			}

			else if (inputNum == 7) {
				char inputName[NAME_LENGTH] = { '\0' };
				printf("Enter first name of the passenger you wish to find: ");
				scanf_s("%s", inputName, NAME_LENGTH);
				if (FindPassenger(inputName, seatTracker))
					printf("\nPassengers found successfully\n");
			}

		}

	}


	return 0;

}