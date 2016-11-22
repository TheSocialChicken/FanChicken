#include <iostream>
#include "Communicator.h"
#include "controlPanel.h"
#include "fanStatusManager.h"
#include "fanstatus.h"

#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings

void testFanStatusManager(){
    
    fanStatusManager testManager = fanStatusManager();
	fanstatus_t testStatus;
	testManager.setFanStatus(testStatus);
	testStatus = testManager.getFanStatus(-1);
	assert(testStatus.id == -1);
	std::cout << "fanStatusManager survived the test!";

}

void testCommunicator(){
    //TODO IMPLEMENTATION
    assert(false);
}

void testControlPanel(){
    //TODO IMPLEMENTATION
    assert(false);
}

//dirty way to test all the subclasses
void testMe(){
    testFanStatusManager();
    testCommunicator();
    testControlPanel();
}

int main(int argc, char *argv[]){
    UNUSED(argc);
    UNUSED(argv);
	//todo imlementation. 
    	testMe(); // can be removed in production
	return 0;
}