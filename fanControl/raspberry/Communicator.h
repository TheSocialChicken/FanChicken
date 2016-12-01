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
#include "fanstatus.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>

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
    int activateFans(std::string devicePath, bool active);

    /*
     * Updates internal fanList. After function returns, all the information in the fanList should be up-to-date.
     */
    void refreshStatus();
private:
    /*
     * vector that contains all the information about the Fans
     */
    
    std::vector<fanstatus_t> fanList;
    

    /*
     * Pushes the fanList to the controlPanel. 
     */
    void pushUpdates();

    /*
     * List current arduino devices is /dev/
     */
    std::vector<std::string> getArduinoDevicePaths();


    /*
     * Get the status of the specified device, return its status as an fanstatus_t struct
     */
    fanstatus_t getStatus(fanstatus_t);
};
#endif /* ifndef COMMUNICTOR */
