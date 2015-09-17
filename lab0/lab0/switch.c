/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>
#include "switch.h"

#define OUTPUT 0
#define INPUT 1

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;
   // CNCONDbits.ON = 1;
    CNPUDbits.CNPUD6 = 1;
}