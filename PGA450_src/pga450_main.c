      
#include "PGA450.h"     		// Register Definitions
#include "PGA450_vars.h"     	// Variable Definitions
#include <stdio.h>

#define BurstCaptureComparePrint; //when enabled: combines burst, capture, compare, and printing results to terminal on single command.

union {unsigned short u16; unsigned char u8[2];} FifoWritePointer;
union {unsigned short u16; unsigned char u8[2];} FRT_T1;
union {unsigned short u16; unsigned char u8[2];} FRT_T2;
volatile unsigned short lcv;									// temporary loop count variable
volatile unsigned short lcvTemp;							// temporary loop count variable
volatile unsigned char MaskEcho;							// Counter for masking data after an echo has been found
volatile unsigned char DetectionThreshold;
volatile unsigned char DetectionThresholdTemp;
volatile unsigned char DetectIndex; 
volatile unsigned char echo_data;
volatile unsigned short thrEndLevel = 0;
volatile unsigned short thrLvlModInterval = 0;
volatile unsigned short thrIgnore = 0;
volatile unsigned short thrEndStart = 0;

void main (void){
  Initialization();
	
  while (1){} /* Loop forever */
}

char checksum_add_cary (char param1, char param2){
	
	union {unsigned short u16; unsigned char u8[2];} Sum;
	
	Sum.u16 = param1+param2;

	return ((Sum.u8[0] != 0) ? (Sum.u8[1] + 1) : Sum.u8[1]);
}


void UART_send_data (unsigned char data_packet){
	
	ES = 0;
	SBUF = data_packet;
	while(~TI) {}; 
	TI = 0;
	ES = 1;
}

void setThreshold(int mode)
{
	if (mode == 0){		//short mode
				EE_Data_Threshold[0] = data_EEPROM[0] & 0x0F;
				EE_Data_Threshold[1] = data_EEPROM[1] & 0x0F;
				EE_Data_Threshold[2] = data_EEPROM[2] & 0x0F;
				EE_Data_Threshold[3] = data_EEPROM[3] & 0x0F;
				EE_Data_Threshold[4] = data_EEPROM[4] & 0x0F;
				EE_Data_Threshold[5] = data_EEPROM[5] & 0x0F;
				EE_Data_Threshold[6] = data_EEPROM[6] & 0x0F;
				thrEndStart = data_EEPROM[7] & 0x0F;
				thrEndLevel = data_EEPROM[8] & 0x0F; 					// Fixed threshold until end of FIFO
				thrIgnore = data_EEPROM[9] & 0x0F; 						// Initialize threshold with offset from beginnning of FIFO
				thrLvlModInterval = data_EEPROM[10] & 0x0F; 	// threshold level change interval accross FIFO
	}
	else 							//long mode
	{
				EE_Data_Threshold[0] = data_EEPROM[0] >> 4;
				EE_Data_Threshold[1] = data_EEPROM[1] >> 4;
				EE_Data_Threshold[2] = data_EEPROM[2] >> 4;
				EE_Data_Threshold[3] = data_EEPROM[3] >> 4;
				EE_Data_Threshold[4] = data_EEPROM[4] >> 4;
				EE_Data_Threshold[5] = data_EEPROM[5] >> 4;
				EE_Data_Threshold[6] = data_EEPROM[6] >> 4;
				thrEndStart = data_EEPROM[7] >> 4;
				thrEndLevel = data_EEPROM[8] >> 4; 				// Fixed threshold until end of FIFO
				thrIgnore = data_EEPROM[9] >> 4; 					// Initialize threshold with offset from beginnning of FIFO
				thrLvlModInterval = data_EEPROM[10] >> 4; // threshold level change interval accross FIFO
	}
				
}


void command0 (void){		// Transmit 2 bytes to Master	
	
	UART_send_data (0x12);
	UART_send_data (0x34);
	UART_send_data (~(checksum_add_cary (0x12, 0x34)));
}
								
