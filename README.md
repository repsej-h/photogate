# Photogate

## project description





# Scripts

Currently the photogate project features 2 scripts

## photogate.ino

This script uses a single photogate pcb to measure the time between two triggers.
For demonstration purposes, the internal arduino led is turned on in between the start and stop trigger.
A picture of the hardware setup is presented below. By default, the sensorpin should be connected to the Arduino's `A0` pin.

`insert picture`



## photogate_pendulum

This script is used to measure the period of a pendulum. This is done by taking the average of 10 measured periods. Currently, the script features a sanity check which warns the user when a period larger than 5s is included in the average. This is done because it's very likely that the user adjusted the pendulum setup.

In the near future this script will be updated to automatically restart its measurements after a given time interval. 

A picture of the hardware setup is presented below. By default, the sensorpin should be connected to the Arduino's `A0` pin.

`insert picutere`
