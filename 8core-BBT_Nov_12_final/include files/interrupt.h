/*
 * interrupt.h
 *
 *  Created on: Mar 7, 2013
 *      Author: nachiappanr
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include"csl_intc.h"

uint8_t interrupt_config(uint8_t,void*);

void fpga_gpio_interrupt(void);
void fpga_remote_prog(uint8_t);

void delay_intr(uint32_t);
void fpga_rem_interrupt(void *);
void fpga_interrupt(void*);



#endif /* INTERRUPT_H_ */
