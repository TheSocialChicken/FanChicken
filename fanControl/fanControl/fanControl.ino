#include <DHT.h>

#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define relayPin 8
#define onButton 12
#define offButton 11
#define bounceInterval 5
#define debugPin 17
#define errorPin 7
#define DHTPIN 2 // Pin which is connected to the DHT sensor.


bool fanActive = false;
bool error = false;
float temperature;
float humidity;
unsigned long SensorMilliSecCount = millis();

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(errorPin, OUTPUT);
  pinMode(debugPin, OUTPUT);
  pinMode(onButton, INPUT);

  dht.begin();
}


void loop()
{

  if (fanActive) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(debugPin, LOW);
  } else {
    if (!fanActive) {
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
   reads out sensors and serial line.
   Sends information back to pi if requested
*/
void updateStatus() {

  while (Serial.available() != 0) {
    piSignal = Serial.read();
  }

  switch (piSignal) {

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

  readDHT();
}

void sendVerboseStatus() {
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
void sendStatus() {
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

void readDHT() {
  self implemented non-blocking timer)
  if (SensorMilliSecCount + 1000 < millis()) {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
  }

}
