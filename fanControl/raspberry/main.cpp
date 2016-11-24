#include <iostream>
#include "Communicator.h"
#include "controlPanel.h"
#include "fanStatusManager.h"
#include "fanstatus.h"
#include <iostream>
#include <chrono>
#include <thread>

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

void quickAndDirtyFanTest(){
	    	system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");	//Activates the tty connection with the Arduino, needs to run as root
		while(true){
		    system("echo '1' >> /dev/ttyACM0");
		    std::cout << "FANS TURNED ON";
		    flush(std::cout);
		    system("sleep 10");
		    std::cout << "FANS TURNED OFF";
		    flush(std::cout);
		    system("echo '0' >> /dev/ttyACM0");
		}

}

int main(int argc, char *argv[]){
    UNUSED(argc);
    UNUSED(argv);
	//todo imlementation. 
    quickAndDirtyFanTest();
    testMe(); // can be removed in production
    return 0;
}