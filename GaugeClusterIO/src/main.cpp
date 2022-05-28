#include <Arduino.h>
#include "OilPressureGauge.h"
#include "FuelGauge.h"
#include "WaterTempGauge.h"
#include "VoltGauge.h"
#include "Speedometer.h"
#include "mcp2515_can.h"

#define CAN_2515

const int SPI_CS_PIN = 15;
const int CAN_INT_PIN = 2;

OilPressureGauge oilPressureGauge;
FuelGauge fuelGauge;
WaterTempGauge waterTempGauge;
VoltGauge voltGauge;
Speedometer speedometer;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

void setup () {
  speedometer.setup();   
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
    delay(100);
  }
}

typedef struct {
  uint8_t volts;
  uint8_t water;
  uint8_t fuel;
  uint8_t oil;
  uint8_t paddding[4];
} SmallGauges;

typedef struct {
  uint8_t speed;
  uint16_t rpm;
  uint32_t mileage;
  uint8_t padding;
} LargeGauges;

void loop () {
  LargeGauges largeGauges;
  SmallGauges smallGauges;

  speedometer.loop();
  largeGauges.speed = speedometer.getSpeed();
  largeGauges.rpm = speedometer.getRPM();
  largeGauges.mileage = speedometer.getCurrentMileage();
  smallGauges.oil = oilPressureGauge.getValue();
  smallGauges.water = waterTempGauge.getValue();
  smallGauges.fuel = fuelGauge.getValue();
  smallGauges.volts = voltGauge.getValue();

  CAN.sendMsgBuf(0x4d1, 0, 8, (byte*)&smallGauges);
  CAN.sendMsgBuf(0x3e9, 0, 8, (byte*)&largeGauges);
}