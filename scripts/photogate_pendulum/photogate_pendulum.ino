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

  // Initial Table Header
  Serial.println(F("\n============================================================"));
  Serial.println(F(" ID  |  TIME (ms)  |  PROGRESS                              "));
  Serial.println(F("============================================================"));
}

// Helper function to keep the table columns aligned by adding spaces
void printPadded(unsigned long val) {
  if (val < 1000) Serial.print(" ");
  if (val < 100)  Serial.print(" ");
  if (val < 10)   Serial.print(" ");
  Serial.print(val);
}



void loop() {
  if (trigger) { // switch state: no light reaching sensor after a period of light reaching the sensor
    if (!timing) {
      timing = true;
      startT = millis();
      Serial.println(F(" >>> Timing Started..."));
    } else if (periodCount < counts) { // Record period only if the array is not full
      stopT = millis();
      deltaT = stopT - startT;

      // sanity check / automatic reset
      if (deltaT > sanityValue){ 
        // Reset logic: discard previous measurements if user waited too long
        periodCount = 0; 
        startT = stopT;  
        Serial.println(F("------------------------------------------------------------"));
        Serial.println(F(" !!! AUTO-RESET: Gap > 5s. Measurements discarded.       !!!"));
        Serial.println(F("------------------------------------------------------------"));
      } else {
        periods[periodCount] = deltaT;
        periodCount++; 
        
        // Print Table Row
        Serial.print(F(" #"));
        if(periodCount < 10) Serial.print("0"); // Alignment for single digits
        Serial.print(periodCount);
        Serial.print(F(" |  "));
        
        printPadded(deltaT); // Align the time value
        
        Serial.print(F(" ms   |  ["));
        
        // Visual Progress Bar
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
        
        Serial.println(F("============================================================"));
        Serial.print(F(" RESULT: Average Period = "));
        Serial.print(average * 2); // Calculated average * 2 as per original logic
        Serial.println(F(" ms"));
        Serial.println(F("============================================================\n"));
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