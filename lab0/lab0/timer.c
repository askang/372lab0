/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"
#define time 1.0
#define freq 625,000


void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1 = 0; //initializes the timer, clears it
    //PR1 = ((freq)*(time)/256)-1; //initialize PR
    PR1 = 1221*2; //*does this make it a 1 sec timer?*
    T1CONbits.TCS = 0; //setting the oscillator
    T1CONbits.TCKPS = 3; //Initializes prescalar to 256
    IEC0bits.T1IE = 1; //enable the interrupt
    IFS0bits.T1IF = 0; //puts the flag down
    IPC1bits.T1IP = 3; //configure Interrupt Priority
    //T1CONbits.ON = 1; //turns on timer
}

void initTimer2(){
    //TODO: Initialize Timer 2.
    TMR2 = 0; //initializes timer 2
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}

void delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0; //put down flag?
    T2CONbits.ON = 1; //turns timer on
    while(IFS0bits.T2IF == 0)
    {
    //do nothing    
    }
    T2CONbits.ON = 0;
}