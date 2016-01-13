/*
 * Test_bbt.c
 *
 *  Created on: Mar 7, 2013
 *      Author: nachiappanr
 */
#include "platform.h"
#include "resource_mgr.h"
#include"evmc66x_nor.h"
#include "bbt.h"
#include"evmc66x_gpio.h"
#include"gpio.h"
#include"platform_internal.h"
#include"spi_fpga.h"
#include"srioloopback.h"
#include"interrupt.h"
#include"stdlib.h"
#include"spi_nor.h"

void ProgLoad_Test(void)
 {
	platform_write("HELLO WORLD\n");
	platform_write("PROGRAM_LOAD_TEST Completed\n");

 }

void print_boardinfo(test_config * args )
{
	platform_info p_info;
	if(args->print_info)
	{
		platform_write("Dear User, Printing the Board information\n");
		platform_get_info(&p_info);
		print_platform_info(&p_info, args);
		print_current_core_id();
	}
}

void bbt_internal_mem_test(test_config * args )
{
		uint8_t buf1;
		platform_write("Internal memory test start\n");
		platform_write("Enter the core number ");
		get_input(&buf1);
		args->int_mem_test_core_id = atoi((char*)&buf1);
		test_internal_memory(args);
		platform_write("Internal memory test over for core %d",buf1);
		platform_write("see the above message for test status\n");
}

void bbt_external_mem_test(test_config * args)
{

          platform_write("External memory test start\n");
          args->regression=0;
          test_external_memory(args);
          platform_write("External memory test complete\n");

}

void bbt_ddr3_regresssion_mem_test(test_config * args)
{

          platform_write("External memory regression test start\n");
          args->regression=1;
          test_external_memory(args);
          platform_write("External memory regression test complete\n");

}


void bbt_eeprom_mem_test(test_config * args)
{
		uint8_t addr;
		uint8_t buf1;
		platform_write("EEPROM test start\n");
		platform_write("Enter EEPROM slave address\n ");
		platform_write("Enter 0 for address 0X50 \n ");
		platform_write("Enter 1 for address oX51 \n ");
		get_input(&buf1);
		addr=atoi((char*)&buf1);
		if(!addr)
		{
			args->eeprom_test_slave_address= DEF_EEPROM_TEST_SLAVE_ADDRESS0;
			test_eeprom(args);
		}
		else
		{
			args->eeprom_test_slave_address= DEF_EEPROM_TEST_SLAVE_ADDRESS1;
			test_eeprom(args);
		}
}

void bbt_flash_spi_test(test_config* args)
{
		platform_write("Flash READ ID test start\n");
		if(nor_init()==NOR_EOK)
		{
			platform_write("NOR test complete\n");
		}
		else
		{
			platform_write("NOR test failed error no: %d \n",PLATFORM_ERRNO_BADFLASHDEV);
		}
}

void bbt_flash_readwrite(test_config* args)
{
		platform_write("Flash read test start\n");
		test_flash_readwrite();
		platform_write("NOR Read test complete\n");
}

void bbt_flash_erase(test_config* args)
{
		platform_write("Flash erase test start\n");
		test_flash_erase();
		platform_write("NOR erase test complete\n");
}

void bbt_gpio_led_test(test_config* args,uint32_t led)
{
		uint8_t count=0,Count=1;
		platform_write("GPIO LED test start\n");
		platform_write("Enter the No. of times to toggle the led \n");
		get_input(&count);
		Count=atoi((char*)&count);

		gpioInit();
		gpioSetDirection(led,GPIO_OUT);

		do
		{
			gpioSetOutput(led);
			platform_delay(1000000000);		//.76Hz or 1.3s
			gpioClearOutput(led);
			platform_delay(1000000000);
			Count--;

		}while(Count);
		platform_write("LED test complete\n");
}

void bbt_fpga_reset_test()
{
	uint8_t count=0,Count=1,i=0;
	platform_write("FPGA RESET test start\n");
	platform_write("Enter the No. of times to toggle the led \n");
	get_input(&count);
	Count=atoi((char*)&count);

	gpioInit();
	gpioSetDirection(DSP2FPGA_RESET,GPIO_OUT);
	do
		{
			gpioSetOutput(DSP2FPGA_RESET);
			platform_delay(2000000000);
			platform_delay(2000000000);
			platform_delay(2000000000);//.76Hz or 6(1.3s)
			gpioClearOutput(DSP2FPGA_RESET);
			platform_delay(2000000000);
			platform_delay(2000000000);
			platform_delay(2000000000);//.76Hz or 6(1.3s)
			Count--; i++;
			platform_write("Resetted %d time \n",i);
		}while(Count);
	platform_write("FPGA RESET test complete\n");
}

void bbt_fpga_remote_prog()
{
	uint8_t Count=0,count;
	platform_write("FPGA remote programming test start\n");
	platform_write("Enter the No. of times to toggle the programming pins \n");
	get_input(&count);
	Count=atoi((char*)&count);
	platform_write_configure(PLATFORM_WRITE_UART);
	fpga_remote_prog(Count);

}

void bbt_fpga2dsp_interrupt_test()
{
	platform_write("FPGA INTERRUPT test start\n");
	platform_write_configure(PLATFORM_WRITE_UART);
	fpga_gpio_interrupt();

}
void bbt_fpga_spiloopback_test(test_config* args)
{
	uint32_t status=1,i;
	uint8_t data_len;
	uint8_t data[100];
		platform_write("FPGA SPI test start\n");
		platform_write("Enter the number of bytes to loopback\n Note :max of 100 bytes\n");
		data_len=sizeof(data);
	    for (i = 0; i < data_len; i++)
	    {
	        data[i]=i;
	    }
		status= fpga_spi_loopback((uint8_t*)data,data_len);
		if(status==0)
		platform_write("FPGA SPI test completed Successful\n");

}

