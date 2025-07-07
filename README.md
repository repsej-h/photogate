![Watch the video](https://github.com/user-attachments/assets/5a69227e-c142-498d-8717-64d389a69f4b)

# Photogate

## project description

The photogate project is an Arduino compatible PCB, designed to take precise measurements of for example a pendulum's period or the speed of a miniature car in a test rig. Since the photogate project is driven by a school project, some screenshots and component workings will be included in this repository.

### The PCB

The U-shaped PCB most importantly features a 3 pin connector. From left to right the pins need to be connected to `GND`, `digital interrupt` & `+5V` on your Arduino. There are two mounting holes in the PCB, which could be used to attach the photogate to a 3d printed mounting piece (which is not yet developed). Last every PCB features a unique QR-code, for easy identification of the PCB's

A screenshot of the schematics can by found in the `references` folder

### Components

Only 5 components are placed on the PCB. Starting off with `R1` and `R2`, these are 220 $\Omega$ and 2000 $\Omega$ resistors respectively. These are placed on the board as 0805 SMD **resistors**. Next is a 3 pin connector with a 90 degree bend, making the photogate easily compatible with a breadboard. Alternatively, when mounting the PCB, female to male Arduino jumper wires can be used. Next we have the more vital components. The first one is the 940 nm LED, which constantly emits light when connected to a power source. Finally a 940 nm `insert type`phototransistor either blocks or allows electricity to flow through the circuit. This flow is then read by an analog Arduino pin.

# Scripts

Currently the photogate project features 3 scripts:

## photogate.ino

This script uses a single photogate pcb to measure the time between two triggers.
For demonstration purposes, the internal arduino led is turned on in between the start and stop trigger.
A picture of the hardware setup is presented below. In order for the interrupt to work, the `SensorPin` **has to be wired** to the `digital 2 / 3` pin on an Arduino Uno.

<img src="https://github.com/user-attachments/assets/0700b60f-fb24-4033-8771-118e4cd9fd5e" width="579" height="771">

## photogate_pendulum.ino

This script is used to measure the period of a pendulum using a single photogate. This is done by taking the average of 10 measured periods. Currently, the script features a sanity check which warns the user when a period larger than 5s is included in the average. This is done because it's very likely that the user adjusted the pendulum setup.

In the near future this script will be updated to automatically restart its measurements after a given time interval. 

A picture of the hardware setup is presented below. In order for the interrupt to work, the `SensorPin` **has to be wired** to the `digital 2 / 3` pin on an Arduino Uno.

<img src="https://github.com/user-attachments/assets/0700b60f-fb24-4033-8771-118e4cd9fd5e" width="579" height="771">

## SlingerPeriode.ino

This script has the same functionality as the `photogate_pendulum.ino` script, but has been modified to be used on a college information day. Most important changes are reformatting the script's output and adding instructions for the demo in de code documentation. Also, this script is based on a older version of the pendulum script and still uses analog readings. Theirfore connect the `SensorPin` to pin `A0`!

## speed_measurement.ino

This script is designed to calculate the speed of an object traveling through multiple photogates. Unlike previous projects, an array of photogates is used to collect timestamps along the path of the object. This data is used to calculate the speed of the object for each interval.

> note: since old Arduino Uno's only feature 2 interupt pins, only 2 photogates can be used. Please consult [Arduino docs](https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/) to check if your Arduino model can support more than 2 interrupts.

### Configure the script

By default the script is configured to work with two photogates, connected to digital pins `2` & `3`.  In this case, simply input the distance in cm between the 2 gates right here: `unsigned int distances[pinsLength - 1] = {100};`

When adding more photogates, first add your pins into the `int pins[]` seperatedby comma's. Next plug in the distances between the gates, also separated by comma's into `unsigned int distances[pinsLength - 1]` and you are good to go. 

Until now the script has been tested with up to 3 photogates. Also note that the script doesn't bother in which order gates get triggered. This means that a set up can be used in both directions. The end user needs to interpret which is gate one, two, etc based on the object's trajectory.
