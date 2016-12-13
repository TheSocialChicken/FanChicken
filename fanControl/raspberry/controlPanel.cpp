
/*
 * main.c
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.https://pinout.xyz/
 */
#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings
#define BUTTON1PIN 23
#define BUTTON2PIN 23
#define BUTTON3PIN 23
#include "controlPanel.h"
#include <mutex>

communicator* comm;
std::mutex muInterupt; //prevent multiple interrupts from being handled .simultaneously Should not be necessary, but can never be to careful. 

// very handy site for pinouts: https://pinout.xyz/

controlPanel::controlPanel(communicator* commie) {
    wiringPiSetupGpio(); //use GPIO numbering scheme
    pinMode(BUTTON1PIN,INPUT);
    pullUpDnControl(BUTTON1PIN, PUD_DOWN);
    pinMode(BUTTON2PIN,INPUT);
    pullUpDnControl(BUTTON2PIN, PUD_DOWN);
    pinMode(BUTTON3PIN,INPUT);
    pullUpDnControl(BUTTON3PIN, PUD_DOWN);

    comm = commie;

    wiringPiISR(BUTTON1PIN, INT_EDGE_BOTH, &button1StatusChange);
    wiringPiISR(BUTTON2PIN, INT_EDGE_BOTH, &button2StatusChange);
    wiringPiISR(BUTTON3PIN, INT_EDGE_BOTH, &button3StatusChange);
    
}


int controlPanel::updateStatus(fanstatus_t status){
    UNUSED(status);
    assert(false);
    //TODO implementation, need to get a display working properly for this to work. 
}

void controlPanel::button1StatusChange(){
    muInterupt.lock();
    (digitalRead(BUTTON1PIN) == 1) ? comm->activateFans(1, true) : comm->activateFans(1, false);	
    muInterupt.unlock();
}

void controlPanel::button2StatusChange(){
    muInterupt.lock();
    (digitalRead(BUTTON2PIN) == 1) ? comm->activateFans(2, true) : comm->activateFans(2, false);	
    muInterupt.unlock();
}

void controlPanel::button3StatusChange(){
    muInterupt.lock();
    (digitalRead(BUTTON3PIN) == 1) ? comm->activateFans(3, true) : comm->activateFans(3, false);
    muInterupt.unlock();
}

//TODO, create watch methods for buttons. 
