#define SensorPin A0 // pin where we connected the LDR and the resistor

// variables for sensor state
int SensorValue = 0;     
int preSensorValue = 0;

//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 38 to print light level to console


void setup() {
  Serial.begin(9600); // sets serial port for communication
  Serial.println("Photogate up and running");
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  SensorValue = analogRead(SensorPin); // read the value from the sensorpin

  if (SensorValue > threshold && preSensorValue < threshold){   // switch state: no light reaching sensor after a periode of light reaching the sensor
    if (!timing){
      timing = true;
      startT = millis();
      Serial.println("Sensor triggerd, timer started");
      digitalWrite(LED_BUILTIN, HIGH); // turn on led when timing
    } else {
      Serial.println("Sensor triggerd, timer stopped");
      stopT = millis();
      deltaT = stopT - startT;
      Serial.print("Time Elapsed: ");
      Serial.println(deltaT);
      timing = false;
      digitalWrite(LED_BUILTIN, LOW); // turn off led when done
    }
  }
  preSensorValue = SensorValue;
  //Serial.println(SensorValue);
  delay(10);
  
}
