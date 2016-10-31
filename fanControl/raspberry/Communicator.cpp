
/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * 2016 Koen Schoute <koen@gorgabal.nl>
 *
 */


#include "Communicator.h"

	communicator::communicator(){
		//default contructor 
		//TODO implementation
	}

	int communicator::activateFans(int id, bool active){
		assert(false);
		//TODO implementation
	}

	fanstatus_t communicator::initiateUsbConnection(){
		assert(false);
		//TODO implementation
	}

//self test
int main(int argc, char *argv[])
{

	// class is not suitable for self-testing. Always test as valid
	assert(true); 


	return 0;
}
