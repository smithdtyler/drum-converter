/*

This code is based on Arduino examples. It reads a voltage on A0 and writes high on pin 8 when the voltage jumps. 
Modifications copyright Tyler Smith

*/

/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
const int readingcount = 10;
float readings[readingcount];
float previous = 0;
int count = 0;
int timer = 0;
bool hitstate = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
// unclear how fast the RedBoard actually runs.
void loop() {
  timer++;
  if(hitstate){
    if(timer > 500){
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(8, LOW);
      hitstate = false;
      timer = 0;
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(8, HIGH);
    }
  }
  // read the input on analog pin 0:
  int time = micros();
  int sensorValue = analogRead(A0);
  int dur = micros() - time;
  //Serial.println(dur); // Tests show an average latency of about 100 microseconds to read the voltage. Pretty small (less than one millisecond).
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // Serial.print(voltage);
  // Serial.print(", ");
  // Serial.print(previous);
  // Serial.print("\n");
  // Signal detection seems to be pretty fast - the LED turns on almost immediately. 
  // I suspect the problem is with the voltage required for the transistor to activate. I'll set up a separate LED to test this. 
  if((voltage - previous) > 0.3){
    digitalWrite(8, HIGH);
    hitstate = true;
    digitalWrite(LED_BUILTIN, HIGH);
    timer=0;
  } else {
  }
  previous = voltage;
}
