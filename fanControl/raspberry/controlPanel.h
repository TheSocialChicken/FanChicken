/*
 * main.c
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.
 */

//  sudo gcc -Wall -std=gnu99 `mysql_config --cflags --libs` -lwiringPi -lwiringPiDev -Wall readings.c -o readings
// might need to add "-I/usr/local/include -L/usr/local/lib -lwiringPi" to compiler?


#ifndef controlPanelGuard
#define controlPanelGuard

#include "fanstatus.h"
#include "Communicator.h"

//This regueres wiringPi to be installed
#include <wiringSerial.h>
#include <wiringPi.h>




class controlPanel 
{
	public:
	    	/*
		 Default compiler, sets up wiringPi and the like. 
		 */
		controlPanel(communicator *commie);
		
		/* preconditions: system is connected and turned on
		 * postconditions: statusindicators have been updated to reflect the status of passed fanstatus object
		 */
		int updateStatus(fanstatus_t status);

		void checkButtonStatus();


		/*
		 * get the status of the fans from the communicator, and display those
		 */
		void getAndDisplayStatus();
	private:

		/*
     * These Methods should be called when a button is pressed. It should check the status of the button status and pass the state along to the communicator.
     *
		*/
		static void button1StatusChange();
		static void button2StatusChange();
		static void button3StatusChange();
};
#endif /* end include geard*/
