
/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * 2016 Koen Schoute <koen@gorgabal.nl>
 *
 */

#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings

#include "Communicator.h"
using namespace std;



const string arduinoDevPath = "/dev/ACM"; //without number

	communicator::communicator(){
		//default contructor 
		//TODO implementation
	}

	int communicator::activateFans(int id, bool active){
	    UNUSED(id);
	    UNUSED(active);
		assert(false);
		//TODO implementation
	}
	
	int communicator::activateFans(string devicePath, bool active){
	    	system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");	//Activates the tty connection with the Arduino,

	ifstream Arduino_Input(devicePath); //Opens the tty connection as an ifstream
	ofstream Arduino_Output(devicePath); //Opens the tty connection as an ofstream, not used in this example
	    if(active){
		//activate
		Arduino_Output << 1;
		    flush(Arduino_Output);
		    std::cout << "FANS TURNED ON FOR DEVICE " << devicePath << '\n';
		    flush(std::cout);
		    return 0;
	    } else {
		    Arduino_Output << 0;
		    flush(Arduino_Output);
		    std::cout << "FANS TURNED OFF FOR DEVICE " << devicePath << '\n';
		    flush(std::cout);
		    return 0;
	    }
	return 1;
}

void communicator::refreshStatus() {
    //TODO implementation
}

void communicator::pushUpdates() {
    //TODO implementation
}


