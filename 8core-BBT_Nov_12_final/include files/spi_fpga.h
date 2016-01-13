/*
 * spi_fpga.h
 *
 *  Created on: Nov 29, 2012
 *      Author: nachiappanr
 */

#ifndef SPI_FPGA_H_
#define SPI_FPGA_H_

#include"platform.h"

#define	FPGA_STATUS Uint32
#define SPI_FPGA_OPFREQ		9760000	 			/* 9.76 MHz operating frequency*/

#define CMDPKT_FPGA_READID	0x01
#define CMDPKT_FPGA_READ 	0x11
#define CMDPKT_FPGA_WRITE	0x21

#define ERROR_SPI_FPGA 		0x0E
/* ------------------------------------------------------------------------ *
 *  Function declarations                                                   *
 * ------------------------------------------------------------------------ */
void fpga_spi_init();
void fpga_spiinitgpio(uint32_t);
void delay(uint32_t);
FPGA_STATUS fpga_spiclaim(uint32_t freq);
FPGA_STATUS fpga_get_details(uint8_t *);
FPGA_STATUS fpga_spi_write(uint8_t*,uint32_t,uint8_t*,uint32_t);
FPGA_STATUS fpga_spi_loopback(uint8_t* data,uint32_t data_len);

#endif /* SPI_FPGA_H_ */
