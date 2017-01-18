                
#include "PGA450.h"     		// Register Definitions
#include "PGA450_vars.h"     	// Variable Definitions

// ** INITIALIZES PGA450 PORTS, ESFRs, LIN, TIMERS, AND INTERRUPTS **
void Initialization (void){	
	
// * INITIALIZE PORTS *
  	GPIO1 = 1;
  	GPIO2 = 1;
		TxD = 1;
		RxD = 1;
  	LSGA=0;
  	LSGB=0;
  	LINTX=0;
	
		GPIO_CTRL=0x00; 		// TX-weak
		

// * INITIALIZE ESFRs *
  	VREG_SEL = 0x03;	  	// VREG 5V mode
  	PWR_MODE = 0x02; 		// VREG_EN(D1)=1, ACTIVE_EN(D0)=0, low power state until ready to transmit ultrasonic burst
  	CLK_SEL = 0x00;  		// Internal Clock WITH OUT LIN SYNC   		
		DP_SCI_CTRL = 0x00; 	// FIFO loaded with LPF output
  	
	/*
	//BPF, Ts = 1MHz, CF=58KHz, BW=4KHz
  	BPF_B1_MSB = 0x03;
  	BPF_B1_LSB = 0x2D;
  	BPF_A2_MSB = 0xEC;
  	BPF_A2_LSB = 0x3D;
  	BPF_A3_MSB = 0xF9;		
  	BPF_A3_LSB = 0xA5;
	*/

#define DOWNSAMPLE_50				// 50 downsamples by changing this definition to maximize long distance detect to 7.28m
//#define DOWNSAMPLE_40				// 40 downsamples by changing this definition
//#define DOWNSAMPLE_25				// 25 downsamples by changing this definition

#ifdef DOWNSAMPLE_50 				// LPF CF = 4KHz, 50 downsamples
	DOWNSAMPLE = 0x32;  	        // 50us output rate
  	LPF_B1_MSB = 0x35;
  	LPF_B1_LSB = 0xDD;
  	LPF_A2_MSB = 0x14;
  	LPF_A2_LSB = 0x46;
#endif

#ifdef DOWNSAMPLE_40 				// LPF CF = 4KHz, 40 downsamples
	DOWNSAMPLE = 0x28;  	        // 40us output rate
  	LPF_B1_MSB = 0x2D;
  	LPF_B1_LSB = 0x68;
  	LPF_A2_MSB = 0x25;
  	LPF_A2_LSB = 0x30;
#endif

#ifdef DOWNSAMPLE_25					//	LPF CF = 4KHz, 25 downsamples
	DOWNSAMPLE = 0x19;  	            // 25us output rate
	LPF_B1_MSB = 0x1F;
	LPF_B1_LSB = 0x64;
	LPF_A2_MSB = 0x41;
	LPF_A2_LSB = 0x38;
#endif

// * INITIALIZE LIN * 
	LIN_SCI = 0x00; 			// Select LIN
	LIN_CFG = 0x40; 			// CRC set to ENHANCED

// * INITIALIZE TIMERS *
	TMOD = TMOD | 0x01;   	// Timer0, free running, 16 bit, mode 8
	TL0 = 0x00;	 						// Clear timer0 counter
	TH0 = 0x00;							// Clear timer0 counter

	TMOD = TMOD | 0x20;	 	// Timer1 (serial communication), 8bit mode
	TL1 = 0x00;						// Clear timer1 coutner
	TH1 = 0xE6;						// Clear timer1 coutner //Set UART Baud to 19.2 kbps TH1 = 0xE6;0xCC
	TCON = TCON | 0x40;		// Run timer1

// * INITIALIZE SERIAL COMMUNICATION *
	SM0 = 0;
	SM1 = 1; 					// Serial Mode is 8-bit UART with baud rate set by Timer 1
	SM2 = 0; 					// Multiprocessor communication is not enabled
	TB8 = 0; 					// 9th bit is 0
	REN = 1; 					// Enable Receiver
	PCON = PCON | 0x80; 		// Set PCON.7 to enable double baud rate

// * INITIALIZE INTERRUPTS * 
   ES = 1;						//Enable Serial Port Interrupt
	 EA = 1; 						// Enable All Interrupts

// * LOAD EEPROM Values *
	EE_CTRL = 0x02;
	while (EE_CTRL == 0x02){}
		
		
// * INITIALIZE GLOBAL VARS *
		UART_byte_count = 0;
}  