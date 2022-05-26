#include <Arduino.h>
#include <SPI.h>
#include "OilPressureGauge.h"
#include "FuelGauge.h"
#include "WaterTempGauge.h"
#include "VoltGauge.h"
#include "Speedometer.h"
#include "Tach.h"
#include "DataDisplay.h"
#include "mcp2515_can.h"

#define RESET 10
#define CAN_2515

const int SPI_CS_PIN = 15;
const int CAN_INT_PIN = 2;

OilPressureGauge oilPressureGauge;
FuelGauge fuelGauge;
WaterTempGauge waterTempGauge;
VoltGauge voltGauge;
Speedometer speedometer;
Tach tachometer;

mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];

void displayValues();

void MCP2515_ISR() {
    flagRecv = 1;
}

void setup () {
  attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), MCP2515_ISR, FALLING); // start interrupt
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
    delay(100);
  }

  digitalWrite(RESET, HIGH);
  speedometer.setup();
  tachometer.setup();
  oilPressureGauge.setup();
  waterTempGauge.setup();
  fuelGauge.setup();
  voltGauge.setup();    
}

void loop() {
  if (flagRecv) {
    flagRecv = 0;  

    while (CAN_MSGAVAIL == CAN.checkReceive()) {
      CAN.readMsgBuf(&len, buf);
      int id = CAN.getCanId();

      switch (id) {
        case 0x0c8:
        {
          int voltage = buf[0];
          voltGauge.indicateVoltage(voltage);
          break;
        }
        case 0x0c9:
        {
          // Tach
          int rpm = buf[2] << 8 | buf[3];
          tachometer.indicateRPM(rpm);
          break;
        }
        case 0x4d1:
        {
          // Oil Pressure / Fuel
          int oil = buf[3] * 0.766;
          int fuel = buf[6] * 100 / 255;
          oilPressureGauge.indicatePsi(oil);
          fuelGauge.indicateFuel(fuel);
          break;
        }
        case 0x4c1:
        {
          // Water Temp
          int temp = ((buf[3] - 40) * 1.8) + 32;
          waterTempGauge.indicateTemp(temp);
          break;
        }
        case 0x3e9:
        {
          // Speedometer
          long mileage = (long)buf[0] << 24 | (long)buf[1] << 16 | (long)buf[2] << 8 | (long)buf[3];
          int speed = (buf[5] << 8 | buf[6]) / 100;
          speedometer.indicateSpeed(speed);
          speedometer.indicateMileage(mileage);
          break;
        }
        default:
          break;
      }
    }
  }
}