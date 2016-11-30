//#include <Bounce2.h>
#define relayPin 8
#define onButton 12
#define offButton 11
#define bounceInterval 5
#define debugPin 17
#define errorPin 7

//Bounce onBounce = Bounce();  
//Bounce offBounce = Bounce();  

//status variables

bool fanActive = false;
bool error = false;
float temperature = -50;
float humidity = -50;


void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(errorPin, OUTPUT);
   pinMode(debugPin, OUTPUT);
  pinMode(onButton, INPUT);
}


void loop()
{
  if(fanActive){
  	digitalWrite(relayPin, HIGH);
  	digitalWrite(debugPin, LOW);
  } else { 
    if(!fanActive){
     	digitalWrite(debugPin, HIGH);
    	digitalWrite(relayPin, LOW);
    } else {
      digitalWrite(errorPin, HIGH);
      Serial.println("ERROR");
    }
  }


	updateStatus();
  
}

char piSignal;
/*
 * reads out sensors and serial line. 
 * Sends information back to pi if requested
 */
void updateStatus(){

  //TODO HUMIDITY SENSOR IMPLEMENTATION
  //TODO TEMPERATURE SENSOR IMPLEMENTATION
  
  
 	while(Serial.available() != 0){
 		piSignal = Serial.read();
  }

	switch(piSignal){

	case '0':
		fanActive = true;
		break;
	case '1':
		fanActive = false;	
		break;
	case '2':
		sendStatus();
		break;
  case '3':
    sendVerboseStatus();
  case 'x':
    //nothing received, do nothing
    break;
	default:
	  Serial.print("received: ");
	  Serial.println(piSignal);
	}

  piSignal = 'x';
}

void sendVerboseStatus(){
  Serial.println();
	Serial.print("fanActive:");
	Serial.println(fanActive);
	Serial.print("error:");
	Serial.println(error);
	Serial.print("temperature:");
	Serial.println(temperature);
	Serial.print("humidity:");
	Serial.println(humidity);
	Serial.println();
}

//It is a bit dirty to convert evyrithing to a char first, but it will do for now. 
void sendStatus(){
	Serial.print('U'); //indicate to raspberry that you are going te do an update
	Serial.print(fanActive);
	Serial.print(',');
	Serial.print(error);
	Serial.print(',');
	Serial.print(temperature);
	Serial.print(',');
	Serial.print(humidity);
	Serial.print('\n');
}
