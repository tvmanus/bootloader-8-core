/*
 * bbt.h
 *
 *  Created on: Feb 25, 2013
 *      Author: nachiappanr
 */

#ifndef BBT_H_
#define BBT_H_


typedef struct test_config
{
    uint32_t init_config_pll1_pllm;
    uint32_t init_config_uart_baudrate;
    uint32_t nor_test_sector_number;
    uint32_t eeprom_test_slave_address;
    uint32_t led_test_loop_count;
    uint32_t led_test_loop_delay;
    uint32_t ext_mem_test_base_addr;
    uint32_t ext_mem_test_length;
    uint32_t int_mem_test_core_id;
    uint32_t print_info;
    uint8_t regression;
    uint8_t phytestmode;

} test_config;


/*
The inputs to the test application can be controlled
by the following file. User need to create this file in
pdk_#_##_##_##\packages\ti\platform\lib\platform_utils_test\bin
directory.

The syntax to the input file is as follows
<input string> = <value 1 => enable, 0 => disable
*/

//char    input_file_name[] = "../testconfig/platform_test_input.txt";
//#define MAX_LINE_LENGTH 40

/* The input strings for the input config file is given below */
/* Input flags */

#define INIT_PLL1             "init_pll"
#define INIT_DDR3             "init_ddr"
#define INIT_UART             "init_uart"
#define INIT_TCSL             "init_tcsl"
#define INIT_PHY              "init_phy"
#define INIT_ECC              "init_ecc"

#define PRINT_INFO            "print_info"
#define PRINT_CURRENT_CORE_ID "print_current_core_id"
#define PRINT_SWITCH_STATE    "print_switch_state"
#define TEST_EEPROM           "test_eeprom"
#define TEST_NOR              "test_nor"
#define TEST_LED              "test_led"
#define TEST_UART             "test_uart"
#define TEST_EXT_MEM          "run_external_memory_test"
#define TEST_INT_MEM          "run_internal_memory_test"

/* Input parameters */
#define INIT_CONFIG_PLL1_PLLM      "init_config_pll1_pllm"
#define INIT_CONFIG_UART_BAUDRATE  "init_config_uart_baudrate"

#define EEPROM_TEST_SLAVE_ADDRESS  "eeprom_test_slave_address"

#define LED_TEST_LOOP_COUNT        "led_test_loop_count"
#define LED_TEST_LOOP_DELAY        "led_test_loop_delay"

#define EXT_MEM_TEST_BASE_ADDR     "ext_mem_test_base_addr"
#define EXT_MEM_TEST_LENGTH        "ext_mem_test_length"

#define INT_MEM_TEST_CORE_ID       "int_mem_test_core_id"

/* The default values for the input strings are given below */
#define DEF_INIT_CONFIG_PLL1_PLLM      0
#define DEF_INIT_CONFIG_UART_BAUDRATE  115200

#define DEF_NAND_TEST_BLOCK_NUMBER    1000

#define DEF_NOR_TEST_SECTOR_NUMBER    10

#define DEF_EEPROM_TEST_SLAVE_ADDRESS1 0x51
#define DEF_EEPROM_TEST_SLAVE_ADDRESS0 0x50

#define DEF_LED_TEST_LOOP_COUNT    1
#define DEF_LED_TEST_LOOP_DELAY    3000000

#define DEF_EXT_MEM_TEST_BASE_ADDR 0x80000000
#define DEF_EXT_MEM_TEST_LENGTH    0x1fffffff //0x20000000

#define DEF_INT_MEM_TEST_CORE_ID   1

#undef TEST_READ_IMAGE

#ifdef TEST_READ_IMAGE
#define IMAGE_STORE_ADDR        0x80000000
#define READ_EEPROM_IMAGE       1
#define READ_NAND_OOB_IMAGE     1
#endif
/*
typedef enum
{
	ZERO,
	SYSTEM_CLK_TEST,
	PROGRAM_LOAD_AND_MEMORY_TEST,
	GPIO_TEST,
	FPGA_INTERRUPT_TEST,
	SPI_FLASH_TEST,
	SPI_FPGA_TEST,
	SRIO_TEST,
	ETHERNET_TEST,
	CONFIG_SWITCH_TEST,
	UART_TEST
}MainMenu;

typedef enum {
	INIT_STATE,
	SYSCLK_TEST,
	PROGRAM_LOAD_TEST=11,
	INTERNAL_MEMORY_TEST,
	DDR3_MEMORY_TEST,
	EEPROM_TEST,
	BOOT_GREEN_LED_TEST,
	BOOT_RED_LED_TEST,
	HEALTH_GREEN_LED_TEST,
	HEALTH_RED_LED_TEST,
	SRIO_ACTIVE_LED_TEST,
	GPIO_SET_VOLTAGE_TEST,
	GPIO_CLEAR_VOLTAGE_TEST,
	FPGA_INTR_TEST,
	FLASH_SPI_SPEED_TEST_25MHZ,
	FLASH_SPI_READ_TEST,
	FLASH_SPI_WRITE_TEST,
	FPGA_SPI_SPEED_TEST_10MHZ,
	FPGA_SPI_TEST,
	SRIO_1_LOOPBACK_TEST,
	CONFIGURATION_SWITCH_TEST,
	ETHERNET_PHY_LINK_STATUS_TEST,
	ETHERNET_DATA_TEST,
	UART_TST
}BBTTestID;
*/
#define PRINT_VARIABLE(F, VAR) platform_write(#VAR"\t= "#F"\n", VAR)

void print_current_core_id(void);
void print_platform_info(platform_info * p_info, test_config * args);
void test_eeprom(test_config * args);
void test_nand(test_config * args);
void test_nor(test_config * args, platform_info * p_info);
void test_led(test_config * args, platform_info * p_info);
void test_internal_memory(test_config * args);
void test_external_memory(test_config * args);
void test_uart(test_config * args);
void bbt_internal_mem_test(test_config * args );
void bbt_external_mem_test(test_config * args );
void bbt_ddr3_regresssion_mem_test(test_config * args);
void bbt_eeprom_mem_test(test_config * args);
void bbt_flash_spi_test(test_config *args);
void bbt_flash_readwrite(test_config * args);
void bbt_flash_erase(test_config * args);
void bbt_gpio_led_test(test_config * args,uint32_t);
void ProgLoad_Test(void);
void bbt_fpga_reset_test(void);
void bbt_gpio_clear_test(void);
void bbt_fpga2dsp_interrupt_test();
void bbt_fpga_spiloopback_test(test_config* args);
void bbt_ReadFpgaId(test_config* args);
void bbt_SrioloopbackTest(test_config* args);
void bbt_eth_phy_reg_status(test_config *args);
void bbt_phy_test_node (test_config  *args);
void bbt_srio_init(test_config* args);
void bbt_fpga_remote_prog();
void get_input(uint8_t*);
void test_flash(void);

#endif /* BBT_H_ */
