#include <Bounce2.h>
#define relayPin 1
#define onButton 2
#define offButton 3


Bounce onBounce = Bounce();  
Bounce offBounce = Bounce();  

void setup()
{

  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
 
 
  pinMode(onButton, INPUT);
  digitalWrite(onButton, LOW); 
  onBounce.attach(onButton);
  onBounce.interval(5);


  pinMode(offButton, INPUT);
  digitalWrite(offButton, LOW);
  offBounce.attach(offButton);
  offBounce.interval(5);
  

  
  Bounce bouncer02 = Bounce();  
}


void loop()
{

  onBounce.update();
  offBounce.update();
  if(offBounce.read() == true){
	digitalWrite(relayPin, LOW);
  } else {
    if(onBounce.read() == true){
  	digitalWrite(relayPin, HIGH);

    }
  }
}
