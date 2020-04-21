#include <Arduino.h>

#include "TaunoTinyMotor.h"

const int PWM_PIN = PB0;
const int B_PIN = PB1;

TaunoTinyMotor motor(PWM_PIN, B_PIN);

/*
 * PB1 - b
 * PB0 - pwb
 */

int main(void)
{

  //uint8_t duty = 0;
  motor.begin();
  
  /* loop */
  while (1)
  {

    for (int i=0; i<20; ++i) {
      motor.go(CCW, 5);
      _delay_ms(100);
    }
    
    for (int i=0; i<60; ++i) {
      motor.go(CCW, 0);
      _delay_ms(100);
    }
    /////////////////////////////////

    for (int i=0; i<20; ++i) {
      motor.go(CW, 5);
      _delay_ms(100);
    }

    for (int i=0; i<60; ++i) {
      motor.go(CW, 0);
      _delay_ms(100);
    }

  }

  return 0;
}