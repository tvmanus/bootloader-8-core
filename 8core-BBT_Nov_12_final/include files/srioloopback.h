/*
 * srioloopback.h
 *
 *  Created on: Mar 7, 2013
 *      Author: nachiappanr
 */

#ifndef SRIOLOOPBACK_H_
#define SRIOLOOPBACK_H_

#include"platform.h"
#include"spi.h"
#include"gpio.h"
#include"spi_fpga.h"
#include"platform_internal.h"
#include"srioloopback.h"

typedef enum
{
	 SRIO_DATARATE_1250 = 1,
	 SRIO_DATARATE_2500,
	 SRIO_DATARATE_3125,
	 SRIO_DATARATE_5000,
	 MAX_SRIO_DATARATE
}SrioSpeed;

 int32_t UartWritestring(char []);
 void fpga_spiinitgpio(uint32_t);
 uint32_t fpga_spi_write(uint8_t*,uint32_t,uint8_t*,uint32_t);
 int32_t SrioDevice_init (uint8_t,uint8_t);
 uint32_t Srio_Init(uint8_t,uint8_t);
 void Srio_loopback(uint8_t);

#endif /* SRIOLOOPBACK_H_ */