void command1 (void){		// Do distance Measurment with predefined driver/receive settings or UART entered
	
		if (UART_data[3] > 2)	return;		// Valid data for command1 is only 0 - Liten mode ; 1 - Short Distance Detection; 2 - Long Distance Detection;

		BPF_B1_MSB = 0x03;
  	BPF_B1_LSB = 0x2D;
  	BPF_A2_MSB = 0xEC;
  	BPF_A2_LSB = 0x3D;
  	BPF_A3_MSB = 0xF9;		
  	BPF_A3_LSB = 0xA5;
  	LPF_B1_MSB = 0x35;
  	LPF_B1_LSB = 0xDD;
  	LPF_A2_MSB = 0x14;
  	LPF_A2_LSB = 0x46;	
		BURST_MODE = 0x00;     				// Push Pull mode
		BURST_ONA_MSB = 0x00;
		BURST_ONA_LSB = 0x8A;  				// ON Time = 8.6us 16MHz/58KHz/2
		BURST_OFFA_MSB = 0x00;
		BURST_OFFA_LSB = 0x8A;		 		// OFF Time = 8.6us
		DEADTIME = 0x05;							// Dead time between burst phases to limit shoot through current
		SAT_DEGLITCH = 0x09;   				// 2us per count || 1/58kHz (17.2uS)
	
		if (UART_data[3] == 2) 				// Long Distance Measurement
			{			
				PULSE_CNTA = 0x12; 				// # pulses during burst
				BLANKING_TIMER = 0xFF; 		// Waits #*16 uS after ECHO_EN = 1 to fill up FIFO (Ignores very close range data)
				FIFO_CTRL = 0x06;					// NO FIFO Rollover, 8 LSB
				CONTROL_1 = 0x01; 				// SAT threshold 300mV
				setThreshold(1); 					// set long threshold levels													
			}

			else if (UART_data[3] == 1) // Short Distance Measurment
			{	   					
				PULSE_CNTA = 0x01;				// # pulses during burst
				BLANKING_TIMER = 0x37;		// Waits #*16 uS after ECHO_EN = 1 to fill up FIFO (Ignores very close range data)
				FIFO_CTRL = 0x05;					// NO FIFO Rollover, 8 MSB mode
				CONTROL_1 = 0x01; 				// SAT threshold 300mV		
				setThreshold(0); 					// set short threshold levels
			}
			
			else 								// Listen Mode
			{
				setThreshold(1); 	//set long threshold levels
			}
										
	burst_cap_comp(); 			// Burst,Capture,Compare	

	#ifdef BurstCaptureComparePrint
		command2(); 					// Enabled: send and receive data on single command.	
	#endif
}
						
void command2 (void){		// Transmit Results (2 bytes) to Master
	
	UART_send_data (TimeOfFlight.u8[0]);
	UART_send_data (TimeOfFlight.u8[1]);
	UART_send_data (~(checksum_add_cary (TimeOfFlight.u8[0], TimeOfFlight.u8[1])));
}		
						
void command3 (void){		// Write EEPROM

	
	data_EEPROM[UART_data[3]] = UART_data[4];
	
	EE_CTRL = 0x01;
	while (EE_CTRL == 0x01){}

	UART_send_data(data_EEPROM[UART_data[3]]);
		
}

void command4 (void){		// Transmit all FIFO data (768 bytes) to Master
	for (lcv = 0; lcv<768; lcv++)
	{
		UART_send_data (data_FIFO[lcv]);
	}
}

