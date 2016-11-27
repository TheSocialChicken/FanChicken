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
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

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
private:
    /*
     * vector that contains all the information about the Fans
     */
    
    std::vector<fanstatus_t> fanList;
    /*
     * Updates internal fanList. After function returns, all the information in the fanList should be up-to-date.
     */
    void refreshStatus();

    /*
     * Pushes the fanList to the controlPanel. 
     */
    void pushUpdates();
};
#endif /* ifndef COMMUNICTOR */
