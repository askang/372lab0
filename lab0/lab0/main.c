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
    led1, led2, led3, waitPress, waitTimer, waitRelease, wait2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int count; //counts the timer for delay
volatile stateType state = waitPress; //start in this state

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
                if (IFS1bits.CNDIF == 1)
                {
                    state = waitTimer;
                }
                else 
                {
                    state = waitPress;
                }
                break;
                
            case waitTimer:
                
                break;
                
            case wait2:
                
                break;
                
            case waitRelease:
                
                break;
                
            case led1:
                turnOnLED(1);
                state = waitPress;
                break;
                
            case led2:
                turnOnLED(2);
                state = waitPress;
                break;
                
            case led3:
                turnOnLED(3);
                state = waitPress;
                break;    
        }
        
    
    
    return 0;
}

//void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(){
    //*need this or not?*