                
#include "PGA450.h"     		// Register Definitions
#include "PGA450_vars.h"     	// Variable Definitions

unsigned char xdata data_FIFO[768] _at_ 0x0000;		 	// FIFO Data
unsigned char xdata data_RAM[256] _at_ 0x0300;			// External RAM
unsigned char xdata data_EEPROM[32] _at_ 0x0400;		// EEPROM

volatile unsigned char idata RAM_UPPER_VARIABLES[10] _at_ 0x80;
volatile unsigned char idata RAM_LOWER_VARIABLES[10] _at_ 0x40;

volatile unsigned char idata pid _at_ 0x90;

volatile unsigned char idata EE_Data_Threshold[7];

unsigned char idata UART_data[12];
unsigned char idata UART_byte_count;

union{unsigned short u16; unsigned char u8[2];} TimeOfFlight;
