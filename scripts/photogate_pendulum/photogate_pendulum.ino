#define SensorPin A0 // pin where we connected the sensor

// variables for sensor state
int SensorValue = 0;
int preSensorValue = 0;

//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 27 - 28 to print light level to console
const unsigned int sanityValue = 5000; // if in this interval no messurements are recored, the user gets warned that the following average may contain inorrect messuremets

unsigned long periods[10];
int periodCount = 0; // Keep track of how many periods have been recorded
float average = 0;  
int counts = 10; // amout of periods before calculating the average

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  SensorValue = analogRead(SensorPin); // Read the current value of the sensor

  // Print the light level for debugging or adjustment of the threshold
  // Serial.print("Sensor Value: ");
  // Serial.println(SensorValue);

  if (SensorValue > threshold && preSensorValue < threshold) { // switch state: no light reaching sensor after a period of light reaching the sensor
    if (!timing) {
      timing = true;
      startT = millis();
      Serial.println("Sensor triggered");
    } else if (periodCount < counts) { // Record period only if the array is not full
      stopT = millis();
      deltaT = stopT - startT;

      // sanity check
      if (deltaT > sanityValue){ 
        startT = stopT;
        Serial.println("WARNING: Reading to large and did not pass the sanity check!");
        Serial.println("Please consider ignoring the following average, since it may contain messurements from previouse exeperiments!");
      } else {
        Serial.print("Sensor triggered, period ");
        Serial.print(periodCount + 1);
        Serial.println(" recorded");
        periods[periodCount] = deltaT;
        startT = stopT;
        periodCount++; 
      }

      Serial.print("Time Elapsed: ");
      Serial.println(deltaT);

      // Calculate and print the average only after x periods
      if (periodCount == counts) {
        unsigned long sum = 0;
        for (int i = 0; i < periodCount; i++) {
          sum += periods[i];
        }

        average = (float)sum / periodCount;
        Serial.print("Average period (after 10 periods): ");
        Serial.println(average*2);

        // Reset the period count for the next set of x periods
        periodCount = 0;
      }
    }
  }

  preSensorValue = SensorValue; // Update the previous sensor value
  delay(10); // Small delay to avoid rapid readings
}