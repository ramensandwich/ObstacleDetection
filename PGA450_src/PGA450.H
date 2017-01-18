// SFR Registers
sfr P0   = 0x80;
sfr SP   = 0x81;
sfr DPL  = 0x82;					   
sfr DPH  = 0x83;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr P1   = 0x90;
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr P2   = 0xA0;
sfr IE   = 0xA8;
sfr P3   = 0xB0;
sfr IP   = 0xB8;
sfr PSW  = 0xD0;
sfr ACC  = 0xE0;
sfr IE1  = 0xE8;
sfr B    = 0xF0;
sfr IP1  = 0xF8;

/* ESFR Registers */
sfr BPF_B1_MSB        = 0x92;
sfr BPF_B1_LSB        = 0x93;
sfr BPF_A2_MSB        = 0x94;
sfr BPF_A2_LSB        = 0x95;
sfr BPF_A3_MSB        = 0x96;
sfr BPF_A3_LSB        = 0x97;
sfr LPF_B1_MSB        = 0xA1;
sfr LPF_B1_LSB        = 0xA2;
sfr LPF_A2_MSB        = 0xA3;
sfr LPF_A2_LSB        = 0xA4;
sfr DOWNSAMPLE        = 0xA5;
sfr BURST_ONA_MSB     = 0xA6;
sfr BURST_ONA_LSB     = 0xA7;
sfr BURST_OFFA_MSB    = 0xA9;
sfr BURST_OFFA_LSB    = 0xAA;
sfr BURST_ONB_MSB     = 0xAB;
sfr BURST_ONB_LSB     = 0xAC;
sfr BURST_OFFB_MSB    = 0xAD;
sfr BURST_OFFB_LSB    = 0xAE;
sfr PULSE_CNTA        = 0xAF;
sfr PULSE_CNTB        = 0xB1;
sfr DEADTIME          = 0xB2;
sfr BURST_MODE        = 0xB3;
sfr TEMP_SENS         = 0xB4;
sfr SAT_DEGLITCH      = 0xB5;
sfr SAT_TIME          = 0xB6;
sfr CONTROL_1         = 0xB7;
sfr BLANKING_TIMER    = 0xB9;
sfr FRT_MSB           = 0xBA;
sfr FRT_LSB           = 0xBB;
sfr GPIO_CTRL         = 0xBC;
sfr CLK_SEL           = 0xBD;
sfr WD_EN             = 0xBE;
sfr LIN_SCI           = 0xBF;
sfr EE_CTRL           = 0xC0;
sfr STATUS1           = 0xC1;
sfr STATUS2           = 0xC2;
sfr PWR_MODE          = 0xC3;
sfr DP_SCI_CTRL       = 0xC4;
sfr FIFO_CTRL         = 0xC5;
sfr ECHODATA_MSB      = 0xC6;
sfr ECHODATA_LSB      = 0xC7;
sfr EN_CTRL           = 0xC8;
sfr RX_DATA0          = 0xC9;
sfr RX_DATA1          = 0xCA;
sfr RX_DATA2          = 0xCB;
sfr RX_DATA3          = 0xCC;
sfr RX_DATA4          = 0xCD;
sfr RX_DATA5          = 0xCE;
sfr RX_DATA6          = 0xCF;
sfr RX_DATA7          = 0xD1;
sfr LIN_PID           = 0xD2;
sfr TX_DATA0          = 0xD3;
sfr TX_DATA1          = 0xD4;
sfr TX_DATA2          = 0xD5;
sfr TX_DATA3          = 0xD6;
sfr TX_DATA4          = 0xD7;
sfr TX_DATA5          = 0xD8;
sfr TX_DATA6          = 0xD9;
sfr TX_DATA7          = 0xDA;
sfr DATA_CNT          = 0xDB;
sfr LIN_CFG           = 0xDC;
sfr LIN_CTRL          = 0xDD;
sfr LIN_STATUS        = 0xDE;
sfr FIFO_POINTER_MSB  = 0xDF;
sfr FIFO_POINTER_LSB  = 0xE1;
sfr VREG_SEL          = 0xE2;
sfr SYNC_COUNT_MSB    = 0xE3;
sfr SYNC_COUNT_LSB    = 0xE4;
sfr TEMP_DAC_CTRL     = 0xE5;
sfr OSC_SYNC_CTRL     = 0xE6;
sfr ANALOG_MUX        = 0xE9;
sfr DIGITAL_MUX       = 0xEA;

/*  BIT Registers  */
/* P0   */
sbit P07  = P0^7;
sbit P06  = P0^6;
sbit P05  = P0^5;
sbit P04  = P0^4;
sbit P03  = P0^3;
sbit P02  = P0^2;
sbit P01  = P0^1;
sbit P00  = P0^0;