void bbt_ReadFpgaId(test_config* args)				//9.76MHZ
{
	uint8_t id[4]={0,0,0,0},i;
		platform_write("FPGA SPI READ ID test start\n");
		if(!fpga_get_details(id))
		{
			platform_write("FPGA device ID is");
			for(i=0;i<4;i++)
			{
				platform_write("%X",id[i]);
			}
		platform_write("\n FPGA SPI READ ID test complete\n");
		}

}

void bbt_SrioloopbackTest(test_config* args)
{
	platform_errno = PLATFORM_ERRNO_RESET;
		uint32_t status=1;
		uint8_t PortNo=0,speed=0;
		static uint8_t portnum;
		static SrioSpeed datarate;
		uint8_t cmd[4]={133,96,0,32},data[32]={00,00,128,132,  //84800000 - memeory region
											   64,138,03,00,   //0x038A40 - buffer size - 1000 packets
											   10,00,00,00,	// 10 packets -doorbell interval
											   00,00,00,00,
											   00,00,128,132,  //same for other SRIO
											   64,138,03,00,
											   200,00,00,00,
											   00,00,00,00 };
		platform_write("FPGA SRIO loopback test start\n");
		platform_write("Enter the port number to perform test\nPortNO:");
		get_input(&PortNo);
		portnum= (uint8_t) atoi((const char*)&PortNo);
		platform_write("Port Number is %d",portnum);

		platform_write("Enter the DATARATE to operate\n");
		platform_write("1 for 1.25	gbps\n");
		platform_write("2 for 2.5	gbps\n");
		platform_write("3 for 3.125	gbps\n");
		platform_write("4 for 5		gbps\n##>");
		get_input(&speed);

		datarate=(SrioSpeed)(atoi((const char*)&speed));

		//Initialize and write the command on SPI interface
		fpga_spi_write(cmd,sizeof(cmd),data,sizeof(data));
		platform_write("CONFIG_SRIO command sent sucessfully \n");

		//Initialize the SRIO interface
		status=Srio_Init(portnum,datarate);
		if(status!=0)
		platform_write("Error in initializing SRIO port");

		//start SRIO loopback
		Srio_loopback(portnum);

		platform_write("\n FPGA SRIO loopback test over : see the above message for test status\n\n\n");

}

/*void bbt_gpio_clear_test()
{
	uint8_t i;
	platform_write("GPIO CLEAR VOLTAGE test start\n");
	gpioInit();
	for(i=0;i<16;i++)
	{
		gpioSetDirection(i,GPIO_OUT);
		gpioClearOutput(i);
	}
	platform_write("GPIO CLEAR VOLTAGE test complete\n");
}*/
/*
void bbt_srio_init(test_config* args)
{
		platform_errno = PLATFORM_ERRNO_RESET;
		uint32_t status=1;
		uint8_t speed=0,PortNo=0;
		SrioSpeed datarate;
		uint8_t cmd[4]={133,96,0,32},data[5]={255,170,170,170,0};
		platform_write("FPGA SRIO init test start\n");
		//memset((void *)0x84800000, 0, (SRIOTEST_MAX_BLOCK_SIZE * SRIOTEST_MAX_BLOCK));
		//memset((void *)0x8d000000, 0, (SRIOTEST_MAX_BLOCK_SIZE * SRIOTEST_MAX_BLOCK)/2);
		platform_write("Enter the port number to perform test\n ##> \n");
		get_input(&PortNo);
		platform_write("Enter the DATARATE to operate\n");
		platform_write("1 for 1.25	gbps\n");
		platform_write("2 for 2.5	gbps\n");
		platform_write("3 for 3.125	gbps\n");
		platform_write("4 for 5		gbps\n ##>\n");
		get_input(&speed);
		datarate=(SrioSpeed)speed;
		//Initialize and write the command on SPI interface
		fpga_spi_write(cmd,sizeof(cmd),data,sizeof(data));
		//Initialize the SRIO interface
		status =Srio_Init(PortNo,datarate);
		if(status!=0)
			platform_write("Error in initializing SRIO port");
		else
			platform_write("\n FPGA SRIO init test complete\n");

}
*/
void bbt_eth_phy_reg_status(test_config *args)
{
    //configSerdes();
    //Init_SGMII(0);
    platform_phy_link_status(0);
    //Init_SGMII(1);
    platform_phy_link_status(1);
}

void bbt_phy_test_node (test_config  *args)
{
		if(args->phytestmode==1)
				{
			 	 	 if(platform_phy_test_mode(1))
			 	 		 platform_write("ERROR:PHY cannot be set in given test mode \n");
				}
		else if(args->phytestmode==2)
				{
					 if(platform_phy_test_mode(2))
						 platform_write("ERROR:PHY cannot be set in given test mode \n");
				}
		else if(args->phytestmode==3)
				{
					 if(platform_phy_test_mode(3))
						 platform_write("ERROR:PHY cannot be set in given test mode \n");
				}
		else if(args->phytestmode==4)
				{
					 if(platform_phy_test_mode(4))
						 platform_write("ERROR:PHY cannot be set in given test mode \n");
				}
		else if(args->phytestmode==0)
				{
					if(platform_phy_test_mode(0))
						 platform_write("ERROR:PHY cannot be set in normal mode \n");
				}

}
