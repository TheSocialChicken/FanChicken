/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.
 */


#ifndef COMMUNICTOR
#define COMMUNICTOR


#include <assert.h>
#include <stdio.h>
#include "fanStatusManager.h"
#include <string>
#include <sstream>

class communicator{

public:
	communicator(); // declaration default constructor

	/*
	 * Preconditions: id provided has been connected to. 
	 * Postconditions: fan has been (de)activated and the fanstatus struct has been updated accordingly
	 *
	 * will provide an error code if id provided is not connected to 
	 */
	int activateFans(int id, bool active);
        
        /*
         * same as activate
         */
        int activateFans(string devicePath, bool active);
private:
	/*
		Will initiate usb communication with one arduino. Returns its status. Status can be used as a reference for further communication
	*/
	fanstatus_t initiateUsbConnection();

};
#endif /* ifndef COMMUNICTOR */