void command5 (void){		// Burst and capture based on EEPROM values
	
	PULSE_CNTA = data_EEPROM[11];							  	
	BLANKING_TIMER = data_EEPROM[12];
	FIFO_CTRL = data_EEPROM[13];
	DOWNSAMPLE = data_EEPROM[14];
	CONTROL_1 = data_EEPROM[15];
	BURST_MODE = data_EEPROM[16];
	BURST_ONA_LSB = data_EEPROM[17];
	BURST_OFFA_LSB = data_EEPROM[18];
	DEADTIME = data_EEPROM[19];
	SAT_DEGLITCH = data_EEPROM[20];
	BPF_B1_MSB = data_EEPROM[21];
	BPF_B1_LSB = data_EEPROM[22];
	BPF_A2_MSB = data_EEPROM[23];
	BPF_A2_LSB = data_EEPROM[24];
	BPF_A3_MSB = data_EEPROM[25];
	BPF_A3_LSB = data_EEPROM[26];
	LPF_B1_MSB = data_EEPROM[27];
	LPF_B1_LSB = data_EEPROM[28];
	LPF_A2_MSB = data_EEPROM[29];
	LPF_A2_LSB = data_EEPROM[30];
	
	if (UART_data[3] == 1)
		{
			setThreshold(0); //set short threshold levels.	
		}		
	else
		{
			setThreshold(1); //set long threshold levels.	
		}
		
		burst_cap_comp(); // burst, capture, compare
	
	#ifdef BurstCaptureComparePrint
		command2(); // Enabled: send and receive data on single command.	
	#endif
}

void burst_cap_comp (void){		// Burst, Capture, Compare
	
	FifoWritePointer.u16 = 0;
	FRT_T1.u16 = 0;
	FRT_T2.u16 = 0;
	TimeOfFlight.u16 = 0;
	MaskEcho = 0;
	DetectIndex = 1;
		
	PWR_MODE = 0x03; 								// VREG_EN (D1)=1, ACTIVE_EN (D0)=1, ready for ultrasonic burst	  
	EN_CTRL = 0x00;  								// Clear FIFO memory before burst     

	
	if (UART_data[3] != 0) 
	{
			while(STATUS2 & 0x01 == 0) {}		// Wait for VREG to be ready
			EN_CTRL = 0x85;       					// Enable Burst and saturation check, as well as log Free Running Timer
				
			//Record time
			FRT_T1.u8[0]=FRT_MSB;
			FRT_T1.u8[1]=FRT_LSB;
									
			while(STATUS2 & 0x02 == 0){}		// wait for decay done to be set			
			// If needed, user can check for the decay time capture here to check for an effective burst as a diagnostic
	}
	else	EN_CTRL = 0x80;						// Log Free Running Timer only. Used for Listen only mode, or triangulation.	
			
	PWR_MODE = 0x01;								// VREG disabled for better noise, ACTIVE mode remains enabled	
	EN_CTRL = 0x0C;									// Enable Echo Capture
			
		DetectionThreshold = 255;
	
		for(lcv=thrIgnore;lcv<767;lcv++)
			{
				// Read FIFO Pointer coherently
				while ( lcv >= FifoWritePointer.u16 )
					{	     			
						FifoWritePointer.u8[0] = FIFO_POINTER_MSB;
						FifoWritePointer.u8[1] = FIFO_POINTER_LSB;
						if ( FifoWritePointer.u8[0] != FIFO_POINTER_MSB ) // Check if coherent
							{ 	     	
								FifoWritePointer.u8[0] = FIFO_POINTER_MSB;
								FifoWritePointer.u8[1] = FIFO_POINTER_LSB;
							}		 
					}  			 			

			if ((UART_data[3] == 2)) 
				{	// long distance  - threshold assignment  
				if (lcv > (thrEndStart*40)) 
					{					
						DetectionThreshold = thrEndLevel*5; // modify to adjust last threshold level value based on noise floor
					}
				else if (lcv == ((thrLvlModInterval*8)*(DetectIndex)) && (DetectIndex < 7))
				{
						if (DetectIndex < 8)
						{
							DetectionThreshold = 12 + (EE_Data_Threshold[DetectIndex-1]<<3);
							DetectIndex++;
						}
				}					
				else
					{
					}			
				}					
				
			else if ((UART_data[3] == 1)) 
				{			 		 // short distance  - threshold assignment  
				if (lcv > (thrEndStart*8)) {					
					DetectionThreshold = thrEndLevel*2; // modify to adjust last threshold level value based on noise floor	
					}				
				else if (lcv == ((thrLvlModInterval*2)*(DetectIndex)) && (DetectIndex < 7)) 
					{ 
						if (DetectIndex < 8)
						{
							DetectionThreshold = 4 + (EE_Data_Threshold[DetectIndex]<<4);
							DetectIndex++;
						}
					}
				else 
					{	
					}
				}
				
			else
				{
					//do nothing
				}				
				
			if ( MaskEcho == 0){									
				if ( data_FIFO[lcv] > DetectionThreshold) {
				
					EN_CTRL = 0x8C;			//log free running timer						
					FRT_T2.u8[0]=FRT_MSB;
					FRT_T2.u8[1]=FRT_LSB;
					if (FRT_T1.u16 > FRT_T2.u16) {
						TimeOfFlight.u16 = 65535+FRT_T2.u16-FRT_T1.u16;
					}
					else {
						TimeOfFlight.u16 = FRT_T2.u16-FRT_T1.u16;	
					}
					MaskEcho = 1;
					//break;	// when enabled, break for loop as soon as an object is found, and not all FIFO will be filled
						
				}
					
			}	 					
		}			
		if (MaskEcho == 0)  TimeOfFlight.u16 = 65535;
																		
		PWR_MODE = 0x02; 		// VREG_EN (D1)=1, ACTIVE_EN (D0)=0, ready for ultrasonic burst
		EN_CTRL = 0x00;			// Clear all enables
}

