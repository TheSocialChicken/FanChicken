// compile comando:
//gcc -L/usr/local/lib -lwiringPi -lwiringPiDev -I/usr/local/include -Wall myLCD.c

#include <wiringPi.h>
#include <lcd.h>

int main() {
	displayString();
	return 0;
}

void displayString(){
	wiringPiSetupGpio();

	int fd = lcdInit(
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
	lcdHome(fd);
	lcdClear(fd);

	lcdPuts(fd, "GORGABAL");
}
