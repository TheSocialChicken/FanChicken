
/*
 * author: Koen Schoute, koen@gorgabal.nl (october 2016)
 * (description of responsibilities of class)
 */

#include "fanStatusManager.h"
#include <assert.h>

fanStatusManager::fanStatusManager(){
	//default constructor TODO
}

fanstatus_t fanStatusManager::setFanStatus(fanstatus_t status){
	 //TODO: imlement this!
	 assert(false);
}


fanstatus_t fanStatusManager::getFanStatus(int id){
	 //TODO: imlement this!
	 assert(false);
}

fanstatus_t[] getFanStatus(){
	 //TODO: imlement this!
	 assert(false);
}



//self test
int main(int argc, char *argv[])
{
	assert(false);

	fanStatusManager testManager = fanStatusManager::fanStatusManager();
	//check if null
	assert(testManager);
	fanstatus_t testStatus;
	fanStatusManager::setFanStatus(testStatus);
	fanstatus_t = fanStatusManager::getFanStatus()
	assert(fanstatus.id == -1);
	
	return 0;
}
