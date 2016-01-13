/******************************************************************************
 * Copyright (c) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 *
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *****************************************************************************/

#include <cerrno>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "resource_mgr.h"
#include "bbt.h"
#include"platform_internal.h"

/******************************************************************************
 * Function:    print_current_core_id  
 ******************************************************************************/
 void print_current_core_id(void)
{
    platform_write("Current core id is %d\n", platform_get_coreid());
}

/******************************************************************************
 * Function:    print_platform_info  
 ******************************************************************************/
 void print_platform_info(platform_info * p_info, test_config * args)
{
	uint32_t	i;
	PLATFORM_DEVICE_info *p_device;
    PLATFORM_EMAC_EXT_info emac_info;
/*

    PRINT_VARIABLE(%s, p_info->version);
    PRINT_VARIABLE(%d, p_info->cpu.core_count);
    PRINT_VARIABLE(%s, p_info->cpu.name);
    PRINT_VARIABLE(%d, p_info->cpu.id);
    PRINT_VARIABLE(%d, p_info->cpu.revision_id);
    PRINT_VARIABLE(%d, p_info->cpu.silicon_revision_major);
    PRINT_VARIABLE(%d, p_info->cpu.silicon_revision_minor);
    PRINT_VARIABLE(%d, p_info->cpu.megamodule_revision_major);
    PRINT_VARIABLE(%d, p_info->cpu.megamodule_revision_minor);
    PRINT_VARIABLE(%d, p_info->cpu.endian);
    PRINT_VARIABLE(%s, p_info->board_name);
    PRINT_VARIABLE(%d, p_info->frequency);
    PRINT_VARIABLE(%d, p_info->board_rev);
    PRINT_VARIABLE(%d, p_info->led[PLATFORM_USER_LED_CLASS].count);
    PRINT_VARIABLE(%d, p_info->led[PLATFORM_SYSTEM_LED_CLASS].count);
    PRINT_VARIABLE(%d, p_info->emac.port_count);*/

    platform_write(" BOARD NAME :%s \n", p_info->board_name);
    platform_write(" CPU NAME :%s \n", p_info->cpu.name);
    platform_write(" CPU CORE COUNT :%d \n", p_info->cpu.core_count);
    platform_write(" CPU OPERATING FREQUENCY :%d \n", p_info->frequency);
    platform_write(" EMAC PORT COUNT :%d \n", p_info->emac.port_count);

    for (i = 0; i < PLATFORM_MAX_EMAC_PORT_NUM; i++)
    {
        platform_get_emac_info (i, &emac_info);
        if (emac_info.mode == PLATFORM_EMAC_PORT_MODE_PHY)
        {
            platform_write("EMAC port %d connected to the PHY.\n", emac_info.port_num);
            platform_write("MAC Address = %02x:%02x:%02x:%02x:%02x:%02x\n",
            		emac_info.mac_address[0], emac_info.mac_address[1],
            		emac_info.mac_address[2], emac_info.mac_address[3],
            		emac_info.mac_address[4], emac_info.mac_address[5]);
        }
    }

   //NOR device
    	platform_write("Detected a Flash device - NOR type\n");
    	platform_write("----------------------------------------------\n");
		p_device = platform_device_open(PLATFORM_DEVID_NORN25Q128, 0);

		if (p_device)
		{
			platform_write("\nNOR Device: \n");
			PRINT_VARIABLE(%d, p_device->device_id);
			PRINT_VARIABLE(%d, p_device->manufacturer_id);
			PRINT_VARIABLE(%d, p_device->width);
			PRINT_VARIABLE(%d, p_device->block_count);
			PRINT_VARIABLE(%d, p_device->page_count);
			PRINT_VARIABLE(%d, p_device->page_size);
			PRINT_VARIABLE(%d, p_device->spare_size);
			PRINT_VARIABLE(%d, p_device->handle);
			PRINT_VARIABLE(%d, p_device->flags);
			PRINT_VARIABLE(%d, p_device->bboffset);
			if (p_device->bblist)
			{
				platform_write("Bad Block Table (only bad block numbers shown): \n");
				for (i=0; i < p_device->block_count; i++)
				{
					if (p_device->bblist[i] == 0x00)
					{
						platform_write("%d ", i);
					}
				}
			}
			platform_device_close(p_device->handle);
		}
		else
		{
			platform_write("Could not open the NOR device errno = 0x%x\n", platform_errno);
		}
    //NAND device
		platform_write("Detected 2 EEPROM devices\n");
		platform_write("----------------------------------------------\n");

		p_device = platform_device_open(PLATFORM_DEVID_EEPROM50, 0);

		if (p_device)
		{
			platform_write("\nEEPROM Device (@ 0x50): \n");
			PRINT_VARIABLE(%d, p_device->device_id);
			PRINT_VARIABLE(%d, p_device->manufacturer_id);
			PRINT_VARIABLE(%d, p_device->width);
			PRINT_VARIABLE(%d, p_device->block_count);
			PRINT_VARIABLE(%d, p_device->page_count);
			PRINT_VARIABLE(%d, p_device->page_size);
			PRINT_VARIABLE(%d, p_device->spare_size);
			PRINT_VARIABLE(%d, p_device->handle);
			PRINT_VARIABLE(%d, p_device->flags);
			PRINT_VARIABLE(%d, p_device->bboffset);
			platform_device_close(p_device->handle);
		}
		else
		{
			platform_write("Could not open the EEPROM @50 device errno = 0x%x\n", platform_errno);
		}

		p_device = platform_device_open(PLATFORM_DEVID_EEPROM51, 0);

		if (p_device)
		{
			platform_write("\nEEPROM Device (@ 0x51): \n");
			PRINT_VARIABLE(%d, p_device->device_id);
			PRINT_VARIABLE(%d, p_device->manufacturer_id);
			PRINT_VARIABLE(%d, p_device->width);
			PRINT_VARIABLE(%d, p_device->block_count);
			PRINT_VARIABLE(%d, p_device->page_count);
			PRINT_VARIABLE(%d, p_device->page_size);
			PRINT_VARIABLE(%d, p_device->spare_size);
			PRINT_VARIABLE(%d, p_device->handle);
			PRINT_VARIABLE(%d, p_device->flags);
			PRINT_VARIABLE(%d, p_device->bboffset);
			platform_device_close(p_device->handle);
		}
		else
		{
			platform_write("Could not open the EEPROM @51 device errno = 0x%x\n", platform_errno);
		}


    return;
}

