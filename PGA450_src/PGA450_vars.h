// Define GPIO Pins
#define GPIO1 P34
#define GPIO2 P35
#define LINRX P32
#define LINRXB P33
#define LINTX P23
#define RxD P30
#define TxD P31
#define LSGA P20
#define LSGB P21

extern unsigned char xdata data_FIFO[];								// FIFO Data
extern unsigned char xdata data_RAM[];								// External RAM
extern unsigned char xdata data_EEPROM[];							// EEPROM Data


// Internal RAM
extern volatile unsigned char idata RAM_UPPER_VARIABLES[];
extern volatile unsigned char idata RAM_LOWER_VARIABLES[];
extern volatile unsigned char idata pid;

extern volatile unsigned char idata EE_Data_Threshold[]; 

extern unsigned char idata UART_data[];
extern unsigned char idata UART_byte_count;

extern union {unsigned short u16; unsigned char u8[2];} TimeOfFlight;
	
// Function Declaration Section
void Initialization (void);				// Initialize PGA450
void command0 (void);
void command1 (void);
void command2 (void);
void command3 (void);
void command4 (void);
void command5 (void); 
void command6 (void); 
void command7 (void);
void burst_cap_comp (void);
//void UART_send_data (unsigned char data_packet);	// used for debug