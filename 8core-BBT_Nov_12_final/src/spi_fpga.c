/*
 * spi_fpga.c
 *
 *  Created on: Nov 29, 2012
 *      Author: nachiappanr
 */
/************************
 * Include Files
 ************************/
#include<stdio.h>

#include "platform_internal.h"
#include"spi_fpga.h"
#include"spi.h"
#include"gpio.h"


//static uint32_t data1_reg_val=0;


/******************************************************************************
 *
 * Function:    fpga_get_details
 *
 * Description: This function the details of fpga device.
 *
 * Parameters:  None
 *
 * Return Value: status (For debugging purpose only)
 ******************************************************************************/
FPGA_STATUS fpga_get_details(uint8_t *id)

	{
		FPGA_STATUS ret;
		/* Claim the SPI controller */
		//ret	= spi_claim(1,SPI_FPGA_OPFREQ);
	    ret = fpga_spiclaim(SPI_FPGA_OPFREQ);
			    if (ret) {
	    	        spi_release();
	    	        return FAIL;
	    }
	   // spi_xfer(4,NULL,id,TRUE);

   /* send command to read the ID codes */
	    ret = spi_cmd(CMDPKT_FPGA_READID,id,sizeof(id));
	    if (ret) {
	        		spi_release();
	        		return FAIL;
	    		}

	    spi_release();
	    return SUCCESS;
}
/******************************************************************************
 *
 * Function:    spi_fpgaclaim
 *
 * Description: This function claims the SPI bus in the SPI controller
 *
 * Parameters:  Uint32 freq     - SPI clock frequency
 *
 * Return Value: error status
 *
 ******************************************************************************/
FPGA_STATUS fpga_spiclaim (uint32_t freq)
{
	uint32_t scalar;

    PLIBSPILOCK()

    /* Enable the SPI hardware */
    SPI_SPIGCR0 = CSL_SPI_SPIGCR0_RESET_IN_RESET;
    delay(100);
    SPI_SPIGCR0 = CSL_SPI_SPIGCR0_RESET_OUT_OF_RESET;

    /* Set master mode, powered up and not activated */
    SPI_SPIGCR1 =   (CSL_SPI_SPIGCR1_MASTER_MASTER << CSL_SPI_SPIGCR1_MASTER_SHIFT)   |
                    (CSL_SPI_SPIGCR1_CLKMOD_INTERNAL << CSL_SPI_SPIGCR1_CLKMOD_SHIFT);


    /* CS0, CS1, CLK, Slave in and Slave out are functional pins */
     SPI_SPIPC0 =    ((CSL_SPI_SPIPC0_SCS0FUN1_SPI << CSL_SPI_SPIPC0_SCS0FUN1_SHIFT) |
                        (CSL_SPI_SPIPC0_CLKFUN_SPI << CSL_SPI_SPIPC0_CLKFUN_SHIFT)     |
                        (CSL_SPI_SPIPC0_SIMOFUN_SPI << CSL_SPI_SPIPC0_SIMOFUN_SHIFT)   |
                        (CSL_SPI_SPIPC0_SOMIFUN_SPI << CSL_SPI_SPIPC0_SOMIFUN_SHIFT)) & 0xFFFF;


    /* setup format */
    scalar = ((SPI_MODULE_CLK / freq) - 1 ) & 0xFF;

    SPI_SPIFMT0 =   	(8 << CSL_SPI_SPIFMT_CHARLEN_SHIFT)               |
                        (scalar << CSL_SPI_SPIFMT_PRESCALE_SHIFT)                      |
                        (CSL_SPI_SPIFMT_PHASE_DELAY << CSL_SPI_SPIFMT_PHASE_SHIFT)     |
                        (CSL_SPI_SPIFMT_POLARITY_LOW << CSL_SPI_SPIFMT_POLARITY_SHIFT) |
                        (CSL_SPI_SPIFMT_SHIFTDIR_MSB << CSL_SPI_SPIFMT_SHIFTDIR_SHIFT)|
                        (10 << CSL_SPI_SPIFMT_WDELAY_SHIFT);

    //data1_reg_val = (CSL_SPI_SPIDAT1_CSHOLD_ENABLE << CSL_SPI_SPIDAT1_CSHOLD_SHIFT) |
    //                    (0x01 << CSL_SPI_SPIDAT1_CSNR_SHIFT)|
     //                   (CSL_SPI_SPIDAT1_WDEL_ENABLE<<CSL_SPI_SPIDAT1_WDEL_SHIFT);

    /* including a minor delay. No science here. Should be good even with
        * no delay
        */
    // SPI_SPIDELAY =  (6 << CSL_SPI_SPIDELAY_C2TDELAY_SHIFT) |
            //                (9 << CSL_SPI_SPIDELAY_T2CDELAY_SHIFT); //3

    /* no interrupts */
    SPI_SPIINT0 = CSL_SPI_SPIINT0_RESETVAL;
    SPI_SPILVL  = CSL_SPI_SPILVL_RESETVAL;

    /* enable SPI */
    SPI_SPIGCR1 |= ( CSL_SPI_SPIGCR1_ENABLE_ENABLE << CSL_SPI_SPIGCR1_ENABLE_SHIFT );

    // SPI_SPIDAT1 = data1_reg_val| 0x1;

    return SUCCESS;
}
/******************************************************************************
 *
 * Function:		spi_fpgainitgpio
 *
 * Description:		Initializes the GPIO pin number which is used as chip select with FPGA
 *
 *
 * Parameters:		DSP_FPGA_CSGPIO - pin number used as chip select to FPGA
 *
 * Return Value: 	void
 *
 *****************************************************************************/

