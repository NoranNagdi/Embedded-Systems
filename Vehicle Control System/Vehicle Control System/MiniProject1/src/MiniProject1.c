/*
 ============================================================================
 Name        : MiniProject1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//variables
char main_choice;
char sensors_choice;

typedef enum{
	OFF,ON
}states;


typedef struct{
	states engine_state;
	states AC;
	float vehicle_speed;
	float room_temperature;
	states engine_temperature_controller_state;
	float engine_temperature;
} Vehicle_parameters;

Vehicle_parameters vehicle1 = {ON,OFF,40,30,OFF,90};

//functions prototypes
void display_main_menu();
void display_sensors_menu();
void set_traffic_light_color();
void set_room_temperature();
void set_engine_temperature();
void display_current_vehicle_state();

//functions
const char* getEnumText(states state)
{
   switch (state)
   {
      case OFF: return "OFF";
      case ON:  return "ON";
   }
}

void display_main_menu()
{
	puts("Please choose the action you want\n");
	puts("a.Turn on the vehicle engine");
	puts("b.Turn off the vehicle engine");
	puts("c.Quit the system\n");

	scanf(" %c",&main_choice);
	switch(main_choice)
	{
	case 'a':
		puts("Turn on the vehicle engine\n");
		display_sensors_menu();
		break;
	case 'b':
		puts("Turn off the vehicle engine\n");
		display_main_menu();
		break;
	case 'c':
		puts("Quit the System\n");
		exit(0);
		break;
	default:
		puts("Invalid Option\n");
		display_main_menu();
	}
}

void display_sensors_menu()
{
	puts("Please choose the action you want\n");
	puts("a.Turn off the engine");
	puts("b.Set the traffic light color");
	puts("c.Set the room temperature");
	puts("d.Set the engine temperature\n");

	scanf(" %c",&sensors_choice);
	switch(sensors_choice)
	{
	case 'a':
		display_main_menu();
		break;
	case 'b':
		set_traffic_light_color();
		display_current_vehicle_state();
		display_sensors_menu();
		break;
	case 'c':
		set_room_temperature();
		display_current_vehicle_state();
		display_sensors_menu();
		break;
	case 'd':
		set_engine_temperature();
		display_current_vehicle_state();
		display_sensors_menu();
		break;
	default:
		puts("Invalid Option\n");
		display_sensors_menu();
	}
}

void set_traffic_light_color()
{
	char traffic_light;
	puts("Please choose the required color \n");
	scanf(" %c",&traffic_light);

	switch(traffic_light)
	{
	case 'G':
	case 'g':
		vehicle1.vehicle_speed = 100;
		break;
	case 'O':
	case 'o':
		vehicle1.vehicle_speed = 30;
		break;
	case 'R':
	case 'r':
		vehicle1.vehicle_speed = 0;
		break;
	default:
		puts("Invalid Option\n");
		display_sensors_menu();
	}
}

void set_room_temperature()
{
	float room_temp;
	puts("Please choose the required temperature \n");
	scanf(" %f",&room_temp);

	if(room_temp < 10 || room_temp > 30)
	{
		vehicle1.AC = ON;
		vehicle1.room_temperature = 20;
	}
	else
	{
		vehicle1.AC = OFF;
	}
}

void set_engine_temperature()
{
	float engine_temp;
	puts("Please choose the required temperature \n");
	scanf(" %f",&engine_temp);

	if(engine_temp < 100 || engine_temp > 150)
	{
		vehicle1.engine_temperature_controller_state = ON;
		vehicle1.engine_temperature = 125;
	}
	else
	{
		vehicle1.engine_temperature_controller_state = OFF;
	}
}

void display_current_vehicle_state()
{
	if(vehicle1.vehicle_speed == 30)
	{
		vehicle1.AC = ON;
		vehicle1.room_temperature = (vehicle1.room_temperature *(5.0/4))+1;
		vehicle1.engine_temperature_controller_state = ON;
		vehicle1.engine_temperature = (vehicle1.engine_temperature *(5.0/4))+1;
	}
	printf("Engine State: %s\n",getEnumText(vehicle1.engine_state));
	printf("AC: %s\n",getEnumText(vehicle1.AC));
	printf("Vehicle Speed: %0.1f Km/hr \n",vehicle1.vehicle_speed);
	printf("Room Temperature: %0.1f C\n",vehicle1.room_temperature);
	printf("Engine Temperature Controller State: %s\n",getEnumText(vehicle1.engine_temperature_controller_state));
	printf("Engine Temperature: %0.1f C\n\n",vehicle1.engine_temperature);

}

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	display_main_menu();

	return 0;
}
