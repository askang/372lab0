/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, waitPress, waitTimer, waitRelease, waitChoose, debounce
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = waitPress; //start in this state
volatile int ledcurrent = 0; //keeps up with what led is on currently
volatile int counter = 0; //counter for timer

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        switch(state){
            case waitPress:
                
                if (ledcurrent == 0) 
                {
                    turnOnLED(1); //turn on led 1 at beginning
                    ledcurrent = 1;
                }
                
                if (PORTDbits.RD6 == 0) //button pressed
                {
                    T1CONbits.ON = 0;                
                    TMR1 = 0;
                    counter = 0;
                    state = debounce;
                }
                else 
                {
                    state = waitPress;
                }
                
                break;
               
            case debounce:
                delayMs(200);
                T1CONbits.ON = 1;
                state = waitTimer;
                break;
                
            case waitTimer:
                if (PORTDbits.RD6 == 1 & counter < 2)
                {
                    T1CONbits.ON = 0;
                    state = waitChoose;
                }
                
                else if (PORTDbits.RD6 == 1 & counter >= 2)
                {
                    T1CONbits.ON = 0;
                    state = waitRelease;
                }
                
                while (PORTDbits.RD6 == 0)//button is pressed still
                {
                    state = waitTimer;
                }
                break;
                
            case waitChoose: //going forward
                delayMs(200);
                if (ledcurrent == 1) //if led 1 is on 
                {
                    //ledcurrent = 2;
                    state = led2;
                }
                else if (ledcurrent == 2) //if led 2 is on
                {
                   // ledcurrent = 3;
                    state = led3;
                }
                else //if led 3 is on
                {
                   // ledcurrent = 1;
                    state = led1;
                }
                break;
                
            case waitRelease: //going backwards
                delayMs(200);
               // while (PORTDbits.RD6 == 1)//button is released
               // {
                   // T1CONbits.ON = 0;//timer is on 
                if (ledcurrent == 1) //if led 1 is on 
                {
                    //ledcurrent = 3;
                    state = led3;
                }
                else if (ledcurrent == 2) //if led 2 is on
                {
                    //ledcurrent = 1;
                    state = led1;
                    
                }
                else //if led 3 is on
                {
                    //ledcurrent = 2;
                    state = led2;
                }
                //}
                
                /*else 
                {
                    state = waitRelease;
                }*/
                break;
                
            case led1:
                turnOnLED(1);
                ledcurrent = 1;
                state = waitPress;
                break;
                
            case led2:
                turnOnLED(2);
                ledcurrent = 2;
                state = waitPress;
                break;
                
            case led3:
                turnOnLED(3);
                ledcurrent = 3;
                state = waitPress;
                break;    
        }
   
}
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0; //set flag down
    counter = counter + 1;
}

void __ISR(_TIMER_2_VECTOR, IPL4SRS) _T2Interrupt(){
    IFS0bits.T2IF = 0; //set flag down
}