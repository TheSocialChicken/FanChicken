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
    controlPanel panel(&commie);
    //TODO IMPLEMENTATION
    assert(false);
}

//dirty way to test all the subclasses
void testMe() {
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