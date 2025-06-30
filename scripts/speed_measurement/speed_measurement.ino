#define SensorPin1 2 
#define SensorPin2 3

int pins[] = {2,3};
const int arrayLength = sizeof(pins) / sizeof(pins[0]);
//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 38 to print light level to console
unsigned int distance = 100; // distance between photogates in cm

volatile bool trigger = false;

void setup() {
  Serial.begin(9600); // sets serial port for communication
  Serial.println("Photogate up and running");

  // set up sensors

  for (int i = 0; i < arrayLength; i++){
    pinMode( pins[i], INPUT);
    attachInterrupt(digitalPinToInterrupt(pins[i]), triggered, RISING);
  }

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
      Serial.print("Average speed: ");
      Serial.print((distance * .01) / (deltaT* .001) );
      Serial.println(" m / s");
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