void fpga_spiinitgpio(uint32_t DSP_FPGA_CSGPIO)
{

			gpioInit();
    		gpioSetDirection(DSP_FPGA_CSGPIO,GPIO_OUT);
    		gpioSetOutput(DSP_FPGA_CSGPIO);

}
/******************************************************************************
 *
 * Function:    Fpga_write
 *
 * Description: This function writes data to the FPGA
 *
 * Parameters:  uint8_t* cmd      - pointer to the Command to be send to FPGA
 *              uint32_t cmd_len  - Length of the command in bytes
 *              uint8_t* Data     - Pointer to the data to be written
 *              uint32_t data_len - Length of the data in bytes
 ******************************************************************************/
FPGA_STATUS fpga_spi_write(uint8_t* cmd,uint32_t cmd_len,uint8_t* data,uint32_t data_len)
{
		FPGA_STATUS ret;
		uint8_t writecmd = CMDPKT_FPGA_WRITE;
		/* Claim the SPI controller */
	   ret = fpga_spiclaim(SPI_FPGA_OPFREQ);
	   if (ret) {
	    	    spi_release();
	            return FAIL;
	        	}
	    spi_xfer(1,&writecmd,NULL,0);
	    printf("Write command sent:%d\n",writecmd);

	    ret = spi_cmd_write(cmd,cmd_len,data,data_len);
	    if (ret)
	    {
	    	  spi_release();
	    	  return FAIL;
	    }
	    else
	    {     spi_release();
	   	   	  return SUCCESS;
	    }
}

void delay (uint32_t cycles)
{
	volatile int i;
	for(i=0;i<cycles;i++)
		{};
}
FPGA_STATUS fpga_spi_loopback(uint8_t* data,uint32_t data_len)
{
	FPGA_STATUS ret;
	uint8_t i,rcvd[100];
	uint8_t writecmd = CMDPKT_FPGA_WRITE,readcmd=CMDPKT_FPGA_READ;
	//initialise SPI
	ret = fpga_spiclaim(SPI_FPGA_OPFREQ);
	if (ret) {
		    	 spi_release();
		    	 return FAIL;
		      }
	//transmit data
	spi_xfer(1,&writecmd,NULL,0);
	spi_xfer(data_len,data,NULL,0);
	spi_release();
	delay (100);
	platform_write("DATA sent successfully \n");
	//receive the data
	ret = fpga_spiclaim(SPI_FPGA_OPFREQ);
	if (ret) {
			    	 spi_release();
			    	 return FAIL;
			 }
	spi_cmd_read(&readcmd,1,rcvd,data_len);
	//verify the data
	for(i=0;i<data_len;i++)
	{
		if(rcvd[i]=!data[i])
			platform_write("error occurred for byte %d  expected :%d  received %d",i,data[i],rcvd[i]);
		else
			platform_write("DATA verification successful \n");
	}
	spi_release();
	return SUCCESS;
}



