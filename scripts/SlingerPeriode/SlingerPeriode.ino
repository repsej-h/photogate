#define SensorPin A0

// variables for sensor state
int SensorValue = 0;
int preSensorValue = 0;

//variables for time interval
bool timing = false;
unsigned long deltaT = 0;
unsigned long startT = 0;
unsigned long stopT = 0;
const int threshold = 200; // can be adjusted according to light levels; remove // on line 26 - 27 to print light level to console



int periodCount = 0; // Keep track of how many periods have been recorded
float average = 0;  
const int counts = 10; // amout of periods before calculating the average
unsigned long periods[counts];

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
    } else if (periodCount < counts) { // Record period only if the array is not full
      stopT = millis();
      deltaT = stopT - startT;

      Serial.print("Meting ");
      Serial.print(periodCount + 1);
      Serial.print("\t");

      periods[periodCount] = deltaT;
      startT = stopT;
      periodCount++; 

      if(deltaT < 2000){
        Serial.print("Time Elapsed: ");
        Serial.print(deltaT);
        Serial.println(" ms");
      }

      // Calculate and print the average only after x periods
      if (periodCount == counts) {
        unsigned long sum = 0;
        for (int i = 0; i < periodCount; i++) {
          if (periods[i] < 2000){
            sum += periods[i];
          }
          
        }

        average = (float)sum *2 / (periodCount*1000);
        Serial.print("Periode (after 10 periods): ");
        Serial.print(average,2);
        Serial.println(" s \n\n\n\n");
        

        delay(5000);
        // Reset the period count for the next set of x periods
        periodCount = 0;

      }
    }
  }

  preSensorValue = SensorValue; // Update the previous sensor value
  delay(10); // Small delay to avoid rapid readings
}
/*



Denk je dat de slingerperiode (de tijd voor één heen- en weergaande beweging) veel beïnvloed wordt door de hoogte van waarop de slinger losgelaten wordt?
DOE de test hier. Laat de slinger los vanaf een welbepaalde hoogte. De opstelling voert 10 metingen uit en geeft je het gemiddelde.
HERHAAl de test, maar laat nu log vanaf een grotere of kleinere hoogte.
MAAK de hoek nooit groter dan 70°.


*/


