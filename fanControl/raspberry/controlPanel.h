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

//TODO: uncomment when implementing pi stuff
//#include <wiringSerial.h>
//#include <wiringPi.h>




class controlPanel 
{
	public:
		/* preconditions: system is connected and turned on
		 * postconditions: statusindicators have been updated to reflect the status of passed fanstatus object
		 */
		int updateStatus(fanstatus_t status);

	private:

		/*
		* These Methods should be called when a butten is pressed. It should pass the change in status on to the Communicator
		*/
		void button1StatusChange();
		void button2StatusChange();
		void button3StatusChange();
};
#endif /* end include geard*/
