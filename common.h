
#ifndef COMMON_H
#define	COMMON_H

#define F_CPU 8000000U

//============= PORTC ==================
#define ADC0  0
#define ADC1  1
#define ADC2  1
#define LED 3
//SDA,SDL I2C

//============ PORTD ===================
// RX,TX 
#define RST_Ref 2
#define INT_Puerta 3
#define Sens1    4
#define Sens2    5
#define Sens3    6
#define Sens4    7

//=========== PORTB ====================
#define SensTapa 0
#define PWM0     1
#define SPI_SS   2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCLK 5
#define SensorsEnable2 6
#define ADC6   6
#define ADC7   7


#define BufferTX 200


#define TaskSensorsCalibracion 0
#define TaskSensorsMonitoreo 1
#define TaskSensorsTestSensores 2
#define TaskSensorsLowPower 3
#define TaskSensorsMonitoreoContinuo 4
#define TaskSensorsCalibracionContinuo 5


#include <avr/io.h>
#include <avr/interrupt.h>

//Data Types


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