void command6 (void){		// Threshold Values Report

	MaskEcho = 0;
	DetectIndex = 1;

	if (UART_data[3] == 1)
		{
			setThreshold(0); //set short threshold levels.	
		}		
	else
		{
			setThreshold(1); //set long threshold levels.	
		}
	
		DetectionThreshold = 255;
	
	
		for(lcv=thrIgnore;lcv<767;lcv++)
			{			 			

			if ((UART_data[3] == 2)) 
				{	// long distance  - threshold assignment  
				if (lcv > (thrEndStart*40)) 
					{					
						DetectionThreshold = thrEndLevel*5; // modify to adjust last threshold level value based on noise floor
					}
				else if (lcv == ((thrLvlModInterval*8)*(DetectIndex)))
				{
						if (DetectIndex < 8)
						{
							DetectionThreshold = 12 + (EE_Data_Threshold[DetectIndex-1]<<3);
							DetectIndex++;
						}
				}					
				else
					{
					}			
				}					
				
			else if ((UART_data[3] == 1)) 
				{	// short distance  - threshold assignment  
				if (lcv > (thrEndStart*8)) {					
					DetectionThreshold = thrEndLevel*2; // modify to adjust last threshold level value based on noise floor	
					}				
				else if (lcv == ((thrLvlModInterval*2)*(DetectIndex)))
					{ 
						if (DetectIndex < 8)
						{
							DetectionThreshold = 4 + (EE_Data_Threshold[DetectIndex]<<4);
							DetectIndex++;
						}
					}
				else 
					{	
					}
				}
				
			else
				{
					//do nothing
				}
				
				if(DetectionThreshold != DetectionThresholdTemp)
					{
						if(lcv>255)
						{
							if(lcv>511)
							{
								lcvTemp = lcv-511;
							}
							else
							{
							lcvTemp = lcv-256;
							}
						}
						else
						{
							lcvTemp = lcv;
						}
						UART_send_data (lcvTemp);
						UART_send_data (DetectionThreshold);						
					}
				DetectionThresholdTemp = DetectionThreshold;
				
			}				
				
}

void command7 (void){		// Not Used
	//Do nothing
	UART_send_data (0x9A);
	UART_send_data (0xBC);
	UART_send_data (~(checksum_add_cary (0x9A, 0xBC)));
}