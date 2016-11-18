
#include "Communicator.h"
#include "controlPanel.h"
#include "fanStatusManager.h"
#include "fanstatus.h"

void testFanStatusManager(){
    
    fanStatusManager testManager = fanStatusManager();
	fanstatus_t testStatus;
	testManager.setFanStatus(testStatus);
	testStatus = testManager.getFanStatus(0);
	assert(testStatus.id == -1);
}

void testCommunicator(){
    //TODO IMPLEMENTATION
    assert(false);
}

void testControlPanel(){
    
}

//dirty way to test all the subclasses
void testMe(){
    testFanStatusManager();
    testCommunicator();
    testControlPanel();
}

int main(int argc, char *argv[]){
	//todo imlementation. 
    	testMe(); // can be removed in production
	assert(false);

	return 0;
}