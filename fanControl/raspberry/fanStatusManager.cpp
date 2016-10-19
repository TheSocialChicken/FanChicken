/*
 * fanStatusManager.cpp
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include "fanStatusManager.h"


/*
 * The fanstatus struct is meant for holding information about the individual fansystems. 
 * The communicator refers to this struct when doing anything fanstatus related. (update)
 *
 */
struct fanstatus_t {
	/* 
	 * DATA:
	 * int id
	 * string: devicepath
	 * bool:acitve
	 * boor:error
	 * float:temperature
	 * float:humidity
	 *
	 * */

};

struct fanstatus_t fanSystemArray[n];

/*
 * Preconditions: none
 * Postconditions: provided fanstatus struct is added or updated to the internal model. Added if a struct with the same ID is not present, updated if present. 
 * @Returns: a reference to the setted status
 */
public fanstatus_t setFanStatus(fanstatus_t status){
	assert(false);
}

/*
 *  preconditions: fan status must exist
 *  postconditions: none
 *  @id the fanstatus you want to get
 *  @return: a copy of the fanstatus
 */
public fanstatus_t getFanStatus(int id)
{
	assert(false);
}

/*
 *  preconditions: none
 *  postconditions: none
 *  @return: an array containing all elements in fanSystemArray, terminated with an NULL. 
 */
public fanstatus_t[] getFanStatus()
{
	assert(false);
}
