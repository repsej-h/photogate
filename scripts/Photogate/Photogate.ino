#define SensorPin 2 

//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 38 to print light level to console

volatile bool trigger = false;

void setup() {
  Serial.begin(9600); // sets serial port for communication
  Serial.println("Photogate up and running");

  // set up sensor
  pinMode(SensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(SensorPin), triggered, RISING);

  // set up build in led
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  if (trigger){   
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
    trigger = false;
  }
  delay(10);
  
}

void triggered(){
  trigger = true;
}