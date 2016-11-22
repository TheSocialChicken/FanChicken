
/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * 2016 Koen Schoute <koen@gorgabal.nl>
 *
 */

#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings

#include "Communicator.h"
const string arduinoDevPath = "/dev/ACM"; //without number

	communicator::communicator(){
		//default contructor 
		//TODO implementation
	}

	int communicator::activateFans(int id, bool active){
	    UNUSED(id);
	    UNUSED(active);
		assert(false);
		//TODO implementation
	}

	fanstatus_t communicator::initiateUsbConnection() {
	 /*   for (int i = 0; i < 10; i++) {
		string elem(arduinoDevPath + std::to_string(i));

	    }
	*/		
	    
	    	assert(false);
		//TODO implementation
	}
