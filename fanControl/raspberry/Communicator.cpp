
/*
 * Responsible for the communication with the arduinos and to update the status. 
 *
 * 2016 Koen Schoute <koen@gorgabal.nl>
 *
 */

#define UNUSED(x) (void)(x) //temporary supress unused parameter compiler warnings
#define FANOFF 0
#define FANON 1
#define FANINFO 2
#include "Communicator.h"

using namespace std;
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
                    Arduino_Output << FANON;
		    flush(Arduino_Output);
		    std::cout << "FANS TURNED ON FOR DEVICE " << devicePath << '\n';
		    flush(std::cout);
		    return 0;
	    } else {
		    Arduino_Output << FANOFF;
		    flush(Arduino_Output);
		    std::cout << "FANS TURNED OFF FOR DEVICE " << devicePath << '\n';
		    flush(std::cout);
		    return 0;
	    }
	return 1;
}

void communicator::refreshStatus() { 
    //TODO TEST THIS METHOD

    fanList.clear(); //empty device list
    vector<string> devicePaths = getArduinoDevicePaths();

    //convert devicePaths to fanstatus structs
    for (unsigned int i = 0; i < devicePaths.size(); i++) {
        const string elem = devicePaths.at(i);
        fanstatus_t newStatus;
        newStatus.devicepath = elem;
        newStatus.id = i + 1;
        fanList.push_back(newStatus);
    }

    for (unsigned int i = 0; i < fanList.size(); i++) {
        fanList.at(i) = getStatus(fanList.at(i));
    }
}

vector<string> communicator::getArduinoDevicePaths() {
    vector<string> returnVar;

    const string arduinoDevicePath = "/dev/ACM"; //without number
    for (int i = 0; i < 10; i++) {
        string path = (arduinoDevicePath + std::to_string(i));

        ifstream f(path);
        if (f.good()) {
            returnVar.push_back(path);
        }
    }
    return returnVar;
}

fanstatus_t communicator::getStatus(fanstatus_t argStatus) {
    fanstatus_t returnStatus = argStatus;

    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts"); //Activates the tty connection with the Arduino,

    ifstream Arduino_Input(argStatus.devicepath); //Opens the tty connection as an ifstream
    ofstream Arduino_Output(argStatus.devicepath); //Opens the tty connection as an ofstream,
    
    Arduino_Output << FANINFO; //reguest to get information from the arduino
    char data[6];
    data[0] = 0;
    
    while(!Arduino_Input.eof()){
        Arduino_Input.get(data, 5, ',');
        if(strcmp(&data[0], "U") == 0){
            Arduino_Input.get(data, 5, ','); //FANACTIVE
            data[0] == 1 ? returnStatus.active = true : returnStatus.active = false;
            Arduino_Input.get(data, 5, ','); //ERROR STATE
            data[0] == 1 ? returnStatus.error = true : returnStatus.error = false;
            Arduino_Input.get(data, 5, ','); //temperature
            //TODO continue with implementation, not yet complete
            returnStatus.temperature = ::atof(data);
            Arduino_Input.get(data, 5, ','); //humidity
            returnStatus.humidity = ::atof(data);
        }
    }
    
    return returnStatus;
}

void communicator::pushUpdates() {
    //TODO implementation
}