/******************************************************************************
 * Function:    print_switch_state  
 ******************************************************************************/
 void print_switch_state(void)
{
    platform_write("User switch 1 state is %s\n",
            platform_get_switch_state(1) ? "ON" : "OFF");
}

/******************************************************************************
 * Function:    test_eeprom  
 ******************************************************************************/
 void test_eeprom(test_config * args)
{
    uint8_t   test_buf[12] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b};
    uint8_t * test_buf1;
    uint8_t * orig_buf;
	PLATFORM_DEVICE_info *p_device;


	if (args->eeprom_test_slave_address == 0x50) {
		p_device = platform_device_open(PLATFORM_DEVID_EEPROM50, 0);
	}
	else {
		p_device = platform_device_open(PLATFORM_DEVID_EEPROM51, 0);
	}

    if (p_device == NULL) {
       platform_write("test_eeprom: Could not open EEPROM device %x errno = 0x%x \n", args->eeprom_test_slave_address, platform_errno);
       return;
    }

    test_buf1 = malloc(12);
    orig_buf  = malloc(12);

    if(platform_device_read(p_device->handle, 0, orig_buf, 12) != Platform_EOK) {
        platform_write("test_eeprom: Read failed, errno = 0x%x\n", platform_errno);
        goto free;
    }

    if(platform_device_write(p_device->handle,0, test_buf, 12) != Platform_EOK) {
        platform_write("test_eeprom: Write test data failed, errno = 0x%x\n", platform_errno);
        goto free;
    }

    if(platform_device_read(p_device->handle, 0, test_buf1, 12) != Platform_EOK) {
        platform_write("test_eeprom: Read test data failed, errno = 0x%x\n",platform_errno);
        goto free;
    }

    if (memcmp(test_buf, test_buf1, 12) != 0) {
        platform_write("test_eeprom: Data verification failed\n");
        goto free;
    } else {
        platform_write("test_eeprom: passed\n");
    }

    if(platform_device_write(p_device->handle,0, orig_buf, 12) != Platform_EOK) {
        platform_write("test_eeprom: Write back original data failed, errno = 0x%x\n", platform_errno);
    }

