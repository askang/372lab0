/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "leds.h"

#define OUTPUT 0
#define INPUT 1

void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
    
    //use LED1 and LED2 on board 
    //TODO: change this to external LEDs TRD1, TRD2
    
    
    TRISDbits.TRISD0 = OUTPUT; // set led1 as output RUN
    TRISDbits.TRISD1 = OUTPUT; // set led2 as output STOP
    TRISDbits.TRISD2 = OUTPUT;
    
    //turn off all LEDs
    LATDbits.LATD0 = 0; 
    LATDbits.LATD1 = 0; 
    LATDbits.LATD2 = 0;
}

void turnOnLED(int led)
{
    switch (led)  {
            case 1: //turn on LED1
                LATDbits.LATD0 = 1;
                LATDbits.LATD1 = 0;
//                LATDbits.LATD2 = 0;
                break;
            case 2: //turn on LED2
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 1;
//                LATDbits.LATD2 = 0;
                break;
        case 3:
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
//            LATDbits.LATD2 = 1;
    }
}