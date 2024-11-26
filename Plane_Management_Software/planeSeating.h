#pragma once

#include <stdbool.h>
#include <stdlib.h>

// mattr - 71990f24 - assignment4 (refactor)

// header file for plane seat setup

#define PLANE_SIZE					12				// number of seats per plane
#define STATUS_SIZE					5				// length of status thinghy
#define NAME_LENGTH					25				// length of name

typedef enum status { FREE, FULL } STATUS;																		// status to see if seat is full or not (thx steve)

typedef struct planeseat {
	char firstName[NAME_LENGTH];
	char lastName[NAME_LENGTH];
	int seatNumber;
	STATUS seatStatus;
} PLANESEAT;

PLANESEAT seatTracker[PLANE_SIZE];																				// creates an array for the seats

PLANESEAT createPassenger(char FirstName[], char LastName[], int SeatNumber);									// creates new passenger in plane

void DefaultSeats();																							// sets up all seats

void WritePassengersToFile(const char* filename);																// saves the passenger to file

void ReadPassengersFromFile(const char* oldFile);																// reads a passenger from the file

void PrintPassengers();																							// prints all passengers

int NumOfFREESeats();																							// returns # of free seats

void PrintFreeSeats();																							// prints all the free seats

void RemovePassenger(int inputNum);																				// removes a passenger from array

void AddPassenger(int inputNum);																				// adds passenger to array