#include <iostream>
#include "Communicator.h"
#include "controlPanel.h"
#include "fanstatus.h"
#include <fstream>
#include <chrono>
#include <thread>

#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings

void testCommunicator() {
    communicator commie;
    commie.refreshStatus();
}

void testControlPanel(){
    communicator commie;
    commie.refreshStatus();
    controlPanel panel(&commie); //test interupts manually
}

//dirty way to test all the subclasses
void testMe() {
    testCommunicator();
    testControlPanel();
}

void sleep(int seconds){
    std::chrono::seconds dura(seconds);
    std::this_thread::sleep_for( dura );
}


int main(int argc, char *argv[]){
    UNUSED(argc);
    UNUSED(argv);
	//todo imlementation. 
    testMe(); // can be removed in production
    sleep(60);
	//todo periodicly refresh the status of the system

    return 0;
}
