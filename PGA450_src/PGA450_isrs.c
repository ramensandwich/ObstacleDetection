/* 
	PGA450-Q1 UART DEMO Command Overview
	Command 0 - Test UART communication.
	Command 1 - Trigger a short or long distance burst and capture with predefined drive/filter settings, burst, capture, and compare. Returns calculcated datapoint (ref Command2).
	Command 2 - Read the latest instance of threshold comparison results.
	Command 3 - Update an EEPROM value.
	Command 4 - Read all FIFO data.
	Command 5 - Burst, capture, and compare based on EEPROM configuration.
	Command 6 - Threshold Values Report.
	Command 7 - Not Used. Reserved for custom function.
*/

#include "PGA450.h"     		// Register Definitions
#include "PGA450_vars.h"     	// Variable Definitions

// Unused Interrupts //
void external0_ISR (void) interrupt 0 using 1  {}
void external1_ISR (void) interrupt 2 using 1  {}
void timer0_ISR (void) interrupt 1 using 2 {}
void timer1_ISR (void) interrupt 3 using 2 {}
void linSync_ISR (void) interrupt 8 using 3 {}
void linPID_ISR (void) interrupt 5 	using 3{}
void linSciRxData_ISR (void) interrupt 6 	using 3{}
void linSciTxData_ISR (void) interrupt 7 	using 3{}
///////////////////////


	void serial_ISR (void) interrupt 4 	using 3 {
					
	UART_data[UART_byte_count] = SBUF;
	UART_byte_count++ ;
	
	RI = 0;

		if ((SBUF != 0x00 & UART_byte_count == 1) | (SBUF != 0x55 & UART_byte_count == 2) | ((UART_data[2] & 0x0F) != data_EEPROM[31] & UART_byte_count == 3))
	{
		if (SBUF == 0x00 & UART_byte_count == 2) UART_byte_count--;		// Fix for a bug where the Checksum is 0x00
		else
		{
			UART_byte_count = 0;
			return;
		}
	}
	
	/* Command 0 - Test UART communication.
	default hex entry: 0x00, 0x55, 0x01, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x01: '0'= command 0. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x00: ignored but required checksum
	*/
	if (((UART_data[2] & 0x70) == 0x00) & (UART_byte_count == 4))
	{
		EA = 0;
		command0();
		UART_byte_count = 0;
		EA = 1;
		return;		
	}
	

	/* Command 1 - Trigger a short or long distance burst and capture with predefined drive/filter settings. Also, read first instance of threshold crossing.
	default hex entry: 0x00, 0x55, 0x11, 0x02, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x11: '1'= command 1. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x02: '00'= listen. '01'= short. '02'= long.
				[4] 0x00: ignored but required checksum
	*/
	else if (((UART_data[2] & 0x70) == 0x10) & (UART_byte_count == 5))
	{
		EA = 0;
		command1();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	
	/* Command 2 - Read first instance of threshold crossing.
	default hex entry: 0x00, 0x55, 0x21, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x21: '2'= command 2. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x00: ignored but required checksum
	*/
	
	else if (((UART_data[2] & 0x70) == 0x20) & (UART_byte_count == 4))
	{
		EA = 0;
		command2();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	
	/* Command 3 - Update EEPROM values.
	[SINGLE MODE- ENABLED] default hex entry: 0x00, 0x55, 0x31, 0x00, 0xFF, 0x00
	
	whre (SINGLE)
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x31: '3'= command 3. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x00: '00'= EEPROM Addr
				[4] 0xFF: 'FF'= EEPROM Data
				[5] 0x00: ignored but required checksum
	
	*/
	else if (((UART_data[2] & 0x70) == 0x30) & (UART_byte_count == 6)) // else if (((UART_data[2] & 0x70) == 0x30) & (UART_byte_count == 36))
	{
		EA = 0;
		command3();
		UART_byte_count = 0;
		EA = 1;
		return;
	}	

	/* Command 4 - Read all FIFO data.
	default hex entry: 0x00, 0x55, 0x41, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x41: '4'= command 4. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x00: ignored but required checksum
	*/
	else if (((UART_data[2] & 0x70) == 0x40) & (UART_byte_count == 4))
	{
		EA = 0;
		command4();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	

	/* 
	Command 5 - Burst/Capture using EEPROM drive/receive configuration.
	default hex entry (long mode): 0x00, 0x55, 0x51, 0x02, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x51: '5'= command 5. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x02: Use '0'=Listen, '1'=Short, '2'=Long
				[4] 0x00: ignored but required checksum		
				
	*/
	else if (((UART_data[2] & 0x70) == 0x50) & (UART_byte_count == 5))
	{
		EA = 0;
		command5();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	
	/* Command 6 - Threshold Values Report for selected mode of operation (short or long).
	default hex entry: 0x00, 0x55, 0x61, 0x02, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x61: '6'= command 2. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x02: Use '0'=Listen, '1'=Short, '2'=Long
				[4] 0x00: ignored but required checksum
	*/	
	
	else if (((UART_data[2] & 0x70) == 0x60) & (UART_byte_count == 5))
	{
		EA = 0;
		command6();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	
	/* Command 7 - Not used.
	default hex entry: 0x00, 0x55, 0x71, 0x00
	where 
				[0] 0x00: break field
				[1] 0x55: synchronization field
				[2] 0x71: '7'= command 2. '1'= sensor address set in EEPROM Addr 0x31
				[3] 0x00: ignored but required checksum
	*/	
	
	else if (((UART_data[2] & 0x70) == 0x70) & (UART_byte_count == 4))
	{
		EA = 0;
		command7();
		UART_byte_count = 0;
		EA = 1;
		return;
	}
	
	else
	{
		return;
		// do nothing
	}
	
}
