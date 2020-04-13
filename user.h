
#include "common.h"

#include <avr/sleep.h>
#include <stdio.h>

#include "uart.h"
#include "lib_io/digitalAnalog.h"
#include "lib_io/i2cMultiMaster.h"
#include <util/delay.h>
#include <avr/wdt.h>

//#include <util/delay.h>

#ifndef USER_H
#define	USER_H

#define Leerbit(bit,byte) (byte&(1<<bit))>>(bit) 
#define Changebit(byte, pin) byte ^= _BV(pin)

#define Diferenciabit(bit,byte1,byte2) ~((byte&(1<<bit))>>(bit) && (byte2&(1<<bit))>>(bit))



#define DigitalDON(pin) PORTD |= _BV(pin)
#define DigitalDOFF(pin) PORTD &= ~_BV(pin)
#define DigitalDChange(pin) PORTD ^= _BV(pin)
#define DigitalDRead(pin) (PIND&(1<<pin))>>(pin) 

#define DigitalBON(pin) PORTB |= _BV(pin)
#define DigitalBOFF(pin) PORTB &= ~_BV(pin)
#define DigitalBChange(pin) PORTB ^= _BV(pin)
#define DigitalBRead(pin) (PINB&(1<<pin))>>pin 

#define DigitalCON(pin) PORTC |= _BV(pin)
#define DigitalCOFF(pin) PORTC &= ~_BV(pin)
#define DigitalCChange(pin) PORTC ^= _BV(pin)
#define DigitalCRead(pin) (PINC&(1<<pin))>>pin 
//Tareas
void InitSoftware();
void InitHardware();

void WDT_off(void);
void WDT_Prescaler_Change(void);

void watchdogSetup(void);

#endif

    



