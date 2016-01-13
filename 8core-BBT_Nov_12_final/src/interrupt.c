/*
 * interrupt.c
 *
 *  Created on: Mar 7, 2013
 *      Author: nachiappanr
 */
#include "platform.h"
#include "resource_mgr.h"
#include"platform_internal.h"
#include"interrupt.h"
#include "gpio.h"
#include <ti/sysbios/hal/Hwi.h>
#include <xdc/runtime/Error.h>

#include "csl_chip.h"
#include "csl_chipAux.h"
#include "csl_intc.h"
#include "csl_gpio.h"
#include "csl_gpioAux.h"

CSL_IntcContext             intcContext;
CSL_IntcEventHandlerRecord  EventHandler[30];
CSL_IntcObj                 intcObj;
CSL_IntcHandle              hTest;
CSL_IntcGlobalEnableState   state;
CSL_IntcEventHandlerRecord  EventRecord;
CSL_IntcParam               vectId;
Hwi_Handle myHwi;

static uint8_t b=0;
static uint32_t j=0;


uint8_t interrupt_config(uint8_t eventId,void* fnptr_isr)
{

#if 0
		platform_write ("Debug: GEM-INTC Configuration...\n");

	    /* INTC module initialization */
	    intcContext.eventhandlerRecord = EventHandler;
	    intcContext.numEvtEntries      = 10;
	    if (CSL_intcInit(&intcContext) != CSL_SOK)
	    {
	        platform_write("Error: GEM-INTC initialization failed\n");
	        return 0;
	    }

	    /* Enable NMIs */
	    if (CSL_intcGlobalNmiEnable() != CSL_SOK)
	    {
	        platform_write("Error: GEM-INTC global NMI enable failed\n");
	        return 0;
	    }

	    /* Enable global interrupts */
	    if (CSL_intcGlobalEnable(&state) != CSL_SOK)
	    {
	        platform_write ("Error: GEM-INTC global enable failed\n");
	        return 0;
	    }

	    vectId = CSL_INTC_VECTID_4;
	    hTest = CSL_intcOpen (&intcObj,eventId, &vectId , NULL);
	    if (hTest == NULL)
	    {
	        platform_write("Error: GEM-INTC Open failed\n");
	        return 0;
	    }

	    /* Register an call-back handler which is invoked when the event occurs. */
	    EventRecord.handler = fnptr_isr; //&fpga_interrupt;
	    EventRecord.arg = NULL;
	    if (CSL_intcPlugEventHandler(hTest,&EventRecord) != CSL_SOK)
	    {
	        platform_write("Error: GEM-INTC Plug event handler failed\n");
	        return 0;
	    }

	    /* Enabling the events. */
	    if (CSL_intcHwControl(hTest,CSL_INTC_CMD_EVTENABLE, NULL) != CSL_SOK)
	    {
	        platform_write("Error: GEM-INTC CSL_INTC_CMD_EVTENABLE command failed\n");
	        return 0;
	    }
	    platform_write ("Debug: GEM-INTC Configuration Completed\n");
	    return 1;
#endif

	Hwi_Params hwiParams;
	Error_Block eb;

	Hwi_Params_init(&hwiParams);
	Error_init(&eb);

	hwiParams.arg = NULL;
	hwiParams.eventId =eventId;
	hwiParams.maskSetting = Hwi_MaskingOption_NONE;
	myHwi = Hwi_create(4,(void(*)(void*))fnptr_isr,&hwiParams,&eb);

	if(myHwi==NULL)
	{
		platform_write("Hwi not created \n");
		return 0;
	}
	return 1;

}


void fpga_gpio_interrupt()
 {
	uint8_t eventId =87;
	CSL_GpioHandle  hGpio;
	hGpio = CSL_GPIO_open (0);
	CSL_GPIO_bankInterruptDisable(hGpio,0);
	CSL_GPIO_setPinDirInput(hGpio,FIRMWARE_RESET);
	CSL_GPIO_setRisingEdgeDetect(hGpio,FIRMWARE_RESET);
	CSL_GPIO_bankInterruptEnable(hGpio,0);

	if(interrupt_config(eventId,fpga_interrupt))
		platform_write("FPGA TO DSP INTERRUPT CONFIGURATION SUCESS\n");
 }

void fpga_remote_prog(uint8_t count)
{
	CSL_GpioHandle  hGpio;
	uint8_t eventId=84;  //gpio10 is configured as input

	hGpio = CSL_GPIO_open (0);
	CSL_GPIO_bankInterruptDisable(hGpio,0);

	CSL_GPIO_setPinDirOutput(hGpio,FPGA_REMOTE_PROG);
	CSL_GPIO_clearOutputData(hGpio,FPGA_REMOTE_PROG);

	CSL_GPIO_setPinDirInput(hGpio,HEALTH_RED_LED);
	CSL_GPIO_bankInterruptEnable(hGpio,0);
	CSL_GPIO_setRisingEdgeDetect(hGpio,HEALTH_RED_LED);

	CSL_GPIO_setPinDirOutput(hGpio,BOOT_GREEN_LED);
	CSL_GPIO_setPinDirOutput(hGpio,BOOT_RED_LED);
	CSL_GPIO_setPinDirOutput(hGpio,HEALTH_GREEN_LED);

	if(!interrupt_config(eventId, &fpga_rem_interrupt))
		platform_write("Error : Interrupt configuration failed\n");
		else
		{
			do
			{
				CSL_GPIO_setOutputData(hGpio,BOOT_GREEN_LED);
				CSL_GPIO_setOutputData(hGpio,BOOT_RED_LED);
				CSL_GPIO_setOutputData(hGpio,HEALTH_GREEN_LED);
				delay_intr(3);
				CSL_GPIO_clearOutputData(hGpio,BOOT_GREEN_LED);
				CSL_GPIO_clearOutputData(hGpio,BOOT_RED_LED);
				CSL_GPIO_clearOutputData(hGpio,HEALTH_GREEN_LED);
				delay_intr(3);
				count--;
			}while(count);
		}
	platform_write("FPGA remote programming over\n Received interrupt %d times\n",j);
}

void fpga_interrupt(void* dummy)
{
	platform_write("FPGA INTERRUT RECEIVED\n");
}

void fpga_rem_interrupt(void* dummy)
{
	if(b==0)
		b=1;
	j++;
}

void delay_intr(uint32_t num)
{
	uint32_t i;
	for(i=0;i<num;i++)
	{
		asm("nop");
	}
}