/*  P1  */
sbit P17 = P1^7;
sbit P16 = P1^6;
sbit P15 = P1^5;
sbit P14 = P1^4;
sbit P13 = P1^3;
sbit P12 = P1^2;
sbit P11 = P1^1;
sbit P10 = P1^0;

/*  P2  */
sbit P27  = P2^7;
sbit P26  = P2^6;
sbit P25  = P2^5;
sbit P24  = P2^4;
sbit P23  = P2^3;
sbit P22  = P2^2;
sbit P21  = P2^1;
sbit P20  = P2^0;

/*  P3  */
sbit P37  = P3^7;
sbit P36  = P3^6;
sbit P35  = P3^5;
sbit P34  = P3^4;
sbit P33  = P3^3;
sbit P32  = P3^2;
sbit P31  = P3^1;
sbit P30  = P3^0;

/*  TCON  */
sbit TF1  = TCON^7;
sbit TR1  = TCON^6;
sbit TF0  = TCON^5;
sbit TR0  = TCON^4;
sbit TCON_IE1  = TCON^3;
sbit IT1  = TCON^2;
sbit IE0  = TCON^1;
sbit IT0  = TCON^0;

/*  SCON  */
sbit SM0  = SCON^7; // alternatively "FE"
sbit FE   = SCON^7;
sbit SM1  = SCON^6;
sbit SM2  = SCON^5;
sbit REN  = SCON^4;
sbit TB8  = SCON^3;
sbit RB8  = SCON^2;
sbit TI   = SCON^1;
sbit RI   = SCON^0;

/*  IE   */
sbit EA   = IE^7;
sbit EI5  = IE^5;
sbit ES   = IE^4;
sbit ET1  = IE^3;
sbit EX1  = IE^2;
sbit ET0  = IE^1;
sbit EX0  = IE^0;

/*  IE1   */
sbit EI13 = IE1^7;
sbit EI12 = IE1^6;
sbit EI11 = IE1^5;
sbit EI10 = IE1^4;
sbit EI9  = IE1^3;
sbit EI8  = IE1^2;
sbit EI7  = IE1^1;
sbit EI6  = IE1^0;

/*  IP   */ 
sbit PI5  = IP^5;
sbit PS   = IP^4;
sbit PT1  = IP^3;
sbit PX1  = IP^2;
sbit PT0  = IP^1;
sbit PX0  = IP^0;

/*  IP1   */ 
sbit PI13 = IP1^7;
sbit PI12 = IP1^6;
sbit PI11 = IP1^5;
sbit PI10 = IP1^4;
sbit PI9  = IP1^3;
sbit PI8  = IP1^2;
sbit PI7  = IP1^1;
sbit PI6  = IP1^0;

/*  PSW   */
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit F1   = PSW^1;
sbit P    = PSW^0;

/*  ACC   */
sbit ACC7 = ACC^7;
sbit ACC6 = ACC^6;
sbit ACC5 = ACC^5;
sbit ACC4 = ACC^4;
sbit ACC3 = ACC^3;
sbit ACC2 = ACC^2;
sbit ACC1 = ACC^1;
sbit ACC0 = ACC^0;

/*  B   */
sbit B7 = B^7;
sbit B6 = B^6;
sbit B5 = B^5;
sbit B4 = B^4;
sbit B3 = B^3;
sbit B2 = B^2;
sbit B1 = B^1;
sbit B0 = B^0;

/* P0   */
sbit AD7  = P0^7;
sbit AD6  = P0^6;
sbit AD5  = P0^5;
sbit AD4  = P0^4;
sbit AD3  = P0^3;
sbit AD2  = P0^2;
sbit AD1  = P0^1;
sbit AD0  = P0^0;

/*  P1  */
sbit CEX4 = P1^7;
sbit CEX3 = P1^6;
sbit CEX2 = P1^5;
sbit CEX1 = P1^4;
sbit CEX0 = P1^3;
sbit ECI  = P1^2;
sbit T2EX = P1^1;
sbit T2   = P1^0;

/*  P2  */
sbit AD15  = P2^7;
sbit AD14  = P2^6;
sbit AD13  = P2^5;
sbit AD12  = P2^4;
sbit AD11  = P2^3;
sbit AD10  = P2^2;
sbit AD9   = P2^1;
sbit AD8   = P2^0;

/*  P3  */
sbit RD   = P3^7;
sbit WR   = P3^6;
sbit T1   = P3^5;
sbit T0   = P3^4;
sbit INT1 = P3^3;
sbit INT0 = P3^2;
sbit TXD  = P3^1;
sbit RXD  = P3^0;
