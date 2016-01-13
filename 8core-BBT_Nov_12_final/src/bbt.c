/*
 * bbt.c
 *
 *  Created on: Feb 25, 2013
 *      Author: nachiappanr
 */

#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <xdc/cfg/global.h>

#include <cerrno>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include"platform_internal.h"
#include "resource_mgr.h"
#include "evmc66x_gpio.h"
#include "bbt.h"
#include "gpio.h"

#define MAXARGSIZE 		5

Task_Handle task2;
test_config args;
uint8_t eTestID[MAXARGSIZE],BBT_TestID[MAXARGSIZE];

static Void diagTask(UArg arg0, UArg arg1);


int8_t TestApp_GetInput()
{
	uint8_t ok=0,err=1;
	platform_errno = PLATFORM_ERRNO_RESET;

	platform_write(" C6678 8 CORE -Board Bring up Test environment\n");
	platform_write("----------------------------------------------\n");
	platform_write("1.SYSTEM_CLK_TEST\n");
	platform_write("2.PROGRAM_LOAD_AND_MEMORY_TEST\n");
	platform_write("3.GPIO_TEST\n");
	platform_write("4.SPI_FLASH_TEST\n");
	platform_write("5.FPGA_INTERRUPT_TEST\n");
	platform_write("6.SPI_FPGA_TEST\n");
	platform_write("7.SRIO_TEST\n");
	platform_write("8.ETHERNET_TEST\n");
	platform_write("9.FPGA_REMOTE_PROG_TEST\n");
	platform_write(" Enter '0' to quit the test\n");
	platform_write("Enter the appropriate number from menu shown\n ##>");
	get_input(eTestID);
	if((!strcmp((char*)eTestID,"1"))||(!strcmp((char*)eTestID,"2"))||(!strcmp((char*)eTestID,"3"))||(!strcmp((char*)eTestID,"4"))
			||(!strcmp((char*)eTestID,"5"))||(!strcmp((char*)eTestID,"6"))||(!strcmp((char*)eTestID,"7"))||(!strcmp((char*)eTestID,"8"))
			||(!strcmp((char*)eTestID,"9"))||(!strcmp((char*)eTestID,"0")))  //(!strcmp((char*)eTestID,"\r"))
			return ok;
		else
			return err;

}

