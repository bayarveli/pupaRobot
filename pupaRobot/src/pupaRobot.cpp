//============================================================================
// Name        : pupaRobot.cpp
// Author      : Veli Bayar
// Version     :
// Copyright   : puparobot@2015
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include <termios.h>

/* Included for TCP IP socket operations*/
#include <sys/socket.h>
#include <netdb.h>

/* makcakoca libraries */
#include "PupaClass/pwmLib.h"
#include "PupaClass/gpioLib.h"
#include "PupaClass/serialLib.h"


#define WHEEL_BASE 165 // in millimeters
#define WHEEL_OUTER_DIAMETER 65 // in millimeters
#define WHEEL_RADIUS 32.5 // in millimeters

using namespace std;

// The flag for terminating program
bool terminateProg = true;

// Teleop variables - nonblocking keyboard input
int kfd = 0;
struct termios cooked,raw;

// Signal handler for understanding CTRL+C pressed or not
void sighandler(int sig)
{
	cout << "Terminating..." << endl;

	terminateProg = false;
}





int main()
{
	/*
	 * Settings for read console
	 * */
	char keyboardValue;

	tcgetattr(kfd,&cooked);
	memcpy(&raw, &cooked, sizeof(struct termios));
	raw.c_lflag &=~ (ICANON | ECHO);
	raw.c_cc[VEOL] = 1;
	raw.c_cc[VEOF] = 2;
	tcsetattr(kfd, TCSANOW, &raw);

	/*
	 * Raspberry Pin 16 -> IN1 (Red Cable)
	 * Raspberry Pin 18 -> IN2 (Green Cable)
	 * */
	IMGPIO rightMotorInput1("23");
	IMGPIO rightMotorInput2("24");

	/*
	 * Raspberry Pin 29 -> IN3 (Blue Cable)
	 * Raspberry Pin 31 -> IN4 (Orange Cable)
	 * */
	IMGPIO leftMotorInput1("5");
	IMGPIO leftMotorInput2("6");



	/*Set direction pins as output*/
	rightMotorInput1.SetPinDirection(IMGPIO::OUTPUT);
	rightMotorInput2.SetPinDirection(IMGPIO::OUTPUT);
	leftMotorInput1.SetPinDirection(IMGPIO::OUTPUT);
	leftMotorInput2.SetPinDirection(IMGPIO::OUTPUT);

	/* Signal handler for catching "CTRL+C" and break the while loop*/
	signal(SIGINT,&sighandler);


	/*PWM */
	/* Raspberry Pin 12 -> ENA (Gray Cable) */
	/* Raspberry Pin 33 -> ENB (Purple Cable) */

	PWM MotorPWM(1000.0,256,80.0,PWM::MSMODE);

	rightMotorInput1.SetPinValue(IMGPIO::LOW);
	rightMotorInput2.SetPinValue(IMGPIO::LOW);
	leftMotorInput1.SetPinValue(IMGPIO::LOW);
	leftMotorInput2.SetPinValue(IMGPIO::LOW);

	ofstream pwmVelocity;
	pwmVelocity.open("/home/pi/Desktop/test.txt");


	serialPort seriport;

	seriport.openUART();
	seriport.configureUART();

	int duty = 0;
	bool logFlag = false;

	serialPort::SERIAL_PORT_DATA serialPortData;

	while(terminateProg)
	{


		// Read keyboard from console
		if(read(kfd, &keyboardValue, 1) < 0)
		{
			cout << "Keyboard input error!..." << endl;
		}

		//
		switch(keyboardValue)
		{
			case 'w':
				cout << "Move forward..." << endl;
				leftMotorInput1.SetPinValue(IMGPIO::HIGH);
				leftMotorInput2.SetPinValue(IMGPIO::LOW);
				rightMotorInput1.SetPinValue(IMGPIO::LOW);
				rightMotorInput2.SetPinValue(IMGPIO::HIGH);
				break;
			case 's':
				cout << "Move backward..." << endl;
				leftMotorInput1.SetPinValue(IMGPIO::LOW);
				leftMotorInput2.SetPinValue(IMGPIO::HIGH);
				rightMotorInput1.SetPinValue(IMGPIO::HIGH);
				rightMotorInput2.SetPinValue(IMGPIO::LOW);
				break;
			case 'd':
				cout << "Turn right..." << endl;
				leftMotorInput1.SetPinValue(IMGPIO::LOW);
				leftMotorInput2.SetPinValue(IMGPIO::LOW);
				rightMotorInput1.SetPinValue(IMGPIO::LOW);
				rightMotorInput2.SetPinValue(IMGPIO::HIGH);
				break;
			case 'a':
				cout << "Turn left..." << endl;
				leftMotorInput1.SetPinValue(IMGPIO::HIGH);
				leftMotorInput2.SetPinValue(IMGPIO::LOW);
				rightMotorInput1.SetPinValue(IMGPIO::LOW);
				rightMotorInput2.SetPinValue(IMGPIO::LOW);
				break;
			case 'k':
				cout << "Increase linear velocity..." << endl;
				duty++;
				if(duty >= 256)
				{
					duty = 256;
				}
				cout << duty << endl;
				MotorPWM.SetDutyCycleCount(duty,0); // increase Duty Cycle by 16 counts every two seconds
				MotorPWM.SetDutyCycleCount(duty,1); // increase Duty Cycle by 16 counts every two seconds

				break;
			case 'l':
				cout << "Decrease linear velocity..." << endl;
				duty--;
				if(duty <= 0)
				{
					duty = 0;
				}
				MotorPWM.SetDutyCycleCount(duty,0); // increase Duty Cycle by 16 counts every two seconds
				MotorPWM.SetDutyCycleCount(duty,1); // increase Duty Cycle by 16 counts every two seconds

				cout << duty << endl;
				break;
			case 'n':
				cout << "Increase angular velocity..." << endl;
				break;
			case 'm':
				cout << "Decrease angular velocity..." << endl;
				break;
			case 'x':
				cout << "Break!..." << endl;
				rightMotorInput1.SetPinValue(IMGPIO::LOW);
				rightMotorInput2.SetPinValue(IMGPIO::LOW);
				leftMotorInput1.SetPinValue(IMGPIO::LOW);
				leftMotorInput2.SetPinValue(IMGPIO::LOW);
				break;
		}




//		serialPortData = seriport.readUART();
//
//		if(serialPortData.rxBufferLength == 12 && logFlag == true)
//		{
//			pwmVelocity << duty << " " << serialPortData.rxBuffer << endl;
//		}

	}


	pwmVelocity.close();
	seriport.closeUART();
	tcsetattr(kfd, TCSANOW, &cooked);
	return 0;
}





