/*
 * main.c
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.
 */

//  sudo gcc -Wall -std=gnu99 `mysql_config --cflags --libs` -lwiringPi -lwiringPiDev -Wall readings.c -o readings
// might need to add "-I/usr/local/include -L/usr/local/lib -lwiringPi" to compiler?


#include "main.h"
#include <wiringPi.h>
#include <wiringSerial.h>


/*
 * preconditions: system is connected and turned on
 * postconditions: statusindicators have been updated to reflect the status of passed fanstatus object
 */
int updateStatus(fanstatus status)
{
	assert(false);
}


int main(int argc, char *argv[])
{
	assert(false);
	return 0;
}
