#define _CRT_SECURE_NO_WARNINGS

#include "planeSeating.h"
#include <stdio.h>
#include <stdlib.h>

// mattr - 71990f24 - assignment4 (refactor)

// source file for plane seating struct

PLANESEAT createPassenger(char FirstName[], char LastName[], int SeatNumber) {
	PLANESEAT newSeat;

	newSeat.seatStatus = FREE;

	strncpy(newSeat.firstName, FirstName, NAME_LENGTH);										// saves first and last name
	strncpy(newSeat.lastName, LastName, NAME_LENGTH);

	newSeat.seatNumber = SeatNumber;														// saves seat number


	return newSeat;

}

void DefaultSeats(PLANESEAT seatTracker[]) {
	for (int i = 0; i < PLANE_SIZE; i++) {
		seatTracker[i].seatNumber = i + 1;												
		seatTracker[i].seatStatus = FREE;															// Initially all seats are available
		strncpy(seatTracker[i].firstName, "N/A", NAME_LENGTH);										// saves first and last name
		strncpy(seatTracker[i].lastName, "N/A", NAME_LENGTH);
	}
}

void GetFlightData(const char* oldFileName, int flightSelection, PLANESEAT seatTracker[]) {
	int correctFlight = 0;
	int flight = flightSelection;
	char flightName[NAME_LENGTH];
	sprintf(flightName, "%d", flight);

	FILE* ogFile = fopen(oldFileName, "r");															// Open the file for reading
	if (ogFile == NULL) {
		perror("Error opening original file");
		exit(EXIT_FAILURE);
	}

	char line[200] = { '\0' };
	int temp = 0, seatNum = 0, currentSeat = 0;
	char firstName[NAME_LENGTH] = { '\0' },
		lastName[NAME_LENGTH] = { '\0' };
	char seat[STATUS_SIZE] = { '\0' };

	while (fgets(line, sizeof(line), ogFile) != NULL && currentSeat <= PLANE_SIZE) {				// reads the line
		line
		if (strcmp(line, flightName) == 0) {														// giving me issues with saving line as num\n instead of num
			correctFlight = 1;
			continue;
		}
			if (correctFlight) {
				while (fscanf(ogFile, "%d %s %s %s", &seatNum,										// if it find the right flight then it scans the structs
					seat, lastName, firstName) == 4) {
					strncpy(seatTracker[currentSeat].firstName, firstName, NAME_LENGTH);
					strncpy(seatTracker[currentSeat].lastName, lastName, NAME_LENGTH);
					seatTracker[currentSeat].seatNumber = seatNum;
					if (strcmp(seat, "FULL") == 0)
						seatTracker[currentSeat].seatStatus = FULL;
					else
						seatTracker[currentSeat].seatStatus = FREE;


					currentSeat++;

					if (currentSeat >= PLANE_SIZE)
						break;
				}
			}
	}

	fclose(ogFile);
}


void WritePassengersToFile(const char* filename, PLANESEAT seatTracker[]) {
	FILE* newFile = fopen(filename, "w");														// opens file to save data to

	if (newFile == NULL) {
		perror("Error opening original file");												    // error check
		exit(EXIT_FAILURE);
	}

	else {

		int temp = 0, seatNum = 0;
		char firstName[NAME_LENGTH] = { '\0' },
			lastName[NAME_LENGTH] = { '\0' };
		char* seat;

		for (int x = 0; x < PLANE_SIZE; x++) {

			strncpy(firstName, seatTracker[x].firstName, NAME_LENGTH);							 // save first name in f an dlast name in l
			strncpy(lastName, seatTracker[x].lastName, NAME_LENGTH);
			seatNum = seatTracker[x].seatNumber;												 // save seat number as n

			if (seatTracker[x].seatStatus == FULL)												 // checks if seat is full or not
				seat = "FULL";
			else
				seat = "FREE";

			fprintf(newFile, "%d %s %s %s", seatNum, seat, lastName, firstName);				 // print all values to the file
			fprintf(newFile, "\n");
		}

		fclose(newFile);

	}
}

