/*
    TaunoTinyMotor.h - libary for driving motor with pwm
    Created by Tauno Erik
    19.04.2020

    https://blog.podkalicki.com/attiny13-hardware-pwm/
    https://blog.podkalicki.com/attiny13-led-fading-with-delay-function/
    Timer in Fast PWM mode (WGM02:0 = 3, see manual section 11.7.3).
    In this mode, by setting the COM0A1:0 bits to one,
    the compare unit allows generation of PWM waveforms on the AC0A pin (PB0)
    with duty resolution 0..255.
*/
#ifndef TaunoTinyMotor_h
#define TaunoTinyMotor_h

#include "Arduino.h"
#include <util/delay.h>

/* When timer is set to Fast PWM Mode, the freqency can be
calculated using equation: F = F_CPU / (N * 256) 
Posible frequencies (@1.2MHz):
 -> F(N_1) = 4.687kHz
 -> F(N_8) = 585Hz
 -> F(N_64) = 73Hz
 -> F(N_256) = 18Hz
 -> F(N_1024) = 4Hz */
#define N_1    (_BV(CS00))
#define N_8    (_BV(CS01))
#define N_64   (_BV(CS01)|_BV(CS00))
#define N_256  (_BV(CS02))
#define N_1024 (_BV(CS02)|_BV(CS00))

/* motor direction */
#define CW      0x01 // CLOCKWISE
#define CCW     0x02 // COUNTERCLOCKWISE

class TaunoTinyMotor
{
    public:
        // constructor
        TaunoTinyMotor(uint8_t pwm_pin, uint8_t b_pin);
        //
        void begin(uint32_t freq=N_1);
        void go(uint8_t direction, uint8_t speed);
        
    private:
        uint8_t _pwm_pin;
        uint8_t _b_pin;
        uint32_t _freq;
        uint8_t _is_working;

        void disable();
        void enable();
        void pwm_stop();
        void pwm_set_frequency(uint32_t freq); // N_1
        void pin_output(uint8_t pin);
        void pin_input(uint8_t pin);
};

#endif