/*
 * *********************************************************************  *
 * Name       :		Mini project c
 * Author	  :		Abdelrahman	Shabrawy
 * Description:		Vehicle Control system
 * Date		  :		07/05/2023
 *
 * * *********************************************************************  *
 */

#include<stdio.h>
/*The conditional preprocessor construct if the constant ==1 the code of
 *engine temperature controller wall evaluate else will not evaluate*/
#define WITH_ENGINE_TEMP_CONTROLLER 1
//define data type of type structures to store all parameters of the system controller
typedef struct system_control_parametrs
{
	// all state parameters are work as on and off
	int Engine_state;

	int AC_state;

	int Engine_Temperature_Controller_state;

	// this the variable parameters of the system controller
	int	Vehicle_Speed;

	int Room_Temperature;

	int Engine_Temperature;

}controller;
//set integer enumeration constants to all states
enum state
{
	Engine_ON=1,AC_ON=1,Engine_Temperature_Controller_ON=1
	,Engine_OFF=0,AC_OFF=0,Engine_Temperature_Controller_OFF=0
};
//functions declaration
void display_main_menu(char *input);

void display_sensors_set_menu(char *input);

void display_vehicle_state(controller *input);

void Traffic_Light_Data(controller *state_ptr);

void Room_Temperature_Data(controller *state_ptr);

void Engine_Temperature_Data(controller *state_ptr);

void Check_vehicle_speed(controller *input);



int main(void)

{
	// vehicle state initialization values
	controller control_system={Engine_OFF,AC_OFF,Engine_Temperature_Controller_OFF,20,25,70};

	//user input for the main menu

	char user_main_input;

	//user input for the sensor menu

	char user_sensor_input;
	// display the main menu when the program run
	display_main_menu(&user_main_input);
	// loop that make program run until user decide to quite the program
	while(user_main_input!='c')
	{
		// check user input to turn engine on/off

		if(user_main_input == 'a')
		{
			// turn engine on and display sensor menu
			control_system.Engine_state = Engine_ON;
			while (control_system.Engine_state == Engine_ON )
			{
				// call sensors set menu to display and take input from user
				display_sensors_set_menu( &user_sensor_input );
				// check user input
				switch ( user_sensor_input )
				{
				// turn engine off and display the main menu
				case 'a':
				{
					control_system.Engine_state = Engine_OFF;
					printf("The Engine Is OFF \n");
					display_main_menu( &user_main_input );
					break;
				}
				/* call traffic light function by address and take input from user
				 *  and display vehicle state and sensors set menu*/
				case 'b':
				{
					Traffic_Light_Data( &control_system );
					Check_vehicle_speed( &control_system );
					display_vehicle_state( &control_system );
					display_sensors_set_menu( &user_sensor_input );
					break;
				}

				/* call room temperature function by address and take input from user
				 *  and display vehicle state and sensors set menu*/
				case 'c':
				{
					Room_Temperature_Data( &control_system );
					Check_vehicle_speed( &control_system );
					display_vehicle_state( &control_system );
					display_sensors_set_menu( &user_sensor_input );
					break;
				}
				/*The conditional preprocessor construct if the constant ==1 the code of
				 *engine temperature controller wall evaluate else will not evaluate*/

#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
				/* call engine temperature function by address and take input from user
				 *  and display vehicle state and sensors set menu*/
				case 'd':
				{

					Engine_Temperature_Data(&control_system);
					Check_vehicle_speed(&control_system);
					display_vehicle_state(&control_system);
					display_sensors_set_menu(&user_sensor_input);
					break;
				}
#endif
				default:
				{
					printf("you enter wrong input \n"
							"Please enter correct one from the sensor set menu\n");
					display_sensors_set_menu(&user_sensor_input);

				}
				}
			}

		}
		// engine off if the user choose 'b'
		if(user_main_input=='b')
		{
			printf("The Engine Is OFF \n");
			display_main_menu(&user_main_input);
		}
	}
	//quite the program if the user input 'c'
	printf("Quite the system good bye");
	return 0;
}

//functions definition

//work to display the main menu for user and take input from user that pass by address
void display_main_menu(char *input)
{
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	fflush(stdout);
	scanf(" %c",input);
}

/* work to display the sensors menu for user and take input from user
 * that pass by address when the engine is on */

void display_sensors_set_menu(char *input)
{
	printf("The Engine Is ON \n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature \n");

	//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
	printf("d. Set the engine temperature \n\n");
#endif
	fflush(stdout);
	scanf(" %c",input);
}