uint8_t TestApp_ProcessInput()
{
	uint8_t ok=0,err=1,i;
	for(i=0;i<MAXARGSIZE;i++)
	{
		BBT_TestID[i]=0;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"1")))
	{
		platform_write("SYSCLK_TEST \n ");
		platform_write("System Clock Test Completed\n");
		return ok;
	}

	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"2")))
	{
		platform_write("PROGRAM_LOAD_AND_MEMORY_TEST\n");
		platform_write("----------------------------------------------\n");
		platform_write("1.PROGRAM_LOAD_TEST\n");
		platform_write("2.INTERNAL_MEMORY_TEST\n");
		platform_write("3.DDR3_MEMORY_TEST\n");
		platform_write("4.EEPROM_TEST\n");
		platform_write("30.DDR3_REGRESSION_MEM_TEST\n");
		platform_write("Enter '0' to go back to the main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"1"))||(!strcmp((char*)BBT_TestID,"2"))||(!strcmp((char*)BBT_TestID,"3"))
				||(!strcmp((char*)BBT_TestID,"4"))||(!strcmp((char*)BBT_TestID,"0"))||(!strcmp((char*)BBT_TestID,"30")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"3")))
	{
		platform_write("GPIO_TEST\n");
		platform_write("-------------------------------\n");
		platform_write("5.BOOT_GREEN_LED_TEST\n");
		platform_write("6.BOOT_RED_LED_TEST\n");
		platform_write("7.HEALTH_GREEN_LED_TEST\n");
		platform_write("8.HEALTH_RED_LED_TEST\n");
		platform_write("9.SRIO_ACTIVE_LED_TEST\n");
		platform_write("10.FPGA_RESET_TEST\n");
		platform_write("11.GPIO_CLEAR_VOLTAGE_TEST\n");
		platform_write("Enter '0' to go to main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"5"))||(!strcmp((char*)BBT_TestID,"6"))||(!strcmp((char*)BBT_TestID,"7"))||(!strcmp((char*)BBT_TestID,"8"))
						||(!strcmp((char*)BBT_TestID,"9"))||(!strcmp((char*)BBT_TestID,"10"))||(!strcmp((char*)BBT_TestID,"11"))||(!strcmp((char*)BBT_TestID,"0")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"4")))
	{
		platform_write("SPI_FLASH_TEST\n");
		platform_write("-------------------------------\n");
		platform_write("12.FLASH_READ_ID_TEST\n");
		platform_write("13.FLASH_READ_WRITE_TEST\n");
		platform_write("14.FLASH_ERASE_TEST\n");
		platform_write("Enter '0' to go to main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"12"))||(!strcmp((char*)BBT_TestID,"13"))||(!strcmp((char*)BBT_TestID,"14"))||(!strcmp((char*)BBT_TestID,"0")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"5")))
	{
		platform_write("FPGA_INTERRUPT_TEST\n ");
		platform_write("-------------------------------\n");
		bbt_fpga2dsp_interrupt_test();
		return ok;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"6")))
	{
		platform_write(" SPI_FPGA_TEST\n ");
		platform_write("----------------------------------------------\n");
		platform_write("15.FPGA_READ_ID_TEST\n");
		platform_write("16.FPGA_SPI_TEST\n");
		platform_write("Enter '0' to go to main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"15"))||(!strcmp((char*)BBT_TestID,"16"))||(!strcmp((char*)BBT_TestID,"0")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"7")))
	{
		platform_write("SRIO_TEST\n ");
		platform_write("----------------------------------------------\n");
		platform_write("17.SRIO_1_LOOPBACK_TEST\n");
		platform_write("Enter '0' to go to main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"17"))||(!strcmp((char*)BBT_TestID,"0")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"8")))
	{
		platform_write(" ETHERNET_TEST\n ");
		platform_write("----------------------------------\n");
		platform_write("18.ETHERNET_TEST_MODE_1\n");
		platform_write("19.ETHERNET_TEST_MODE_2\n");
		platform_write("20.ETHERNET_TEST_MODE_3\n");
		platform_write("21.ETHERNET_TEST_MODE_4\n");
		platform_write("22.ETHERNET_NORMAL_MODE\n");
		platform_write("23.ETHERNET_REG_STATUS_READ_TEST\n");
		platform_write("Enter '0' to go to main menu\n");
		platform_write("Enter the appropriate number from menu shown\n ##>");
		get_input(BBT_TestID);
		if((!strcmp((char*)BBT_TestID,"18"))||(!strcmp((char*)BBT_TestID,"19"))||(!strcmp((char*)BBT_TestID,"0"))||(!strcmp((char*)BBT_TestID,"20"))||(!strcmp((char*)BBT_TestID,"21"))||(!strcmp((char*)BBT_TestID,"22"))||(!strcmp((char*)BBT_TestID,"23")))
			return ok;
		else
			return err;
	}
	if(((char*)eTestID[0]!=NULL)&&(!strcmp((char*)eTestID,"9")))
	{
		platform_write("FPGA_REMOTE_PROGRAMING_TEST\n");
		platform_write("----------------------------------\n");
		bbt_fpga_remote_prog();
		return ok;
	}
	platform_write("Enter the appropriate value\n");
	return err;
}

void TestApp_DSP()
{
	if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"1")))
		{
			platform_write("PROGRAM_LOAD_TEST\n ");
			ProgLoad_Test();
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"2")))
		{
			platform_write("INTERNAL_MEMORY_TEST\n");
			bbt_internal_mem_test(&args);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"3")))
		{
			platform_write("DDR3_MEMORY_TEST \n");
			bbt_external_mem_test(&args);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"4")))
		{
			platform_write("EEPROM_TEST\n ");
			bbt_eeprom_mem_test(&args);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"30")))
		{
			platform_write("DDR3_REGRESSION_MEMORY_TEST \n");
			bbt_ddr3_regresssion_mem_test(&args);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"5")))
		{
			platform_write("BOOT_GREEN_LED_TEST\n ");
			bbt_gpio_led_test(&args,BOOT_GREEN_LED);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"6")))
		{
			platform_write("BOOT_RED_LED_TEST\n ");
			bbt_gpio_led_test(&args,BOOT_RED_LED);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"7")))
		{
			platform_write("HEALTH_GREEN_LED_TEST\n ");
			bbt_gpio_led_test(&args,HEALTH_GREEN_LED);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"8")))
		{
			platform_write("HEALTH_RED_LED_TEST\n ");
			bbt_gpio_led_test(&args,HEALTH_RED_LED);
			return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"9")))
		{
			platform_write("SRIO_ACTIVE_LED_TEST\n ");
			bbt_gpio_led_test(&args,SRIO_ACTIVE_LED);
			return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"10")))
		{
		platform_write("GPIO_FPGA_RESET_TEST\n ");
		bbt_fpga_reset_test();
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"11")))
		{
		platform_write("GPIO_CLEAR_VOLTAGE_TEST\n ");
		//bbt_gpio_clear_test();
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"12")))
		{
		platform_write("FLASH READ ID TEST\n");
		bbt_flash_spi_test(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"13")))
		{
		platform_write("FLASH_READ_WRITE_TEST\n ");
		bbt_flash_readwrite(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"14")))
		{
		platform_write("FLASH_ERASE_TEST\n ");
		bbt_flash_erase(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"25")))
		{
		platform_write("FPGA_INTERRUPT_TEST ");
		bbt_fpga2dsp_interrupt_test(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"15")))
		{
		platform_write("FPGA_SPI_TEST\n ");
		bbt_ReadFpgaId(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"16")))
		{
		platform_write("FPGA_SPI_SPEED_TEST_10MHZ\n ");
		bbt_fpga_spiloopback_test(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"17")))
		{
		platform_write("SRIO_1_LOOPBACK_TEST\n ");
		bbt_SrioloopbackTest(&args);
		return;
		}

	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"18")))
		{
		platform_write("ETHERNET_TEST_MODE_1\n ");
		args.phytestmode =1;
		bbt_phy_test_node(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"19")))
		{
		platform_write("ETHERNET_TEST_MODE_2\n ");
		args.phytestmode =2;
		bbt_phy_test_node(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"20")))
		{
		platform_write("ETHERNET_TEST_MODE_3\n ");
		args.phytestmode =3;
		bbt_phy_test_node(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"21")))
		{
		platform_write("ETHERNET_TEST_MODE_4\n ");
		args.phytestmode =4;
		bbt_phy_test_node(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"22")))
		{
		platform_write("ETHERNET_NORMAL_MODE\n ");
		args.phytestmode =0;
		bbt_phy_test_node(&args);
		return;
		}
	else if(((char*)BBT_TestID[0]!=NULL)&&(!strcmp((char*)BBT_TestID,"23")))
		{
		platform_write("ETHERNET_REG_STATUS_READ_TEST\n ");
		bbt_eth_phy_reg_status(&args);
		return;
		}
	return;
}

