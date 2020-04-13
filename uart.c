#include "uart.h"
//#include "user.h"
#include "lib_io/digitalAnalog.h"
#include <avr/interrupt.h>
#include <avr/cpufunc.h> 
uint8_t txValue;
uint8_t rxValue;
uint8_t ready=0;

extern char TXDATA_UART0[100];
extern char RXDATA_UART0[100];


extern uint8_t indTX, indRX;
extern uint8_t stateRX;
extern uint8_t  lenghTX;

SIGNAL(USART_RX_vect)
{
    if(!stateRX)
    {
        indRX=0;
    }
    RXDATA_UART0[indRX]=UDR0;	
    stateRX=1;
    //_NOP();
    if(indRX<98)
    {
        if(RXDATA_UART0[indRX++]=='\r')   //check for carriage return terminator and increment buffer index
        {
            // if terminator detected
            RXDATA_UART0[indRX-1]=0x00;   //Set string terminator to 0x00
                           //Reset buffer index
        }
    }

}

SIGNAL(USART_UDRE_vect)
{
    char tmp;
    tmp=(char)TXDATA_UART0[indTX++];
    if(indTX<31 || tmp!=0)
    {
        UDR0 =tmp;
        //UDR0='A';
    }
    else
    {
        indTX=0; //No hay espacio en el buffer
        UCSR0B&=~_BV(UDRIE0); // Quita la interrupcion
    }
    
}


void Init_usart(uint8_t baudios)
{
   
    
    cli();	
    UCSR0B = 0;
    UCSR0A = 0;
	//UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // And enable interrupts
	//UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	/*Enable transmitter */
	UCSR0B = (1<<TXEN0);
	
	/* Set frame format: 8data */
    UCSR0C = 0;
	UCSR0C |= (0<<USBS0)| (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0=baudios;	
    
    sei();
    
    
}


void StartTX()
{
    indTX=0;
    UCSR0B|=_BV(UDRIE0) ; //UCSR0B|=_BV(TXCIE0);  
    //UDR0=TXDATA_UART0[indTX++];
}
 
 
char Get_usart()
{
	if(UCSR0A&(1<<7))
    {  
		return UDR0;    
	}
	else
	return 0 ;
}
 
void Put_usart(char val)
{	
    while(!(UCSR0A&(1<<5)));   
	UDR0=val;    
    
}
 

 
void put_string_usart(char* val)
{	 
	while(*val !=0x00)
    {        
		Put_usart(*val);       
		val++;						
	}
     
}
