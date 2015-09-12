/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#define time 1.0
#define freq 625,000


void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1 = 0; //initializes the timer, clears it
    PR1 = ((freq)*(time)/256)-1; //initialize PR
    T1CONbits.TCS = 0; //setting the oscillator
    T1CONbits.TCKPS = 4; //Initializes prescalar to 256
    IEC0bits.T1IE = 1; //enable the interrupt
    IFS0bits.T1IF = 0; //puts the flag down
    IPC1bits.T1IP = 3; //configure Interrupt Priority
    T1CONbits.ON = 1; //turns on timer
}

initTimer2(){
    //TODO: Initialize Timer 2.
    TMR2 = 0; //initializes timer 2
    
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
}