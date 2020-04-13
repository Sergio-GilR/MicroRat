/* 
 * File:   uart.h
 * Author: sei
 *
 * Created on April 20, 2019, 7:09 PM
 */
//#include "user.h"


#ifndef UART_H
#define	UART_H
  #include <avr/interrupt.h>
#include <avr/cpufunc.h> 


#ifdef	__cplusplus
extern "C" {
#endif
					   
char Get_usart();     //funci�n para la recepci�n de caracteres
void Put_usart(char val);  //funci�n para la transmisi�n de caracteres
void put_string_usart(char* val);            //funci�n para la transmisi�n de cadenas de caracteres
void Init_usart(uint8_t baudios);  //funci�n para iniciar el USART AVR as�ncrono, 8 bits, 9600 baudios,
                       //sin bit de paridad, 1 bit de parada

void StartTX();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