static Void diagTask(UArg arg0, UArg arg1)
{
	while(1)
	{
			if(!TestApp_GetInput())
			{
				if(!strcmp((char*)eTestID,"0"))//if(ZERO==(char*)eTestID)	//To Exit the test.
				{
				    	platform_write("Test completed\n");
				    	platform_write("Exiting Test Environment\n");
				    	platform_write("Press FULL RESET switch to load again to continue testing\n");
				    	Task_delete(&task2);
				}
				else if(*(char*)eTestID==NULL)
				{
					platform_write("##> /n");
					continue;
				}
				else
    			{
					if (!TestApp_ProcessInput())
					{
						TestApp_DSP();
					}
					else
					{
						platform_write(" you have entered inappropiate number \n try again \n");
					}

    			}
			}
			else
			{
				platform_write(" you have entered inappropiate num \n try again \n");
				continue;
			}
    }
}
#if READ_EEPROM_IMAGE
    read_eeprom_image();
#endif

# if 0
   if(args.test_uart) {
        platform_write("UART test start\n");
        test_uart(&args);
        platform_write("UART test complete\n");
    				  }
#endif

/******************************************************************************
 * Function:    main
 ******************************************************************************/
void main()
{
	 platform_init_flags  init_flags;
	 platform_init_config init_config;
	 platform_info        p_info;
	 Task_Params     taskParams;

/* Set default values */
	 memset(&args, 0x01, sizeof(test_config));
	 memset(&init_flags, 0x01, sizeof(platform_init_flags));
	 args.init_config_pll1_pllm     = DEF_INIT_CONFIG_PLL1_PLLM;
	 args.init_config_uart_baudrate = DEF_INIT_CONFIG_UART_BAUDRATE;
	 args.nor_test_sector_number    = DEF_NOR_TEST_SECTOR_NUMBER;
	 args.eeprom_test_slave_address = DEF_EEPROM_TEST_SLAVE_ADDRESS0;
	 args.led_test_loop_count       = DEF_LED_TEST_LOOP_COUNT;
	 args.led_test_loop_delay       = DEF_LED_TEST_LOOP_DELAY;
	 args.ext_mem_test_base_addr    = DEF_EXT_MEM_TEST_BASE_ADDR;
	 args.ext_mem_test_length       = DEF_EXT_MEM_TEST_LENGTH;
	 args.int_mem_test_core_id      = DEF_INT_MEM_TEST_CORE_ID;
	 init_config.pllm    = args.init_config_pll1_pllm;

	  gpioInit();
	  gpioSetDirection(3,GPIO_OUT);
	  gpioClearOutput(3);


	  gpioSetDirection(ETHERNET_PHY1_RESET,GPIO_OUT);
	  gpioClearOutput(ETHERNET_PHY1_RESET);

	  gpioSetDirection(ETHERNET_PHY2_RESET,GPIO_OUT);
	  gpioClearOutput(ETHERNET_PHY2_RESET);

	  gpioSetDirection(UART_ENABLE,GPIO_OUT);
	  gpioClearOutput(UART_ENABLE);

	  gpioSetDirection(FLASH_ENABLE,GPIO_OUT);
	  gpioClearOutput(FLASH_ENABLE);

	  platform_uart_init();
	  platform_write_configure(PLATFORM_WRITE_ALL);

	  platform_delay(100);

	  platform_write("The JTAG ID register contents is 0x%x \n",JTAGID_REG);

	  if (platform_init(&init_flags, &init_config) != Platform_EOK)
		  {
			  platform_write("Platform failed to initialize, errno = 0x%x \n", platform_errno);
		  }

	  platform_get_info(&p_info);

//Initliaze the diag Task

	  Task_Params_init(&taskParams);
	  taskParams.stackSize = 2048;
	  taskParams.priority = 14;
	  task2=Task_create(diagTask, &taskParams, NULL);
	  if(task2==NULL)
    		{
    			platform_write("Task create failed\n");
    			System_abort("Task create failed");
    		}
      BIOS_start();    //Start the BIOS

}

/******************************************************************************
 * Function:    Get Input
 ******************************************************************************/
void get_input(uint8_t* var)
{
	uint8_t i=0;
	platform_errno=PLATFORM_ERRNO_READTO;
	uint8_t buf[MAXARGSIZE]={0,0,0,0,0};
	while(1)
	{
		if(i>=MAXARGSIZE)
		{
			platform_write("Variable exceeding the Max size\n");
			break;
		}
		if (platform_uart_read(&buf[i], 30 * 10000000) == Platform_EOK)
		{
			platform_write("%c",buf[i]);
			if(!strcmp((char*)&buf[i],"\r"))
				{
				buf[i]='\0';
				break;
				}
		}
		else
		{
			platform_write("Time Out(errno: 0x%x)\n", platform_errno);
		}
		i++;
	}
	strcpy((char *)var,(char*)buf);
}