free:
	platform_device_close(p_device->handle);
    free(test_buf1);
    free(orig_buf);
}

/******************************************************************************
 * Function:    test_nor 
 ******************************************************************************/
void test_nor(test_config * args, platform_info * p_info)
{
    uint8_t * test_buf0;
    uint8_t * test_buf1;
    uint8_t * orig_buf;
    uint32_t  i;
    uint32_t  address;
	PLATFORM_DEVICE_info 	*p_device;

#define SPI_NOR_TEST_SIZE 	10

    platform_init_flags   flags;
    platform_init_config  config;
    
    memset(&flags, 0, sizeof(platform_init_flags));
    memset(&config, 0, sizeof(platform_init_config));

    p_device = platform_device_open(PLATFORM_DEVID_NORN25Q128, 0);

    if (p_device == NULL) {
       platform_write("test_nor: Could not open NOR device  errno = 0x%x \n", platform_errno);
       return;
    }

    test_buf0 = malloc(SPI_NOR_TEST_SIZE);
    test_buf1 = malloc(SPI_NOR_TEST_SIZE);
    orig_buf  = malloc(SPI_NOR_TEST_SIZE);

    /* Initialize the test pattern */
    for (i=0; i < SPI_NOR_TEST_SIZE; i++) {
        test_buf0[i] =0x55;
    }

    address = args->nor_test_sector_number * 64 * 1024; /* each sector is 64kb */
    if(platform_device_read(p_device->handle, address, orig_buf, SPI_NOR_TEST_SIZE) != Platform_EOK) {
        platform_write("test_nor: Read failed errno = 0x%x\n", platform_errno);
        goto free;
    }

    if(platform_device_erase_block (p_device->handle, args->nor_test_sector_number) != Platform_EOK) {
    	platform_write("test_nor: Erase Failed for sector %d  errno = 0x%x\n", args->nor_test_sector_number, platform_errno);
    }
    	
    if(platform_device_read(p_device->handle, address, test_buf1, SPI_NOR_TEST_SIZE) != Platform_EOK) {
        platform_write("test_nor: Read test data failed errno = 0x%x\n", platform_errno);
    }
    
    if(platform_device_write(p_device->handle, address, test_buf0, SPI_NOR_TEST_SIZE) != Platform_EOK) {
        platform_write("test_nor: Write test data failed errno = 0x%x\n", platform_errno);
    }

    if(platform_device_read(p_device->handle, address, test_buf1, SPI_NOR_TEST_SIZE) != Platform_EOK) {
        platform_write("test_nor: Read test data failed errno = 0x%x\n", platform_errno);
    }

    if (memcmp(test_buf0, test_buf1, SPI_NOR_TEST_SIZE) != 0) {
        platform_write("test_nor: Data verification failed\n");
    } else {
        platform_write("test_nor: passed\n");
    }
    
    if(platform_device_erase_block (p_device->handle, args->nor_test_sector_number) != Platform_EOK) {
    	platform_write("test_nor: Erase Failed errno = 0x%x\n", platform_errno);
    }
    
    if(platform_device_write(p_device->handle, address, orig_buf, SPI_NOR_TEST_SIZE) != Platform_EOK) {
        platform_write("test_nor: Write back original data failed errno = 0x%x\n", platform_errno);
    }

free:
    free(test_buf0);
    free(test_buf1);
    free(orig_buf);

	platform_device_close(p_device->handle);

}

/******************************************************************************
 * Function:    test_led  
 ******************************************************************************/
 void test_led(test_config * args, platform_info * p_info)
{
    int32_t i,j;
    int32_t max_loop = args->led_test_loop_count;

    do {
        for (j = PLATFORM_USER_LED_CLASS; j < PLATFORM_END_LED_CLASS; j++) {;
            for (i = 0; i < p_info->led[j].count; i++) {
                platform_write("LED %d ON\n", i);
                platform_led(i, PLATFORM_LED_ON, (LED_CLASS_E)j);
                platform_delay(args->led_test_loop_delay);
                platform_write("LED %d OFF\n", i);
                platform_led(i, PLATFORM_LED_OFF, (LED_CLASS_E) j);
                platform_delay(args->led_test_loop_delay);                
                platform_write("LED %d ON\n", i);
                platform_led(i, PLATFORM_LED_ON, (LED_CLASS_E)j);
            }
        }
    } while (--max_loop);

    /* turn on all the LEDS (default state) after the test */
}

