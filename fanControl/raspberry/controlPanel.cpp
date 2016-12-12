
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

communicator* comm;


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
    
}


int controlPanel::updateStatus(fanstatus_t status){
    UNUSED(status);
    assert(false);
    //TODO implementation, need to get a display working properly for this to work. 
}

void controlPanel::button1StatusChange(){
    (digitalRead(BUTTON1PIN) == 1) ? comm->activateFans(1, true) : comm->activateFans(1, false);	
}

void controlPanel::button2StatusChange(){
    (digitalRead(BUTTON2PIN) == 1) ? comm->activateFans(2, true) : comm->activateFans(2, false);	
}

void controlPanel::button3StatusChange(){
    (digitalRead(BUTTON3PIN) == 1) ? comm->activateFans(3, true) : comm->activateFans(3, false);
}

//TODO, create watch methods for buttons. 
