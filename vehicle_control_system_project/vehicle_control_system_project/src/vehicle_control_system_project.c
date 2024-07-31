
/*
 ============================================================================
 Name        : test.c
 Author      : Mohamed A.Abdelmoatiiii
 Date        : 15/08/2023
 Copyright   : Your copyright notice
 Description : vehicle control system project
 ============================================================================
 */

// Include necessary header files
#include <stdio.h>
#include <stdlib.h>

// Define constants for on and off states
#define on 1
#define off 0
// Define whether engine temperature controller is enabled

#define WITH_ENGINE_TEMP_CONTROLLER 1

// Struct to hold system information
struct information
{
	int AC; // Air conditioning status
	int Engine_Temperature_Controller; // Engine temperature controller status
	int vehicle_speed; // Current vehicle speed
	int room_temperature; // Current room temperature
	int Enginetemperature; // Current engine temperature
	int open; // System open statu
} MO;

// Function prototypes
void initial_values(void);         // Function to set initial values for the system
void initial(void);                // Function to display initial menu
void start_menu(void);             // Function to display start menu
int traffic_light(char q);         // Function to set vehicle speed based on traffic light color
int room_temmperature(int r);      // Function to set room temperature based on input
int engine_Temperature(int w);     // Function to set engine temperature based on input
int speed(int vehicle_speed);      // Function to adjust system parameters based on vehicle speed
void Print(void);                  // Function to display system status


// START CODE
int main(void) {
	// Set output buffering for stdout and stderr
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Initialize the MO struct with initial values
	initial_values();
	//MO = {off, off, 100, 35, 90, off}; Eclipse in this case console doesn't show anything

	char choice, choice1;

	while (MO.open == on) {
		here:
		// Display initial menu
		initial();
		scanf(" %c", &choice);

		if (choice == 'c' || choice == 'C') {
			printf("Quit the system \n");
			break;
		} else if (choice == 'b' || choice == 'B') {
			printf("Turn off the vehicle engine\n\n");
			continue;
		} else if (choice == 'a' || choice == 'A') {
			printf("Sensors set menu \n\n");
			here2:
			// Engine is on, display start menu
			start_menu();
			scanf(" %c", &choice1);
			if (choice1 == 'a' || choice1 == 'A') {
				goto here;
			} else if (choice1 == 'b' || choice1 == 'B') {
				printf("Enter the required color: \n");
				char color;
				scanf(" %c", &color);
				traffic_light(color); // Set traffic light and return vehicle_speed
			} else if (choice1 == 'c' || choice1 == 'C') {
				printf("Enter the required room temp :\n");
				int temp;
				scanf("%d", &temp);
				room_temmperature(temp); // Set room temperature
			} else if (choice1 == 'd' || choice1 == 'D') {
#if WITH_ENGINE_TEMP_CONTROLLER == 1
				printf("Enter the required engine temp :\n");
				int tempengine;
				scanf("%d", &tempengine);
				engine_Temperature(tempengine); // Set engine temperature
#endif
			}
		} else {
			printf("Character not found in the list \n");
		}
		Print(); // Display system status
		goto here2;
	}
	return 0;
}

// Set initial values for the system
void initial_values(void) {
	MO.AC = off;
	MO.Engine_Temperature_Controller = off;
	MO.Enginetemperature = 90;
	MO.open = on;
	MO.room_temperature = 35;
	MO.vehicle_speed = 100;
}

// Set initial menu
void initial(void) {
	printf("a.Turn on the engine\n");
	printf("b.Turn off the engine\n");
	printf("c.Quit the program\n");
}

// Set start menu
void start_menu(void) {
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color \n");
	printf("c. Set the room temperature (Temperature Sensor) \n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
}

// Set vehicle speed based on traffic light color
int traffic_light(char q) {
	int *ptr1 = &MO.vehicle_speed;
	switch(q)
	{
	case 'G':
	case 'g':
		*ptr1 = 100;
		break;
	case'O':
	case 'o':
		*ptr1 = 30;
		speed(30); // Adjust other parameters based on speed
		break;
	case 'R':
	case 'r':
		*ptr1 = 0;
		break;
	}
	return 0;
}

// Set room temperature based on input
int room_temmperature(int t) {
	int *ptr2 = &t;
	if (*ptr2 < 10) {
		MO.AC = on;
		*ptr2 = 20;
		return MO.room_temperature = *ptr2;
	} else if (*ptr2 > 30) {
		MO.AC = on;
		*ptr2 = 20;
		return MO.room_temperature = *ptr2;
	} else {
		MO.AC = off;

		return MO.room_temperature;
	}
}


// Set engine temperature based on input
int engine_Temperature(int w) {
#if WITH_ENGINE_TEMP_CONTROLLER == 1
	if (w < 100) {
		MO.Engine_Temperature_Controller = on;
		return MO.Enginetemperature = 125;
	} else if (w > 150) {
		MO.Engine_Temperature_Controller = on;
		return MO.Enginetemperature = 125;
	} else {
		MO.Engine_Temperature_Controller = off;
		return MO.Enginetemperature; // Temperature is set to 0 when it falls within the permissible range.

	}
#endif
}


// Adjust system parameters based on vehicle speed
int speed(int vehicle_speed) {
	if (vehicle_speed == 30) {
		if (MO.AC == off) {
			MO.AC = on;
			MO.room_temperature = MO.room_temperature * (5 / 4) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER == 1
			MO.Engine_Temperature_Controller = on;
			MO.Enginetemperature = MO.Enginetemperature * (5 / 4) + 1;
#endif
		}
	}
	return 0;
}

// Display system status
void Print(void) {
	if (MO.open == on) {
		printf("Engine  IS ON \n");
		(MO.AC == 1) ? printf("AC IS ON  \n") : printf("AC IS off  \n");
		printf("vehicle speed: %d Km/Hr \n", MO.vehicle_speed);
		printf("room temperature : %d C \n", MO.room_temperature);
#if WITH_ENGINE_TEMP_CONTROLLER == 1
		(MO.Engine_Temperature_Controller == 1) ? printf("Engine Temperature Controller IS ON  \n") : printf("Engine Temperature Controller IS off  \n");
#endif
		printf("Enginetemperature: %d C \n\n\n", MO.Enginetemperature);

	} else {
#if WITH_ENGINE_TEMP_CONTROLLER == 1
		printf("Engine state: OFF \n");
#endif
	}
}