/******************************************************************************
 * Function:    test_internal_memory  
 ******************************************************************************/
 void test_internal_memory(test_config * args)
{
    if(platform_internal_memory_test(args->int_mem_test_core_id) != Platform_EOK) {
        platform_write("Internal memory test failed for core %d at address 0x%x \n",
            args->int_mem_test_core_id, platform_errno);
    } else {
        platform_write("Internal memory test (for core %d) passed\n",
            args->int_mem_test_core_id);
    }
}

/******************************************************************************
 * Function:    test_external_memory  
 ******************************************************************************/
 void test_external_memory(test_config * args)
{
    int32_t status;
    uint64_t regcount=1;
do
{
    status = platform_external_memory_test(args->ext_mem_test_base_addr, 
            (args->ext_mem_test_base_addr + args->ext_mem_test_length));
        if (status == PLATFORM_ERRNO_INVALID_ARGUMENT)
        {
        platform_write("Invalid Arguments passed for the test\n");        
        }
        else if (status != Platform_EOK)
        {
        platform_write("External memory test failed at address = 0x%x for iteration %d\n\n", platform_errno,regcount);
        }
        else
        {
        platform_write("External memory test passed for iteration %d\n\n",regcount);
        }
        regcount ++;
}while(args->regression);
}

/******************************************************************************
 * Function:    test_uart  
 ******************************************************************************/
 void test_uart(test_config * args)
{
    uint8_t 	message[] = "\r\nThis is a Platform UART API unit test ...\r\n";
    int 		length = strlen((char *)message);
    uint8_t 	buf;
    int 		i;
    WRITE_info 	setting;

    platform_uart_set_baudrate(args->init_config_uart_baudrate);
    
    /* Don't echo to the uart since we are testing on it */
    setting = platform_write_configure (PLATFORM_WRITE_PRINTF);

    platform_write("Open a serial port console in a PC connected to\n");
    platform_write("the board using UART and set its baudrate to %d\n", args->init_config_uart_baudrate);
    platform_write("You should see following message --- %s", message);
    platform_write("Type 10 characters in serial console\n");

    for (i = 0; i < length; i++) {
        platform_uart_write(message[i]);
    }
    
    for (i = 0; i < 10; i++) {
        platform_errno = PLATFORM_ERRNO_RESET;
        if (platform_uart_read(&buf, 30 * 10000000) == Platform_EOK) {
        	platform_write("Char %d = %c\n", i, buf);
        } else {
        	platform_write("Char %d = %c (errno: 0x%x)\n", i, buf, platform_errno);
        }
    }

    platform_write_configure (setting);
}

#if READ_EEPROM_IMAGE
#define MAX_EEPROM_SIZE     0x10000
uint32_t write_eeprom_image =   0;

