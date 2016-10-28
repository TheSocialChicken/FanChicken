/*
 * Author: 2016 Koen Schoute <koen@gorgabal.nl>
 */

#ifndef FANSTATUSG
#define FANSTATUSG



#include <stdio.h>
#include <string>
#include "fanstatus.h"
#include <vector>
using namespace std;


class fanStatusManager{


public:

	//default constructor
	fanStatusManager();

	/*
	 * Preconditions: none
	 * Postconditions: provided fanstatus struct is added or updated to the internal model. Added if a struct with the same ID is not present, updated if present. 
	 * @Returns: a reference to the setted status
	 */
	fanstatus_t setFanStatus(fanstatus_t status);


	/*
	 *  preconditions: fan status must exist
	 *  postconditions: none
	 *  @id the fanstatus you want to get
	 *  @return: a copy of the fanstatus
	 */
	fanstatus_t getFanStatus(int id);

	/*
	 *  preconditions: none
	 *  postconditions: none
	 *  @return: an array containing all elements in fanSystemArray, terminated with an NULL. 
	 */
	std::vector<fanstatus_t> getFanStatus();


private:

	// array for holding fanstatus information
    std::vector<fanstatus_t> fanList;

};

#endif
