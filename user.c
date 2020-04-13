#include <avr/pgmspace.h>

#include "user.h"
#include <string.h>
#include <inttypes.h>

extern uint8_t indTX;
extern uint8_t indRX, lenghTX;
extern char TXDATA_UART0[100];
extern char RXDATA_UART0[100];

void InitSoftware()
{
    char str[9];
    sprintf(str,"Inicio\n");
    put_string_usart((char*)str);
 
}
    void InitHardware()
{
    DDRC = 0b00000000;
    PORTC=0;
            
    DDRB = 0b00000000;
    PORTB = 0; 
    
    DDRD= 0b00000000;
    PORTD=255;   
    
	DDRB |= _BV(PWM0); //Establece commo salida el Pin de PWM para comparacion de señales DAC
    DDRB |= _BV(SPI_MOSI); //LED como salida
    
    TCCR1A |= _BV(COM1A1) | _BV(WGM10); //establece limite inferior para PWM OCR1A
	TCCR1B |= _BV(CS10) | _BV(WGM12); //Establece limite superior para PWM OCR1A
    
    
    DDRC |= _BV(LED); //Establece como salida el Pin de LED
    DDRC |= _BV(2); //Establece como salida el Pin de enanble de los sensores sharp

    cli();
    //Interrupcion Timer1
    TCCR0A = 0b00000000;
    TCCR0B = 0b00000011;
    TIMSK0 = 0B00000001;
    //Interrupcion Pinchanged
    PCICR|=_BV(PCIE2);  //Configura el Vector
    //PCMSK0|=_BV(PCINT0); //Configura el PIN   
    PCMSK2|=_BV(PCINT18); //Configura el PIN 
    PCMSK2|=_BV(PCINT19);
    PCMSK2|=_BV(PCINT20);
    PCMSK2|=_BV(PCINT21);
    PCMSK2|=_BV(PCINT22);
    PCMSK2|=_BV(PCINT23);
    
    sei();
}


void WDT_off(void)
{
    MCUSR = 0;
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = 0;
         wdt_disable();

}
void WDT_Prescaler_Change(void)
{
/* Start timed equence */
WDTCSR |= (1<<WDCE) | (1<<WDE);
/* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP0);
}


void watchdogSetup(void)
{
    cli(); // disable all interrupts
    wdt_reset(); // reset the WDT timer
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    // Set Watchdog settings:
    WDTCSR = (0<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0);
    sei();
}