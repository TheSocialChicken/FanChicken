#include <iostream>
#include "Communicator.h"
#include "controlPanel.h"
#include "fanstatus.h"
#include <fstream>
#include <chrono>
#include <thread>
#include "debug.h"
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
    DEBUG_MSG("Program started, debug mode enabled");
    system("cat /etc/hostname");
    UNUSED(argc);
    UNUSED(argv);
    //testMe(); // can be removed in production

    communicator commie;
    commie.refreshStatus();
    controlPanel panel(&commie); //test interupts manually
    while (true) {
	DEBUG_MSG("Whiletrueloop lololol");
        panel.checkButtonStatus();
	commie.refreshStatus();
	panel.getAndDisplayStatus();
        sleep(10);
    }
    return 0;
}
