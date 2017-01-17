
/*
 * main.c
 * Copyright (C) 2016 Koen Schoute <koen@gorgabal.nl>
 *
 * Distributed under terms of the MIT license.https://pinout.xyz/
 */
#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings
#define BUTTON1PIN 23
#define BUTTON2PIN 24
#define BUTTON3PIN 25
#include "controlPanel.h"
#include <mutex>
#include "debug.h"
#include <lcd.h> 

communicator* comm;
std::mutex muInterupt; //prevent multiple interrupts from being handled .simultaneously Should not be necessary, but can never be to careful. 

// very handy site for pinouts: https://pinout.xyz/
int fd = -1;
controlPanel::controlPanel(communicator* commie) {
    DEBUG_MSG("controlPanel starts initialized");
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

	//setup display

	fd = lcdInit(
	    //LCDCONFIG
	    //rows
	    4,
	    //colums
	    20,
	    //bits
	    4,


	    //PINLAYOUT
	    //RS (function select
	    12, 
	    //strobe, E (Enable Signal
	    16, 
	    //d0 - d7, the data pints
	    26,17,21,19,0,0,0,0
	    //0,0,0,0,5,6,13,19
		    );

}

//TODO display if error
//FIXME: 'Activated' status incorrectly displayed. Data management is suspect
int controlPanel::updateStatus(fanstatus_t status){
   std::cout << "FanboxID: " << status.id << '\n'; 
   std::cout << "Activated: " << status.active << '\n'; 
   std::cout << "Tempurature: " << status.temperature << '\n';
   std::cout << "Humidity: " << status.humidity << '\n';
   std::cout.flush();
   DEBUG_MSG("WARNING: DISPLAYDRIVER NEEDS IMPLEMENTATION!");
    //TODO implementation, need to get a display working properly for this to work. 
	lcdHome(fd);
	lcdClear(fd);

	lcdPuts(fd, "CHICKLFANLCDTESTWHOHO");
   return 0;
}

void controlPanel::checkButtonStatus() {
    DEBUG_MSG("Checking all button status");
    button1StatusChange();
    button2StatusChange();
    button3StatusChange();
}

void controlPanel::getAndDisplayStatus() {
    for (int i = 0; i < 10; i++) {
        fanstatus_t elem = comm->getStatusFromID(i);
	if(elem.id != -1){
	    updateStatus(elem);
	}
    }
}

void controlPanel::button1StatusChange(){
    DEBUG_MSG("button1StatusChange method entered");
    muInterupt.lock();
    DEBUG_MSG("button 1: Interupt Lock engaged!");
    int pinReadout = digitalRead(BUTTON1PIN); 
    DEBUG_MSG("Button 1 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(1, true) : comm->activateFans(1, false);	
    muInterupt.unlock();
    DEBUG_MSG("button 1: Interupt Lock released");
}

void controlPanel::button2StatusChange(){
    DEBUG_MSG("button2StatusChange method entered");
    muInterupt.lock();
    DEBUG_MSG("button 2: Interupt Lock engaged!");
    int pinReadout = digitalRead(BUTTON2PIN); 
    DEBUG_MSG("Button 2 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(2, true) : comm->activateFans(2, false);	
    muInterupt.unlock();
    DEBUG_MSG("button 2: Interupt Lock released");
}

void controlPanel::button3StatusChange(){
    DEBUG_MSG("button3StatusChange method entered");
    muInterupt.lock();
    DEBUG_MSG("button 3: Interupt Lock engaged!");
    int pinReadout = digitalRead(BUTTON3PIN); 
    DEBUG_MSG("Button 3 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(3, true) : comm->activateFans(3, false);	
    muInterupt.unlock();
    DEBUG_MSG("button 3: Interupt Lock released");
}

