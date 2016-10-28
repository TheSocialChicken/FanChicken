
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

std::vector<fanstatus_t> getFanStatus(){
	 //TODO: imlement this!
	 assert(false);
}



//self test
int main(int argc, char *argv[])
{

	fanStatusManager testManager = fanStatusManager();
	fanstatus_t testStatus;
	testManager.setFanStatus(testStatus);
	testStatus = testManager.getFanStatus(1);
	assert(testStatus.id == -1);
	
	return 0;
}