void
read_eeprom_image(void)
{
    FILE                    *fp;
    char                    *eeprom50 = "eeprom50.bin";
    char                    *eeprom51 = "eeprom51.bin";
	PLATFORM_DEVICE_info    *p_device;
    uint8_t                 *buf;
    uint32_t                size;

    /* Read 64KB from EEPROM 0x50 and save it to eeprom50.bin */
    fp = fopen(eeprom50, "wb");
    if (fp == NULL)
    {
        printf("Error in opening %s file\n", eeprom50);
        return;
    }

    p_device = platform_device_open(PLATFORM_DEVID_EEPROM50, 0);
    if (p_device == NULL) 
    {
       platform_write("read_eeprom_image: Could not open EEPROM device 0x50 errno = 0x%x \n", platform_errno);
       return;
    }

    buf = (uint8_t *)IMAGE_STORE_ADDR;

    /* Read 64K bytes from EEPROM 0x50, and store in external memory */
    if(platform_device_read(p_device->handle, 0, buf, MAX_EEPROM_SIZE) != Platform_EOK) 
    {
        platform_write("read_eeprom_image: Read failed on 0x50, errno = 0x%x\n", platform_errno);
        platform_device_close(p_device->handle);
        return;
    }
    platform_device_close(p_device->handle);

    /* Write the data to a binary file */
    size = fwrite(buf, 1, MAX_EEPROM_SIZE, fp);
    if (size != MAX_EEPROM_SIZE)
    {
        platform_write("read_eeprom_image: write to binary failed\n");
    }
    fclose(fp);

    /* Read 64KB from EEPROM 0x51 and save it to eeprom51.bin */
    fp = fopen(eeprom51, "wb");
    if (fp == NULL)
    {
        printf("Error in opening %s file\n", eeprom51);
        return;
    }

    p_device = platform_device_open(PLATFORM_DEVID_EEPROM51, 0);
    if (p_device == NULL) 
    {
       platform_write("read_eeprom_image: Could not open EEPROM device 0x51 errno = 0x%x \n", platform_errno);
       return;
    }

    buf = (uint8_t *)(IMAGE_STORE_ADDR + MAX_EEPROM_SIZE);

    /* Read 64K bytes from EEPROM 0x51, and store in external memory */
    if(platform_device_read(p_device->handle, 0, buf, MAX_EEPROM_SIZE) != Platform_EOK) 
    {
        platform_write("read_eeprom_image: Read failed on 0x50, errno = 0x%x\n", platform_errno);
        platform_device_close(p_device->handle);
        return;
    }
    platform_device_close(p_device->handle);

    /* Write the data to a binary file */
    size = fwrite(buf, 1, MAX_EEPROM_SIZE, fp);
    if (size != MAX_EEPROM_SIZE)
    {
        platform_write("read_eeprom_image: write to binary failed\n");
    }
    fclose(fp);

    if (!write_eeprom_image)
    {
        return;
    }

    /* Read eeprom50.bin and write it to EEPROM 0x50 */
    fp = fopen(eeprom50, "rb");
    if (fp == NULL)
    {
        printf("Error in opening %s file\n", eeprom50);
        return;
    }

    buf = (uint8_t *)IMAGE_STORE_ADDR;
    size = fread(buf, 1, MAX_EEPROM_SIZE, fp);
    fclose(fp);
    if (size != MAX_EEPROM_SIZE)
    {
        platform_write("read_eeprom_image: read binary failed\n");
        return;
    }

    p_device = platform_device_open(PLATFORM_DEVID_EEPROM50, 0);
    if (p_device == NULL) 
    {
       platform_write("read_eeprom_image: Could not open EEPROM device 0x50 errno = 0x%x \n", platform_errno);
       return;
    }

    if(platform_device_write(p_device->handle, 0, buf, MAX_EEPROM_SIZE) != Platform_EOK) 
    {
        platform_write("read_eeprom_image: write failed on 0x50, errno = 0x%x\n", platform_errno);
        platform_device_close(p_device->handle);
        return;
    }

    platform_device_close(p_device->handle);

    /* Read eeprom51.bin and write it to EEPROM 0x51 */
    fp = fopen(eeprom51, "rb");
    if (fp == NULL)
    {
        printf("Error in opening %s file\n", eeprom51);
        return;
    }

    buf = (uint8_t *)(IMAGE_STORE_ADDR + MAX_EEPROM_SIZE);
    size = fread(buf, 1, MAX_EEPROM_SIZE, fp);
    fclose(fp);
    if (size != MAX_EEPROM_SIZE)
    {
        platform_write("read_eeprom_image: read binary failed\n");
        return;
    }

    p_device = platform_device_open(PLATFORM_DEVID_EEPROM51, 0);
    if (p_device == NULL)
    {
       platform_write("read_eeprom_image: Could not open EEPROM device 0x51 errno = 0x%x \n", platform_errno);
       return;
    }

    if(platform_device_write(p_device->handle, 0, buf, MAX_EEPROM_SIZE) != Platform_EOK)
    {
        platform_write("read_eeprom_image: write failed on 0x51, errno = 0x%x\n", platform_errno);
    }

    platform_device_close(p_device->handle);

    return;
}
#endif

