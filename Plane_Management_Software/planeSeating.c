#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "planeSeating.h"
#include <stdio.h>

// mattr - 71990f24 - assignment4

// source file for plane seating struct

PLANESEAT createPassenger(char FirstName[], char LastName[], int SeatNumber) {

	PLANESEAT newSeat;

	newSeat.seatStatus = FREE;

	strncpy(newSeat.firstName, FirstName, NAME_LENGTH);										// saves first and last name
	strncpy(newSeat.lastName, LastName, NAME_LENGTH);

	newSeat.seatNumber = SeatNumber;														// saves seat number

	if (SeatNumber > 0 && SeatNumber <= PLANE_SIZE) {										// makes sure seat is inbounds

		if (seatTracker[SeatNumber - 1].seatStatus == FREE) {								// checks if seat is empty
			seatTracker[SeatNumber - 1] = newSeat;											// assign the new passenger to the seat
			newSeat.seatStatus = FULL;
		}
		else {
			printf("Seat %d is already occupied!\n", SeatNumber);
		}
	}
	else {
		printf("Invalid seat number: %d\n", SeatNumber);
	}


	return newSeat;

}

void DefaultSeats() {
	for (int i = 0; i < PLANE_SIZE; i++) {
		seatTracker[i].seatNumber = i + 1;												
		seatTracker[i].seatStatus = FREE;													// Initially all seats are available
		strncpy(seatTracker[i].firstName, "N/A", NAME_LENGTH);								// saves first and last name
		strncpy(seatTracker[i].lastName, "N/A", NAME_LENGTH);
	}
}

void WritePassengersToFile(const char* filename) {

	FILE* newFile = fopen(filename, "w");													// opens file to save data to

	if (newFile == NULL) {
		perror("Error opening original file");											    // error check
		exit(EXIT_FAILURE);
	}

	else {

		int temp = 0, n = 0;
		char f[NAME_LENGTH] = { '\0' },
			l[NAME_LENGTH] = { '\0' };
		char* s;

		for (int x = 0; x < PLANE_SIZE; x++) {

			strncpy(f, seatTracker[x].firstName, NAME_LENGTH);								 // save first name in f an dlast name in l
			strncpy(l, seatTracker[x].lastName, NAME_LENGTH);
			n = seatTracker[x].seatNumber;													 // save seat number as n

			if (seatTracker[x].seatStatus == FULL)											 // checks if seat is full or not
				s = "FULL";
			else
				s = "FREE";

			fprintf(newFile, "%d %s %s %s", n, s, l, f);									 // print all values to the file
			fprintf(newFile, "\n");
		}

		fclose(newFile);

	}
}

void ReadPassengersFromFile(const char* filename) {

	FILE* ogFile = fopen(filename, "r");														// opens file to read from
		
	if (ogFile) {
		printf("File reading successful\n");

		if (ogFile == NULL) {
			perror("Error opening original file");											    // error check
			exit(EXIT_FAILURE);
		}

		int currentSeat = 0;

		char f[NAME_LENGTH] = { '\0' },
			l[NAME_LENGTH] = { '\0' }, s[STATUS_SIZE] = { '\0' };								// temp variables for information
		int n = 0;

		while (fscanf(ogFile, "%d %s %s %s",													// saves valuse to temp variables before sending them to array
			&n, &s, &l, &f) == 4) {

			strncpy(seatTracker[currentSeat].firstName, f, NAME_LENGTH);						// saves first and last name
			strncpy(seatTracker[currentSeat].lastName, l, NAME_LENGTH);
			seatTracker[currentSeat].seatNumber = n;
			if (strcmp(s, "FULL") == 0)															// checks if value is FREE or FULL
				seatTracker[currentSeat].seatStatus = FULL;
			else
				seatTracker[currentSeat].seatStatus = FREE;

			currentSeat++;																		// this will read from old file

		}

		fclose(ogFile);

	}

	else {

		printf("No file detected, new file listOfPassengers.txt created\n");

		FILE* ogFile = fopen(filename, "w");

		if (ogFile == NULL) {
			perror("Error opening original file");											    // error check
			exit(EXIT_FAILURE);
		}

		fclose(ogFile);

	}

}

void PrintPassengers() {

	int currentSeat = 0;

	while (currentSeat < PLANE_SIZE) {															// checks if seat is full and if it is it prints it
		if (seatTracker[currentSeat].seatStatus == FULL)
			printf("Passenger ID: Seat #%d, %s, %s\n", seatTracker[currentSeat].seatNumber,
				seatTracker[currentSeat].lastName, seatTracker[currentSeat].firstName);
		currentSeat++;
	}

}

int NumOfFREESeats() {

	int currentSeat = 0;

	int freeSeats = 0;

	while (currentSeat < PLANE_SIZE) {													
		if (seatTracker[currentSeat].seatStatus == FREE)										// if seat staus is free ad 1 to free seat
			freeSeats++;
		currentSeat++;
	}

	if (freeSeats <= 0) {
		return 0;
	}

	return freeSeats;
}

void PrintFreeSeats() {

	int currentSeat = 0;

	while (currentSeat < PLANE_SIZE) {															// checks if seat is full and if it is NOT it prints it
		if (seatTracker[currentSeat].seatStatus == FREE)
			printf("Passenger ID: Seat #%d, %s, %s\n", seatTracker[currentSeat].seatNumber,
				seatTracker[currentSeat].lastName, seatTracker[currentSeat].firstName);
		currentSeat++;
	}

}

void RemovePassenger(int inputNum) {

	int x = inputNum - 1;

	if (seatTracker[x].seatStatus == FULL) {
		seatTracker[x].seatStatus = FREE;														// makes seat FREE

		strncpy(seatTracker[x].firstName, "N/A", NAME_LENGTH);									// puts N/A for first/last name
		strncpy(seatTracker[x].lastName, "N/A", NAME_LENGTH);

	}
}

void AddPassenger(int inputNum) {

	char* f = malloc(NAME_LENGTH * sizeof(char));												// allocate memory for first/last name
	char* l = malloc(NAME_LENGTH * sizeof(char));

	if (f == NULL || l == NULL) {
		printf("Memory allocation failed!\n");													// check if memory allocated properly
	}

	else {

		int x = inputNum - 1;

		if (seatTracker[x].seatStatus == FREE) {
			seatTracker[x].seatStatus = FULL;													// makes seat FULL

				printf("Enter first name: ");
				scanf_s("%25s", f, NAME_LENGTH);												// name inputs

				printf("Enter last name: ");
				scanf_s("%25s", l, NAME_LENGTH);

			strncpy(seatTracker[x].firstName, f, NAME_LENGTH);									// puts N/A for first/last name
			strncpy(seatTracker[x].lastName, l, NAME_LENGTH);

		}

	}

	free(l);
	free(f);

}


