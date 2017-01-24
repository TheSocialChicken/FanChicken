
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
#include "string"
#include <cmath>
controlPanel* contr;
communicator* comm;
std::mutex muLCD;

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
    contr = this;
    comm = commie;

    wiringPiISR(BUTTON1PIN, INT_EDGE_BOTH, &button1StatusChange);
    wiringPiISR(BUTTON2PIN, INT_EDGE_BOTH, &button2StatusChange);
    wiringPiISR(BUTTON3PIN, INT_EDGE_BOTH, &button3StatusChange);

	//setup display
    muLCD.lock();
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
    muLCD.unlock();

}

//TODO display if error
//FIXME: 'Activated' status incorrectly displayed. Data management is suspect
int controlPanel::updateStatus(fanstatus_t status){
   std::cout << "FanboxID: " << status.id << '\n'; 
   std::cout << "Activated: " << status.active << '\n'; 
   std::cout << "Tempurature: " << status.temperature << '\n';
   std::cout << "Humidity: " << status.humidity << '\n';
    std::cout.flush();

    return 0;
}

void controlPanel::checkButtonStatus() {
    DEBUG_MSG("Checking all button status");
    button1StatusChange();
    button2StatusChange();
    button3StatusChange();
}

void controlPanel::getAndDisplayStatus() {

    comm->refreshStatus();
    DEBUG_MSG("WARNING: DISPLAYDRIVER NEEDS IMPLEMENTATION!");
    int lcdLine = 0;

    std::string lcdString [4] = {"", "", "", ""};



    for (int i = 0; i < 10; i++) {
        fanstatus_t elem = comm->getStatusFromID(i);
        if (elem.id != -1 && lcdLine < 4) {
            updateStatus(elem);
            lcdString[lcdLine].append(std::to_string(elem.id));
            lcdString[lcdLine].append(": ON=");
            lcdString[lcdLine].append(std::to_string(elem.active));
            lcdString[lcdLine].append(" T=");
            lcdString[lcdLine].append(std::to_string((int) std::round(elem.temperature)));
            lcdString[lcdLine].append(" H=");
            lcdString[lcdLine].append(std::to_string((int) std::round(elem.humidity)));
            lcdLine++;
        }
    }
        DEBUG_MSG("LCD: " << lcdString[0]);
        DEBUG_MSG("LCD: " << lcdString[1]);
        DEBUG_MSG("LCD: " << lcdString[2]);
        DEBUG_MSG("LCD: " << lcdString[3]);

    muLCD.lock();
        lcdHome(fd);
        lcdClear(fd);
        lcdPuts(fd, lcdString[0].c_str());

        lcdPosition(fd, 0, 1);
        lcdPuts(fd, lcdString[1].c_str());
        lcdPosition(fd, 0, 2);
        lcdPuts(fd, lcdString[2].c_str());
        lcdPosition(fd, 0, 3);
    lcdPuts(fd, lcdString[3].c_str());
    muLCD.unlock();
    
}

void controlPanel::button1StatusChange(){
    DEBUG_MSG("button1StatusChange method entered");
    int pinReadout = digitalRead(BUTTON1PIN); 
    DEBUG_MSG("Button 1 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(1, false) : comm->activateFans(1, true);
    contr->getAndDisplayStatus();
}

void controlPanel::button2StatusChange(){
    DEBUG_MSG("button2StatusChange method entered");
    int pinReadout = digitalRead(BUTTON2PIN); 
    DEBUG_MSG("Button 2 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(2, false) : comm->activateFans(2, true);
    contr->getAndDisplayStatus();
}

void controlPanel::button3StatusChange(){
    DEBUG_MSG("button3StatusChange method entered");
    int pinReadout = digitalRead(BUTTON3PIN); 
    DEBUG_MSG("Button 3 status = "); DEBUG_MSG(pinReadout);
    (pinReadout) ? comm->activateFans(3, false) : comm->activateFans(3, true);
    contr->getAndDisplayStatus();
}

