/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.
 */


#ifndef COMMUNICTOR
#define COMMUNICTOR
#endif /* ifndef COMMUNICTOR */

#include <assert.h>
#include <stdio.h>
#include "Communicator.h"



/*
 * Preconditions: id provided has been connected to. 
 * Postconditions: fan has been (de)activated and the fanstatus struct has been updated accordingly
 *
 * will provide an error code if id provided is not connected to 
 */
public int activateFans(int id, bool active)
{
	assert(false);
}

private fanstatus_t initiateUsbConnection()
{
	assert(false);	
}


