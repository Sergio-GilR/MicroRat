


#ifndef UART_H
#define	UART_H
  #include <avr/interrupt.h>
#include <avr/cpufunc.h> 


#ifdef	__cplusplus
extern "C" {
#endif
					   
char Get_usart();     //función para la recepción de caracteres
void Put_usart(char val);  //función para la transmisión de caracteres
void put_string_usart(char* val);            //función para la transmisión de cadenas de caracteres
void Init_usart(uint8_t baudios);  //función para iniciar el USART AVR asíncrono, 8 bits, 9600 baudios,
                       //sin bit de paridad, 1 bit de parada

void StartTX();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

