
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
#include "debug.h"
using namespace std;

std::mutex mutexComm;

communicator::communicator() {
    //TODO: This is obviously the wrong way to do things, make this code BETTER
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM1 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM2 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM3 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM4 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM5 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM6 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM7 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM8 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM9 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
    system("stty -F /dev/ttyACM10 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts >/dev/null 2>&1"); //Activates the tty connection with the Arduino,
}

int communicator::activateFans(int id, bool active) {
    DEBUG_MSG("ActiveFans Method Entered");
    DEBUG_MSG("ID = " << id);
    DEBUG_MSG("active = " << active);
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
        fanstatus_t elem = fanList.at(i);
        if (elem.id == id) {
            return elem;
        }
    }
    fanstatus_t noStatusFound;
    noStatusFound.id = -1;
    return noStatusFound;
}

int communicator::activateFans(string devicePath, bool active) {
    int returncode = 1;
    DEBUG_MSG("ActiveFans Method Entered");
    DEBUG_MSG("devicePath = " << devicePath);
    DEBUG_MSG("active = " << active);


    mutexComm.lock(); //FIXME, program keeps hanging somewhere here
    DEBUG_MSG("mutexCommLock engaged!");
    DEBUG_MSG("Accasing device on " << devicePath << ", activate=" << active);

    ofstream Arduino_Output(devicePath); //Opens the tty connection as an ofstream
    if (active) {
        //activate
        Arduino_Output << FANON;
        flush(Arduino_Output);
        std::cout << "FANS TURNED ON FOR DEVICE " << devicePath << '\n';
        flush(std::cout);
        returncode = 0;
    } else {
        Arduino_Output << FANOFF;
        flush(Arduino_Output);
        std::cout << "FANS TURNED OFF FOR DEVICE " << devicePath << '\n';
        flush(std::cout);
        returncode = 0;
    }
    Arduino_Output.close();
    mutexComm.unlock();
    DEBUG_MSG("mutexCommLock released!");
    return returncode;
}

void communicator::refreshStatus() {
    DEBUG_MSG("refresing device status...");


    fanList.clear(); //empty device list
    DEBUG_MSG("cleared internal List of devices");
    vector<string> devicePaths = getArduinoDevicePaths();
    DEBUG_MSG("Got arduino device paths");
    //convert devicePaths to fanstatus structs
    for (unsigned int i = 0; i < devicePaths.size(); i++) {
        const string elem = devicePaths.at(i);
	DEBUG_MSG("processing device paths: " << elem);
        fanstatus_t newStatus;
        newStatus.devicepath = elem;
        newStatus.id = i + 1;
        fanList.push_back(newStatus);
    }
    DEBUG_MSG("done processing device paths");
    //populate the status with information from the arduino itself!
    for (unsigned int i = 0; i < fanList.size(); i++) {
        fanList.at(i) = getStatus(fanList.at(i));
    }
    DEBUG_MSG("refresing device status... DONE!");
}

vector<string> communicator::getArduinoDevicePaths() {
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
}

fanstatus_t communicator::getStatus(fanstatus_t argStatus) {

    fanstatus_t returnStatus = argStatus;

    mutexComm.lock();
    ifstream Arduino_Input(argStatus.devicepath); //Opens the tty connection as an ifstream
    ofstream Arduino_Output(argStatus.devicepath); //Opens the tty connection as an ofstream,

    string arduinoOutputString;
    Arduino_Output << FANINFO; //reguest to get information from the arduino
    flush(Arduino_Output);

    do {
        std::getline(Arduino_Input, arduinoOutputString);
    } while (arduinoOutputString.empty());

    mutexComm.unlock();
    Arduino_Input.close();
    Arduino_Output.close();
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

        active[0] == '1' ? returnStatus.active = true : returnStatus.active = false;
        error[0] == '1' ? returnStatus.error = true : returnStatus.error = false;
        returnStatus.temperature = ::atof(temperature.c_str());
        returnStatus.humidity = ::atof(humidity.c_str());
    }
    displayInternalData();


    return returnStatus;
}

void communicator::displayInternalData() {

    for (unsigned int i = 0; i < fanList.size(); i++) {
        fanstatus_t elem = fanList[i];
        string StatusString = "";
        StatusString.append(std::to_string(elem.id));
        StatusString.append(": ON=");
        StatusString.append(std::to_string(elem.active));
        StatusString.append(" T=");
        StatusString.append(std::to_string(((int) elem.temperature)));
        StatusString.append(" H=");
        StatusString.append(std::to_string(((int) elem.humidity)));

        std::cout << StatusString << '\n';
        std::cout.flush();

    }
}