void ReadPassengersFromFile(const char* filename, PLANESEAT seatTracker[]) {
	FILE* ogFile = fopen(filename, "r");														// opens file to read from
		
	if (ogFile) {
		printf("File reading successful\n");

		if (ogFile == NULL) {
			perror("Error opening original file");											    // error check
			exit(EXIT_FAILURE);
		}

		int currentSeat = 0;																	// renamed a lot of variables
		char firstName[NAME_LENGTH] = { '\0' },
			lastName[NAME_LENGTH] = { '\0' }, s[STATUS_SIZE] = { '\0' };						// temp variables for information
		int seatNumber = 0;

		while (fscanf(ogFile, "%d %s %s %s",													// saves values to temp variables before sending them to array
			&seatNumber, &s, &lastName, &firstName) == 4) {

			strncpy(seatTracker[currentSeat].firstName, firstName, NAME_LENGTH);				// saves first and last name
			strncpy(seatTracker[currentSeat].lastName, lastName, NAME_LENGTH);
			seatTracker[currentSeat].seatNumber = seatNumber;
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

void PrintPassengers(PLANESEAT seatTracker[]) {
	int currentSeat = 0;

	while (currentSeat < PLANE_SIZE) {															// checks if seat is full and if it is it prints it
		if (seatTracker[currentSeat].seatStatus == FULL)
			printf("Passenger ID: Seat #%d, %s, %s\n", seatTracker[currentSeat].seatNumber,
				seatTracker[currentSeat].lastName, seatTracker[currentSeat].firstName);
		currentSeat++;
	}

}

int NumOfFREESeats(PLANESEAT seatTracker[]) {
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

void PrintFreeSeats(PLANESEAT seatTracker[]) {
	int currentSeat = 0;

	while (currentSeat < PLANE_SIZE) {															// checks if seat is full and if it is NOT it prints it
		if (seatTracker[currentSeat].seatStatus == FREE)
			printf("Passenger ID: Seat #%d, %s, %s\n", seatTracker[currentSeat].seatNumber,
				seatTracker[currentSeat].lastName, seatTracker[currentSeat].firstName);
		currentSeat++;
	}

}

void RemovePassenger(int inputNum, PLANESEAT seatTracker[]) {
	int x = inputNum - 1;

	if (seatTracker[x].seatStatus == FULL) {
		seatTracker[x].seatStatus = FREE;														// makes seat FREE

		strncpy(seatTracker[x].firstName, "N/A", NAME_LENGTH);									// puts N/A for first/last name
		strncpy(seatTracker[x].lastName, "N/A", NAME_LENGTH);

	}
}

void AddPassenger(int inputNum, PLANESEAT seatTracker[]) {
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


//TODO figure out how to sort properly
void SortNames(int* inputNum, PLANESEAT seatTracker[]) {
	/*
	if (inputNum == 1) {
		for (int i = 0; i < PLANE_SIZE; i++) {
			if (strcmp(seatTracker[i].firstName, seatTracker[i+1].firstName) > 1)
			printf("Passenger ID: Seat #%d, %s, %s\n", seatTracker[i].seatNumber,
				seatTracker[i].lastName, seatTracker[i].firstName);
		}
	}
	if (inputNum == 2) {

	}
	else {

	}
	*/
}

bool FindPassenger(char inputName[], PLANESEAT seatTracker[]) {	
	for (int i = 0; i < PLANE_SIZE; i++) {														// checks every name to see
		if (strcmp(inputName, seatTracker[i].firstName) == 0) {
			printf("\nPassenger ID: Seat #%d, %s, %s\n", seatTracker[i].seatNumber,				// prints the passenger with that name and returns true
				seatTracker[i].lastName, seatTracker[i].firstName);
			return true;
		}
	}
	printf("\nUnable to find passenger\n");


	return false;
}
