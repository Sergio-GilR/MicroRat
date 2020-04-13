
#include "user.h"
#include "uart.h"
#include "eeprom.h"
#include "lib_io/digitalAnalog.h"

#define VEL_BAUDIOS (uint32_t)38400
#define BAUDIOS  ((F_CPU/(VEL_BAUDIOS * 16))-1)

char TXDATA_UART0[100];
char RXDATA_UART0[100];
uint16_t ADC_Values[2];
uint8_t indADC;
uint8_t indTX, indRX;
uint8_t stateRX;
uint8_t  lenghTX;

void goToSleep(void)
{
    byte adcsra = ADCSRA;          //save the ADC Control and Status Register A
    ADCSRA = 0;                    //disable the ADC
    EICRA = _BV(ISC01);            //configure INT0 to trigger on falling edge
    EIMSK = _BV(INT0);             //enable INT0
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();                         //stop interrupts to ensure the BOD timed sequence executes as required
    sleep_enable();
    //disable brown-out detection while sleeping (20-25µA)
    uint8_t mcucr1 = MCUCR | _BV(BODS) | _BV(BODSE);
    uint8_t mcucr2 = mcucr1 & ~_BV(BODSE);
    MCUCR = mcucr1;
    MCUCR = mcucr2;
    //sleep_bod_disable();           //for AVR-GCC 4.3.3 and later, this is equivalent to the previous 4 lines of code
    sei();                         //ensure interrupts enabled so we can wake up again
    sleep_cpu();                   //go to sleep
    sleep_disable();               //wake up here
    ADCSRA = adcsra;               //restore ADCSRA
}

ISR(TIMER0_OVF_vect) //Evento por desbordamiento de Timer0
{ 
    TCNT0=49532; //Cantidad para desbordamiento en 1ms
    wdt_reset(); // reset the WDT timer

}
ISR(WDT_vect)
{
     put_string_usart("*"); 
    DigitalBON(SPI_MOSI);  
}
ISR(WDT_vect)
{
     put_string_usart("*"); 
    DigitalBON(SPI_MOSI);  
}

int main(void) 
{
    init:
    InitHardware(); //Iinicializa Hardware
    DigitalBOFF(5);
    Init_usart(BAUDIOS);  //Inicializa comunicacion serial
    setAnalogMode(MODE_10_BIT);  //Inicia Driver ADC, Inicia Convercion
    InitSoftware(); //Inicializa variables 
    InitADC();//Inicializa ADC
    DigitalCOFF(2);

    char str[5];
    for(;;) //Loop Inifinito
    {    
        sprintf(str,"%d\n",ReadADC(7,AVCC_REF));
        put_string_usart(str);
        _delay_ms(1);
        DigitalCChange(LED);
    }
    
    goto init;
    return 0;
}

