# SinLEDs_AVR
Pulse LEDs in a Sinewave using ATMega AVR! This code uses Timer0 to generate a PWM "sine wave" on PD5 and PD6, using OC0A and OC0B in non-inverting and inverting mode respectively, with the OCRs being updated every 300 milliseconds with the next value in a uint8_t array lookup table for the sine wave. Don't forget to update the #defines at the beginning (and update the Makefile) with your chip (default: ATMega328/P) and clock (default: 1MHz).

[![Build Status](https://travis-ci.org/bithakr/SineLEDs-AVR.svg?branch=master)](https://travis-ci.org/bithakr/SineLEDs-AVR)
