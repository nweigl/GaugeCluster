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

typedef struct {
  uint8_t volts;
  uint8_t water;
  uint8_t fuel;
  uint8_t oil;
  uint8_t paddding[4];
} SmallGauges, *PSmallGauges;

typedef struct {
  uint8_t speed;
  uint16_t rpm;
  uint32_t mileage;
  uint8_t padding;
} LargeGauges, *PLargeGauges;

void loop() {
  if (flagRecv) {
    flagRecv = 0;  

    while (CAN_MSGAVAIL == CAN.checkReceive()) {
      CAN.readMsgBuf(&len, buf);
      int id = CAN.getCanId();

      switch (id) {
        case 0x4d1:
        {
          // Oil Pressure / Fuel / Water / Voltage
          PSmallGauges gauges = (PSmallGauges)buf;
          int oil = gauges->oil;
          int fuel = gauges->fuel;
          int temp = gauges->water;
          int voltage = gauges->volts;
          voltGauge.indicateVoltage(voltage);
          waterTempGauge.indicateTemp(temp);
          oilPressureGauge.indicatePsi(oil);
          fuelGauge.indicateFuel(fuel);
          break;
        }
        case 0x3e9:
        {
          // Speedometer / Tach
          PLargeGauges gauges = (PLargeGauges)buf;
          long mileage = gauges->mileage;
          int speed = gauges->speed;
          int rpm = gauges->rpm;
          speedometer.indicateSpeed(speed);
          speedometer.indicateMileage(mileage);
          tachometer.indicateRPM(rpm);
          break;
        }
        default:
          break;
      }
    }
  }
}