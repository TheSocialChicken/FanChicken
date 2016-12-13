
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
#include <mutex>
using namespace std;

std::mutex mutexComm;

communicator::communicator() {
    //default contructor
    //TODO implementation
}

int communicator::activateFans(int id, bool active) {
    fanstatus_t status = getStatusFromID(id);
    if (status.id == -1) {
        return 1;
    } else {
        activateFans(status.devicepath, active);
        return 0;
    }
}

fanstatus_t communicator::getStatusFromID(int id) {
    for (unsigned int i = 0; i < fanList.size(); i++) {
        fanstatus_t elem = fanList.at(id);
        if (elem.id == id) {
            return elem;
        }
    }
    fanstatus_t noStatusFound;
    noStatusFound.id = -1;
    return noStatusFound;
}

int communicator::activateFans(string devicePath, bool active) {
    mutexComm.lock();
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts"); //Activates the tty connection with the Arduino,

    ifstream Arduino_Input(devicePath); //Opens the tty connection as an ifstream
    ofstream Arduino_Output(devicePath); //Opens the tty connection as an ofstream, not used in this example
    if (active) {
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
    mutexComm.unlock();
    return 1;
}

void communicator::refreshStatus() {
    mutexComm.lock();

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
    mutexComm.unlock();
}

vector<string> communicator::getArduinoDevicePaths() {
    mutexComm.lock();
    vector<string> returnVar;

    const string arduinoDevicePath = "/dev/ttyACM"; //without number
    for (int i = 0; i < 10; i++) {
        string path = (arduinoDevicePath + std::to_string(i));

        ifstream f(path);
        if (f.good()) {
            returnVar.push_back(path);
        }
    }
    return returnVar;
    mutexComm.unlock();
}

fanstatus_t communicator::getStatus(fanstatus_t argStatus) {
    mutexComm.lock();
    fanstatus_t returnStatus = argStatus;

    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts"); //Activates the tty connection with the Arduino,

    ifstream Arduino_Input(argStatus.devicepath); //Opens the tty connection as an ifstream
    ofstream Arduino_Output(argStatus.devicepath); //Opens the tty connection as an ofstream,

    string arduinoOutputString;
    Arduino_Output << FANINFO; //reguest to get information from the arduino
    flush(Arduino_Output);

    do {
        system("sleep 1"); //dirty, need to fix sometime later
        std::getline(Arduino_Input, arduinoOutputString);
    } while (arduinoOutputString.empty());

    Arduino_Input.close();
    //http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

    if (arduinoOutputString.at(0) == 'U') {
        arduinoOutputString.erase(0, 1);
        string active = arduinoOutputString.substr(0, arduinoOutputString.find(','));
        arduinoOutputString.erase(0, arduinoOutputString.find(',') + 1);


        string error = arduinoOutputString.substr(0, arduinoOutputString.find(','));
        arduinoOutputString.erase(0, arduinoOutputString.find(',') + 1);


        string temperature = arduinoOutputString.substr(0, arduinoOutputString.find(','));
        arduinoOutputString.erase(0, arduinoOutputString.find(',') + 1);


        string humidity = arduinoOutputString.substr(0, arduinoOutputString.find(','));
        arduinoOutputString.erase(0, arduinoOutputString.find(',') + 1);

        active[0] == 1 ? returnStatus.active = true : returnStatus.active = false;
        error[0] == 1 ? returnStatus.error = true : returnStatus.error = false;
        returnStatus.temperature = ::atof(temperature.c_str());
        returnStatus.humidity = ::atof(humidity.c_str());
    }

    mutexComm.unlock();
    return returnStatus;
}