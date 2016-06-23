#define fanPulse1 A0
#define fanPulse2 A1
#define fanPulse3 A2

#define fanControl1 3
#define fanControl2 5
#define fanControl3 6

unsigned long pulseDuration;

void setup()
{
  Serial.begin(9600);
  pinMode(fanPulse1, INPUT);
  pinMode(fanPulse2, INPUT);
  pinMode(fanPulse3, INPUT);
  digitalWrite(fanPulse1,HIGH);
  digitalWrite(fanPulse2,HIGH);
  digitalWrite(fanPulse3,HIGH);
}

void readPulse(int fanPulse) {
  Serial.print("FanPulse");
  Serial.println(fanPulse);
  pulseDuration = pulseIn(fanPulse, LOW);
  double frequency = 1000000/pulseDuration;

  Serial.print("pulse duration:");
  Serial.println(pulseDuration);

  Serial.print("time for full rev. (microsec.):");
  Serial.println(pulseDuration*2);
  Serial.print("freq. (Hz):");
  Serial.println(frequency/2);
  Serial.print("RPM:");
  Serial.println(frequency/2*60);

}

void loop()
{
	analogWrite(fanControl1,20);
	analogWrite(fanControl2,20);
	analogWrite(fanControl3,20);
	delay(5000);
	readPulse(fanPulse1);
	readPulse(fanPulse2);
	readPulse(fanPulse3);
	analogWrite(fanControl1,255);
	analogWrite(fanControl2,255);
	analogWrite(fanControl3,255);
	delay(5000);
  readPulse(fanPulse1);
  readPulse(fanPulse2);
  readPulse(fanPulse3);
}
