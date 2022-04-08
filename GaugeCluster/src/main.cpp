#include <Arduino.h>
#include "OilPressureGauge.h"
#include "FuelGauge.h"
#include "WaterTempGauge.h"
#include "VoltGauge.h"
#include "Speedometer.h"
#include "Tach.h"
#include "DataDisplay.h"

#define RESET 10

const byte numChars = 34;
char receivedChars[numChars]; // Format is "<speed>,<mileage>,<rpm>,<fuel>,<oil>,<water>,<volts>\n"
                              // max          999,9999999,9999,999,99.99,999,99
boolean newData = false;

OilPressureGauge oilPressureGauge;
FuelGauge fuelGauge;
WaterTempGauge waterTempGauge;
VoltGauge voltGauge;
Speedometer speedometer;
Tach tachometer;

void recvWithEndMarker();
void displayValues();

void setup () {
  Serial.begin(9600);
  digitalWrite(RESET, HIGH);
  speedometer.setup();
  tachometer.setup();
  oilPressureGauge.setup();
  waterTempGauge.setup();
  fuelGauge.setup();
  voltGauge.setup();    
}

void loop() {
  recvWithEndMarker();
  displayValues();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read(); 
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void displayValues() {
  if (newData == true) {
    char * strtokIndx; // this is used by strtok() as an index
  
    strtokIndx = strtok(receivedChars,",");
    speedometer.indicateSpeed(atoi(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    speedometer.indicateMileage(atol(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    tachometer.indicateRPM(atoi(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    fuelGauge.indicateFuel(atoi(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    oilPressureGauge.indicatePsi(atof(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    waterTempGauge.indicateTemp(atoi(strtokIndx));

    strtokIndx = strtok(NULL, ",");
    voltGauge.indicateVoltage(atoi(strtokIndx)); 

    newData = false;
  }
}