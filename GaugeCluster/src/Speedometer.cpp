/*
    Speedometer/Odometer update class.
    The below code was influenced by the work of Nick Gammon (http://www.gammon.com.au/timers)

    Interrupts are used to measure the pulses received on pin D5 of the arduino. Timer 1 counts
    the rising edges of the signal coming from a hall effect sensor. Timer 2 triggers an interrupt to 
    inspect the pulse count on 4ms intervals. Given a known number of pulses per distance traveled, the
    speed can be deduced. The position of the odometer and speedometer steppers are then updated on the 
    main program loop interval.
*/
#include <Arduino.h>
#include "Speedometer.h"

double speed;
double distanceTraveledBuffer;
double tickCount;

//******************************************************************
//  Timer2 Interrupt Service is invoked by hardware Timer 2 every 4 ms = 250 Hz
//  16Mhz / 256 / 250 = 250 Hz

ISR (TIMER2_COMPA_vect) {
  // Only evaluate pulse count on a 500ms interval.
  if (++tickCount < 125) {
    return;
  }

  unsigned int pulses = TCNT1;

  // Calculate derived values.
  double distanceTraveled = (pulses / PULSES_PER_FOOT);
  distanceTraveledBuffer += distanceTraveled;

  // convert feet/half-second to MPH.
  speed = distanceTraveled * 1.364;

  // Reset counters.
  TCNT1 = 0;
  TCNT2 = 0;
  tickCount = 0;
}

Speedometer::Speedometer() {
}

void Speedometer::setup() {
  // Intialize Timer 2 frequency divider.
  tickCount = 0;

  // reset Timer 1 and Timer 2
  TCCR1A = 0;             
  TCCR1B = 0;              
  TCCR2A = 0;
  TCCR2B = 0;

  // Timer 1 - counts events on pin D5
  TIMSK1 = bit (TOIE1);   // interrupt on Timer 1 overflow

  // Timer 2 - gives us our 1 ms counting interval
  // 16 MHz clock (62.5 ns per tick) - prescaled by 256
  //  counter increments every 16 µs. 
  // So we count 250 of them, giving exactly 4000 µs (4 ms)
  TCCR2A = bit (WGM21) ;
  OCR2A  = 249;

  // Timer 2 - interrupt on match (ie. every 1 ms)
  TIMSK2 = bit (OCIE2A);   // enable Timer2 Interrupt

  TCNT1 = 0;      // Both counters to zero
  TCNT2 = 0;     

  // Reset prescalers
  GTCCR = bit (PSRASY);        // reset prescaler now
  // start Timer 2
  TCCR2B =  bit (CS21) | bit (CS22) ;  // prescaler of 256
  // start Timer 1
  // External clock source on T1 pin (D5). Clock on rising edge.
  TCCR1B =  bit (CS10) | bit (CS11) | bit (CS12);
}

void Speedometer::loop() {
  if (distanceTraveledBuffer > 0)
  {
    double distanceTraveled = distanceTraveledBuffer;
    distanceTraveledBuffer = 0;
    incrementOdometer(distanceTraveled);
  }

  indicateSpeed(speed);
}

void Speedometer::incrementOdometer(double distanceTraveled) {
  // Update odometer stepper position.
}

void Speedometer::indicateSpeed(double speed) {
  // Update speedometer stepper position
}