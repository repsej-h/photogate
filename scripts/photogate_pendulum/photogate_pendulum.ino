#define SensorPin 2 // pin where we connected the sensor

//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 27 - 28 to print light level to console
const unsigned int sanityValue = 5000; // if in this interval no measurements are recorded, the system resets

volatile bool trigger = false;

unsigned long periods[10];
int periodCount = 0; // Keep track of how many periods have been recorded
float average = 0;  
int counts = 10; // amount of periods before calculating the average

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // set up sensor
  pinMode(SensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(SensorPin), triggered, RISING);

  Serial.println(F("========================================"));
  Serial.println(F("       SENSOR MONITORING ACTIVE        "));
  Serial.println(F("========================================"));
  Serial.println(F("Waiting for first trigger..."));
}

void loop() {
  if (trigger) { // switch state: no light reaching sensor after a period of light reaching the sensor
    if (!timing) {
      timing = true;
      startT = millis();
      Serial.println(F("\n[!] Timing Started..."));
    } else if (periodCount < counts) { // Record period only if the array is not full
      stopT = millis();
      deltaT = stopT - startT;

      // Check if the gap is too large (e.g., a new experiment started)
      if (deltaT > sanityValue){ 
        // AUTOMATIC RESET LOGIC
        periodCount = 0; // Wipe the previous progress
        startT = stopT;  // Restart the timer from this new trigger
        Serial.println(F("\n----------------------------------------"));
        Serial.println(F(" !!! AUTO-RESET: Gap detected > 5s !!! "));
        Serial.println(F("  Previous measurements discarded."));
        Serial.println(F("----------------------------------------"));
      } else {
        periods[periodCount] = deltaT;
        periodCount++; 
        
        // ENHANCED OUTPUT: Progress Bar and Stats
        Serial.print(F("Reading "));
        Serial.print(periodCount);
        Serial.print(F("/"));
        Serial.print(counts);
        Serial.print(F(" | Time: "));
        Serial.print(deltaT);
        Serial.print(F(" ms | Progress: ["));
        
        // Simple visual bar
        for (int i = 0; i < counts; i++) {
          if (i < periodCount) Serial.print("=");
          else Serial.print(".");
        }
        Serial.println("]");
        
        startT = stopT;
      }

      // Calculate and print the average only after x periods
      if (periodCount == counts) {
        unsigned long sum = 0;
        for (int i = 0; i < periodCount; i++) {
          sum += periods[i];
        }

        average = (float)sum / periodCount;
        
        Serial.println(F("\n****************************************"));
        Serial.print(F("  AVERAGE PERIOD: "));
        Serial.print(average * 2);
        Serial.println(F(" ms"));
        Serial.println(F("****************************************\n"));
        Serial.println(F("Ready for next set..."));

        // Reset the period count for the next set of x periods
        periodCount = 0;
      }
    }
    trigger = false;
  }
  delay(10); // Small delay to avoid rapid readings
}

void triggered(){
  trigger = true;
}