// sensorpins
int pins[] = {2, 3}; // Add all sensor pins here.
const int pinsLength = sizeof(pins) / sizeof(pins[0]); // Number of pins - please add a array.length function

// Distances between consecutive photogates in cm.
// For N photogates, there are N-1 intervals.
unsigned int distances[pinsLength - 1] = {100}; // Example: 100cm between pin 2 and pin 3. Adjust if you add more pins/intervals.

// Store millis() timestamp when each photogate is triggered.
volatile unsigned long times[pinsLength];

// Flag set true when all photogates are triggered.
volatile bool trigger = false;

// Tracks how many photogates have been triggered.
volatile int counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Photogate system initializing...");

  // Set up sensors and attach interrupts.
  for (int i = 0; i < pinsLength; i++) {
    pinMode(pins[i], INPUT);
    attachInterrupt(digitalPinToInterrupt(pins[i]), triggered, RISING);
    Serial.print("Attached interrupt to Pin: ");
    Serial.println(pins[i]);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Photogate system ready.");
}

void loop() {
  if (trigger) {
    // Disable interrupts to safely copy 'times' array.
    noInterrupts();
    unsigned long localTimes[pinsLength];
    for (int i = 0; i < pinsLength; i++) {
      localTimes[i] = times[i];
    }
    interrupts(); // Re-enable interrupts.

    // Calculate speeds for each interval.
    for (int i = 1; i < pinsLength; i++) {
      unsigned long intervalTimeMs = localTimes[i] - localTimes[i - 1];

      if (intervalTimeMs > 0) {
        unsigned int intervalDistanceCm = distances[i - 1];
        float speedMps = (float)intervalDistanceCm / intervalTimeMs * 10.0;

        Serial.print("Speed between gate ");
        Serial.print(i);
        Serial.print(" and gate ");
        Serial.print(i + 1);
        Serial.print(":\t");
        Serial.print(speedMps, 3);
        Serial.println(" m/s");
      } else {
        Serial.print("Error: Interval time for gate ");
        Serial.print(i);
        Serial.println(" was zero.");
      }
    }

    Serial.println("--- Measurement Complete ---");

    // Reset for the next measurement.
    trigger = false;
    counter = 0;
  }

  delay(10);
}

// Interrupt Service Routine (ISR)
void triggered() {
  if (counter < pinsLength) {
    times[counter] = millis();
    counter++;
  }

  if (counter == pinsLength) {
    trigger = true;
  }
}
