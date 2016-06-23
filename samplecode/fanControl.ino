int fanPulse = 0;
unsigned long pulseDuration;

void setup()
{
	Serial.begin(9600);
	pinMode(fanPulse, INPUT);
	digitalWrite(fanPulse,HIGH);
}

void readPulse() {
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
	analogWrite(3,20);
	delay(5000);
	readPulse();
	analogWrite(3,50);
	delay(5000);
	readPulse();
	analogWrite(3,100);
	delay(5000);
	readPulse();
	analogWrite(3,200);
	delay(5000);
	readPulse();
	analogWrite(3,255);
	delay(5000);
	readPulse();
}
