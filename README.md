# Photogate

## project description

The photogate project is an Arduino compatible PCB, designed to take precise measurements of for example a pendulum's period or the speed of a miniature car in a test rig. Since the photogate project is driven by a school project, some screenshots and component workings will be included in this repository.

### The PCB

The U-shaped PCB most importantly features a 3 pin connector. From left to right the pins need to be connected to `GND`, `analog input` & `+5V` on your Arduino. There are two mounting holes in the PCB, which could be used to attach the photogate to a 3d printed mounting piece (which is not yet developed). lastly every PCB features a unique QR-code, for easy identification of the PCB's

A screenshot of the schematics can by found in the `references` folder

# Scripts

Currently the photogate project features 2 scripts:

## photogate.ino

This script uses a single photogate pcb to measure the time between two triggers.
For demonstration purposes, the internal arduino led is turned on in between the start and stop trigger.
A picture of the hardware setup is presented below. By default, the sensorpin should be connected to the Arduino's `A0` pin.

`insert picture`



## photogate_pendulum

This script is used to measure the period of a pendulum using a single photogate. This is done by taking the average of 10 measured periods. Currently, the script features a sanity check which warns the user when a period larger than 5s is included in the average. This is done because it's very likely that the user adjusted the pendulum setup.

In the near future this script will be updated to automatically restart its measurements after a given time interval. 

A picture of the hardware setup is presented below. By default, the sensorpin should be connected to the Arduino's `A0` pin.

`insert picutere`