//display vehicle state every read of any sensors in the vehicle
void display_vehicle_state(controller *state_ptr)
{
	switch((state_ptr)->Engine_state)
	{
	case Engine_ON:
	{
		printf("Engine state: ON \n");
		break;
	}
	default:
	{
		printf("Engine state: Off \n");
		break;
	}
	}
	switch((state_ptr)->AC_state)
	{
	case AC_ON:
	{
		printf("AC: ON \n");
		break;
	}
	default:
	{
		printf("AC: Off \n");
		break;
	}
	}
	//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
	switch((state_ptr)->Engine_Temperature_Controller_state)
	{
	case Engine_Temperature_Controller_ON:
	{
		printf("Engine Temperature Controller: ON \n");
		break;
	}
	default:
	{
		printf("Engine Temperature Controller: Off \n");
		break;
	}
	fflush(stdout);
	}
#endif

	printf("Vehicle Speed = %d km/hr\n", (state_ptr)->Vehicle_Speed);
	printf("Room Temperature = %d C\n", (state_ptr)->Room_Temperature);

	//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
	printf("Engine Temperature = %d C\n\n", (state_ptr)->Engine_Temperature);
#endif

}

/* pass by address function that check take
 * user input as a sensor read to control traffic light */
void Traffic_Light_Data(controller *state_ptr)
{
	char light_input;
	//input light color from user
	printf("Enter Required Color\n");
	fflush(stdout);
	scanf(" %c",&light_input);

	switch(light_input)
	{


	case 'g':
	{

		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;

		//preprocessor code that check constant value to evaluate code or to remove it
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_ON;
#endif

		(state_ptr)->Vehicle_Speed=100;
		(state_ptr)->Room_Temperature=25;
		//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=120;
#endif

		break;

	}

	case 'o':
	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
		//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_OFF;
#endif
		//preprocessor code that check constant value to evaluate code or to remove it

		(state_ptr)->Vehicle_Speed=30;
		(state_ptr)->Room_Temperature=25;
		//preprocessor code that check constant value to evaluate code or to remove it

#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=100;
#endif

		break;

	}

	case 'r':
	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
		//preprocessor code that check constant value to evaluate code or to remove it
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_OFF;
#endif
		//preprocessor code that check constant value to evaluate code or to remove it
		(state_ptr)->Vehicle_Speed=100;
		(state_ptr)->Room_Temperature=25;
		//preprocessor code that check constant value to evaluate code or to remove it
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=90;
#endif

		break;

	}
	default:
	{
		printf("you enter wrong input please enter correct one \n");
		printf("Enter Required Color\n");
		fflush(stdout);
		scanf(" %c",&light_input);
		break;
	}

	}
}
/* pass by address function that check take
 * user input as a sensor read to control room temperature */
void Room_Temperature_Data(controller *state_ptr)
{
	int Room_Temperature_input;
	//input light color from user
	printf("Enter Required Room Temperature\n");
	fflush(stdout);
	scanf("%d",&Room_Temperature_input);

	if (Room_Temperature_input <10)
	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_ON;
#endif
		(state_ptr)->Vehicle_Speed=100;
		(state_ptr)->Room_Temperature=20;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=120;
#endif
	}

	else if (Room_Temperature_input >30)

	{

		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_OFF;
#endif
		(state_ptr)->Vehicle_Speed=70;
		(state_ptr)->Room_Temperature=20;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=100;
#endif

	}

	else

	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_OFF;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_OFF;
#endif
		(state_ptr)->Vehicle_Speed=45;
		(state_ptr)->Room_Temperature=Room_Temperature_input;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		(state_ptr)->Engine_Temperature=100;
#endif

	}

}

/* pass by address function that check take
 * user input as a sensor read to control engine temperature */

void Engine_Temperature_Data(controller *state_ptr)
{
	int Engine_Temperature_input;
	//input light color from user
	printf("Enter Required Engine Temperature\n");
	fflush(stdout);

	scanf("%d",&Engine_Temperature_input);

	if (Engine_Temperature_input < 100)
	{

		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_ON;
		(state_ptr)->Vehicle_Speed=100;
		(state_ptr)->Room_Temperature=20;
		(state_ptr)->Engine_Temperature=125;

	}

	else if (Engine_Temperature_input > 150)

	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_ON;
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_ON;
		(state_ptr)->Vehicle_Speed=30;
		(state_ptr)->Room_Temperature=20;
		(state_ptr)->Engine_Temperature=125;
	}

	else

	{
		(state_ptr)->Engine_state= Engine_ON;
		(state_ptr)->AC_state=AC_OFF;
		(state_ptr)->Engine_Temperature_Controller_state=Engine_Temperature_Controller_OFF;
		(state_ptr)->Vehicle_Speed=30;
		(state_ptr)->Room_Temperature=25;
		(state_ptr)->Engine_Temperature=Engine_Temperature_input;
	}
}

/* pass by address function that check speed value */
void Check_vehicle_speed(controller *checker_ptr)
{
	if((checker_ptr)->Vehicle_Speed == 30)
	{
		if(	(checker_ptr)->AC_state== AC_OFF )
		{
			(checker_ptr)->AC_state=AC_ON;

		}
		(checker_ptr)->Room_Temperature=(checker_ptr)->Room_Temperature*(5/4)+1;
		if(	(checker_ptr)->Engine_Temperature_Controller_state == Engine_Temperature_Controller_OFF )
		{
			(checker_ptr)->Engine_Temperature_Controller_state= Engine_Temperature_Controller_ON;
			(checker_ptr)->Engine_Temperature=(checker_ptr)->Room_Temperature;
		}

	}
}
