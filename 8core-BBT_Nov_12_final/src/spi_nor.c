#include<stdio.h>
#include"evmc66x_spi.h"
#include"evmc66x_nor.h"
#include"gpio.h"
#include"stdlib.h"
#include"string.h"
#include"platform.h"
#include"spi_nor.h"

void test_flash_readwrite()
{


	uint32_t Write_status,Read_status,i;
	PLATFORM_DEVICE_info* hDeviceNor;
	uint8_t *in,*out;
	uint32_t sector_number=5;
	uint32_t Addr;

	in=malloc( SPI_NOR_TEST_SIZE);
	memset(in,0x55,SPI_NOR_TEST_SIZE);  //allocate memory and initialize the test pattern

	out=malloc( SPI_NOR_TEST_SIZE);
	memset(out,0,SPI_NOR_TEST_SIZE);

	if(in==NULL||out==NULL)
	{
		platform_write("Unable to allocate Memory in the the RAM \n");
		return;
	}

	gpioInit();
	gpioSetDirection(FLASH_ENABLE,GPIO_OUT);
	gpioSetOutput(FLASH_ENABLE);

//Open the device
	hDeviceNor=platform_device_open(PLATFORM_DEVID_NORN25Q128, 0);
	if(hDeviceNor==NULL)
		platform_write("Nor device cannot be opened.\n");
		platform_write("leaving the write protected blocks\n");

	for(sector_number=5;sector_number<256;sector_number++)   //checking all the sectors
	{
		Addr= sector_number*64*1024;  //each sector is 64Kb - total device size is 16 MB
//write 0x55
		Write_status = nor_write(hDeviceNor,Addr,SPI_NOR_TEST_SIZE,in);
		if(Write_status==0)
			platform_write("\n Data Written to NOR Successfully\n");
		else
			platform_write("writing to NOR deivce failed\n");
//clear the output memory
		memset(out,0,SPI_NOR_TEST_SIZE);
//read back and verify
		Read_status=nor_read(hDeviceNor,Addr,SPI_NOR_TEST_SIZE,out);
		if(Read_status==0)
		{
			for(i=0;i<SPI_NOR_TEST_SIZE;i++)
				{
			    if (memcmp(in,out,SPI_NOR_TEST_SIZE) != 0)
						platform_write("Error: Data mismatch occurs at sector %d : expected %d received %d\n",sector_number,in[i],out[i]);
				}
			platform_write("Data verification successful at the sector number %d\n",sector_number);
		}
		else
			platform_write("Reading data from the Nor device failed \n");
	}
    free(in);
	free(out);
	platform_device_close(hDeviceNor->handle);
}

void test_flash_erase()
{
	uint32_t Erase_status;
	PLATFORM_DEVICE_info* hDeviceNor;
	uint32_t sector_number;

	gpioInit();
	gpioSetDirection(FLASH_ENABLE,GPIO_OUT);
	gpioSetOutput(FLASH_ENABLE);

	//Open the device
	hDeviceNor=platform_device_open(PLATFORM_DEVID_NORN25Q128, 0);
	if(hDeviceNor==NULL)
	platform_write("Nor device cannot be opened.\n");

	platform_write("Erasing all the sectors...\n ");

	for(sector_number=0;sector_number<256;sector_number++)   //checking only 1st 1024 sectors
	{
		Erase_status = nor_erase(hDeviceNor,sector_number);
		if(Erase_status==0)
		{
			platform_write("\n The Data Erased from the nor flash successfully\n");
		}
		else
		{
			platform_write("error occurred in erasing the data for NOR flash\n");
		}
	}
	platform_device_close(hDeviceNor->handle);
}


/*

	Write_status = nor_write(hDeviceNor,Addr,SPI_NOR_TEST_SIZE,in);
		if(Write_status==0)
		{
			printf("\n The Data is written in Nor flash\n");
		}
		else
		{
			printf("error occurred in writing the data for NOR flash\n");
		}

	Read_status=nor_read(hDeviceNor,Addr,SPI_NOR_TEST_SIZE,out);
		if(Read_status==0)
			{
				for(i=0;i<SPI_NOR_TEST_SIZE;i++)
				{
					if(out[i]!=in[i])
					printf("Error Occurred at the location %d\n",i);
				}
				printf("Data verification is done Successfully\n");
			}

	Erase_status = nor_erase(hDeviceNor,(Uint32)-1);
		if(Erase_status==0)
		{
			printf("\n The NOR flash is erased successfully");
		}

	Read_status=nor_read(hDeviceNor,Addr,256,out);
		if(Read_status==0)
		{
				for(i=0;i<30;i++)
				{
					printf("\n Location : %x   data: %x",(i+Addr),out[i]);
				}

		}

	}

*/
