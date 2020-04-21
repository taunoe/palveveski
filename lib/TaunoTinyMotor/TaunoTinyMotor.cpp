#include "Arduino.h"
#include <util/delay.h>
#include "TaunoTinyMotor.h"


// constructor
TaunoTinyMotor::TaunoTinyMotor(uint8_t pwm_pin, uint8_t b_pin)
{
    _pwm_pin = pwm_pin;
    _b_pin = b_pin;
}

void TaunoTinyMotor::begin(uint32_t freq){
    _freq = freq;
    /* Set up pins */
    pin_output(_pwm_pin);
    pin_input(_b_pin);

    /* PWM init */
    // TCCR == Timer/Counter Control Register
    // control the Output Compare pin (OC0B) behavior

    // set timer mode to FAST PWM
    TCCR0A |= _BV(WGM01)|_BV(WGM00);
    // connect PWM signal to pwm pin (OC0A => PB0)
    TCCR0A |= _BV(COM0A1); 
    
    /* */
    pwm_set_frequency(_freq);

    _is_working = 0;
}

void TaunoTinyMotor::go(uint8_t direction, uint8_t speed){ //uint8_t duty
    if (direction == CCW) {
        if (speed > 9) { //9
            enable();
            OCR0A = 255; // Max
        }
        else if (speed > 0) {
            enable();
            OCR0A = 160 + 9 * speed;
        }
        else { 
            disable();
            OCR0A = 128; // stop 
        }
        
    }
    else if (direction == CW) {
        if (speed > 9) {
            enable();
            OCR0A = 0; // Max speed
        }
        else if (speed > 0) {
            enable();
            OCR0A = 90 - 9 * speed;
        }
        else { // speed == 0
            disable();
            OCR0A = 128; // stop
        }
    }
    
}

/* Private functions*/

void TaunoTinyMotor::disable() {
    if (_is_working == 1)
    {
        //pwm_stop();
        pin_input(_pwm_pin);
        _is_working = 0;
    }
}

void TaunoTinyMotor::enable() {
    if (_is_working == 0)
    {
        //pwm_set_frequency(_freq);
        pin_output(_pwm_pin);
        _is_working = 1;
    }
}

void TaunoTinyMotor::pwm_stop() //?? ei tööta
{
    // stop the timer
    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); 
}

void TaunoTinyMotor::pwm_set_frequency(uint32_t freq)
{
    /*  When timer is set to Fast PWM Mode, the freqency can be
        calculated using equation: F = F_CPU / (N * 256) 
        Posible frequencies (@1.2MHz):
        -> F(N_1) = 4.687kHz
        -> F(N_8) = 585Hz
        -> F(N_64) = 73Hz
        -> F(N_256) = 18Hz
        -> F(N_1024) = 4Hz */

    // set prescaler
    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | freq; 
}

void TaunoTinyMotor::pin_output(uint8_t pin)
{
    // set pin as OUTPUT
    DDRB |= (1 << pin);
}

void TaunoTinyMotor::pin_input(uint8_t pin)
{
    // set pin as INPUT
    DDRB &= ~(1 << pin);
}