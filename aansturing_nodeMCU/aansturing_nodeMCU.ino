#define RelayPin 5

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(RelayPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(RelayPin, HIGH);
//  delay(5000);
//  digitalWrite(RelayPin, LOW);
//  delay(5000);
}
