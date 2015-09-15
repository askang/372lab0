/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
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
    led1, led2, led3, waitPress, waitTimer, waitRelease, waitChoose
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = waitPress; //start in this state
volatile int ledcurrent = 0; //keeps up with what led is on currently

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
                //resets 2 sec timer
                initTimer1();
                initTimer2();
                if (ledcurrent == 0) 
                {
                    turnOnLED(1);
                }
                //if (IFS1bits.CNDIF == 1) //button pressed
                if (PORTDbits.RD6 == 1)
                {
                    T1CONbits.ON = 1;
                    state = waitTimer;
                }
                else 
                {
                    state = waitPress;
                }
                break;
                
            case waitTimer:
                if (PORTDbits.RD6 == 0)
                //if (IFS1bits.CNDIF == 0)
                {
                    state = waitChoose;
                }
                
                //else if (IFS1bits.CNDIF == 1 && )
                //{
                //    state = waitRelease;
                //}
                else 
                {
                    state = waitTimer;
                }
                break;
                
            case waitChoose: //going forward
                delayMs(200);
                if (ledcurrent == 1) //if led 1 is on 
                {
                    state = led2;
                }
                else if (ledcurrent == 2) //if led 2 is on
                {
                    state = led3;
                }
                else //if led 3 is on
                {
                    state = led1;
                }
                break;
                
            case waitRelease: //going backwards
                delayMs(200);
                if (ledcurrent == 1) //if led 1 is on 
                {
                    state = led3;
                }
                else if (ledcurrent == 2) //if led 2 is on
                {
                    state = led1;
                }
                else //if led 3 is on
                {
                    state = led2;
                }
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
   
    return 0;
}
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0; //set flag down
    if (state == waitPress && PORTDbits.RD6 == 1)//IFS1bits.CNDIF == 0)
    {
        state = waitRelease; //this means that the timer has expired for 2 sec?
    }
}