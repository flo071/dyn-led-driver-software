/*
 * Controller : AT32UC3C2512C
 * Datasheet  : http://ww1.microchip.com/downloads/en/DeviceDoc/doc32117.pdf
 * Author     : flo071
 *
 */ 

#include <avr32/io.h>

#define LMM_INIT_BYTE     0x99
#define LMM_DEVID_BYTE    0x61
#define LMM_LED_CHANNEL01 0x42
#define LMM_LED_CHANNEL02 0x46
#define LMM_LED_CHANNEL03 0x4a
#define LMM_LED_CHANNEL04 0x4e
#define LMM_LED_CHANNEL05 0x52
#define LMM_LED_CHANNEL06 0x56
#define LMM_LED_CHANNEL07 0x5a
#define LMM_LED_CHANNEL08 0x5e
#define LMM_LED_CHANNEL09 0x62
#define LMM_LED_CHANNEL10 0x66
#define LMM_LED_CHANNEL11 0x6a
#define LMM_LED_CHANNEL12 0x6e
#define LMM_CRCL_BYTE	  0x07
#define LMM_CRCH_BYTE     0x42

// Funktionsprototypen - Start
void init(void);
void spi_init(void); 
void can_init(void);
void dac_init(void);
void adc_init(void);

void can_receive_ch0(void);
void can_send_ch0(int led, char data[]);
void build_lmm_message(void);
void can_receive_ch1(void);
void can_send_ch1(void);
void spi_send(void);
void dac_set_current(void);
void adc_measure_current(void);
// Funktionsprototypen - Ende

void init(void) {
	spi_init();
	can_init();
	dac_init();
	adc_init();
}

// SPI0 Schnittstelle initialisieren 
void spi_init(void) {
	// GPIO Ports initialisieren
	/*
	 * PIN PORT INTERFACE USAGE    MODE
	 *  47 PD00 SPI0MOSI  Dig.Pot. A
 	 *  48 PD01 SPI0MISO  Dig.Pot. A
	 *  49 PD02 SPI0SCK   Dig.Pot. A
	 *  50 PD03 SPI0CS    Dig.Pot. A
	 */
	
	// SPI 0
	// for peripheral functions, the GPER must be 0
	AVR32_GPIO.port[3].gper = 0<<00;
	AVR32_GPIO.port[3].gper = 0<<01;
	AVR32_GPIO.port[3].gper = 0<<02;
	AVR32_GPIO.port[3].gper = 0<<03;
	AVR32_GPIO.port[3].pmr0 = 0; AVR32_GPIO.port[3].pmr1 = 0; AVR32_GPIO.port[3].pmr2 = 0; // Port D Pin 0 CANRX MODE A
}

// CANIF0/1 Schnittstelle initialisieren
void can_init(void) {
	/*
	 * PIN PORT INTERFACE USAGE MODE
	 *  39 PC15 CANIFRX1  LMM   D
 	 *  40 PC16 CANIFTX1  LMM   D
	 *  45 PC21 CANIFRX0  UCD   B
	 *  46 PC22 CANIFTX0  UCD   B
	 */
	
	/*
	 * One CAN Port will need to get an external interrupt enabled later
	 * to ensure that the UCD Commands will get received at every 
	 * sent message.
	 */
	
	// CAN 1
	// for peripheral functions, the GPER must be 0
	AVR32_GPIO.port[2].gper = 0<<15;
	AVR32_GPIO.port[2].gper = 0<<16;
	AVR32_GPIO.port[2].pmr0 = 1<<15; AVR32_GPIO.port[2].pmr1 = 1<<15; AVR32_GPIO.port[2].pmr2 = 0; // Port C Pin 15 CANRX MODE D
	AVR32_GPIO.port[2].pmr0 = 1<<16; AVR32_GPIO.port[2].pmr1 = 1<<16; AVR32_GPIO.port[2].pmr2 = 0; // Port C Pin 16 CANTX MODE D
	// CANIF channel 1
	AVR32_CANIF.channel[1].CANCFG.ovrm  = 1; // Overrun Mode
	AVR32_CANIF.channel[1].CANCFG.cmode = 2; // Loopback Mode
	AVR32_CANIF.channel[1].CANCFG.sm    = 1; // Sampling Method
	AVR32_CANIF.channel[1].CANCFG.sjw   = 1; // Sync Jump width
	AVR32_CANIF.channel[1].CANCFG.prs   = 1; // Propagation segment
	// Init CAN channel 1
	AVR32_CANIF.channel[1].CANCTRL.wken = 1; // CAN Interrupt wake enabled
	AVR32_CANIF.channel[1].CANCTRL.ovrq = 0; // Overloads will not be handled
	AVR32_CANIF.channel[1].CANCTRL.cen  = 1; // Enable channel for requests
	AVR32_CANIF.channel[1].CANCTRL.init = 1; // Init CAN channel 1
	
	// CAN 0
	// for peripheral functions, the GPER must be 0
	AVR32_GPIO.port[2].gper = 0<<21;
	AVR32_GPIO.port[2].gper = 0<<22;
	AVR32_GPIO.port[2].pmr0 = 1<<21; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0; // Port C Pin 21 CANRX MODE B
	AVR32_GPIO.port[2].pmr0 = 1<<22; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0; // Port C Pin 22 CANTX MODE B
	// CANIF channel 0
	AVR32_CANIF.channel[0].CANCFG.ovrm  = 1; // Overrun Mode
	AVR32_CANIF.channel[0].CANCFG.cmode = 2; // Loopback Mode
	AVR32_CANIF.channel[0].CANCFG.sm    = 1; // Sampling Method
	AVR32_CANIF.channel[0].CANCFG.sjw   = 1; // Sync Jump width
	AVR32_CANIF.channel[0].CANCFG.prs   = 1; // Propagation segment
	// Init CAN channel 0
	AVR32_CANIF.channel[0].CANCTRL.wken = 1; // CAN Interrupt wake enabled
	AVR32_CANIF.channel[0].CANCTRL.ovrq = 0; // Overloads will not be handled
	AVR32_CANIF.channel[0].CANCTRL.cen  = 1; // Enable channel for requests
	AVR32_CANIF.channel[0].CANCTRL.init = 1; // Init CAN channel 0
}

void can_receive_ch0(void) {
	/*
	 *  Reference for Checks:
	 *		Datasheet Page 781 CAN Status Register
	 */
	if (AVR32_CANIF.channel[0].CANSR.ces == 1) { // check if channel is enabled
		// For debugging: a unused GPIO PIN can be set to 1 when this case is true
		while(AVR32_CANIF.channel[0].CANSR.rs == 1){ // while receiving
			// TODO: Add code to handle LMM ACK message
		}
	}
}

void can_send_ch0(int led, char data[]) {
	/*
	 *  Communication with TI LMM:
	 *		Frame initialisation bit
	 *			0x99	
	 *		Device ID
	 *			0x61
	 *      LED Channel to set
	 *			0x4a
	 *		Data
	 *			0x00
	 *			0x00
	 *		CRCL
	 *			0x07
	 *		CRCH
	 *			0x42
	 *		
	 *		7 - byte communication length
	 *
	 *		LMM sends ACK if it accepts the message
	 *			will be hanled here: can_receive_ch0()
	 *
	 *  Reference for Checks:
	 *		Datasheet Page 781 CAN Status Register
	 */
	if (AVR32_CANIF.channel[0].CANSR.ces == 1) { // check if channel is enabled
		// For debugging: a unused GPIO PIN can be set to 1 when this case is true
		while(AVR32_CANIF.channel[0].CANSR.ts == 1){ // while sending
			// TODO: Add code to transmit message
			
		}
	}
}

void build_lmm_message(void) {
	
}

void can_receive_ch1(void) {
	/*
	 *  Reference for Checks:
	 *		Datasheet Page 781 CAN Status Register
	 */
	if (AVR32_CANIF.channel[1].CANSR.ces == 1) { // check if channel is enabled
		// For debugging: a unused GPIO PIN can be set to 1 when this case is true
		while(AVR32_CANIF.channel[1].CANSR.rs == 1){ // while receiving
			// TODO: Add code to handle received message
		}
	}
}

void can_send_ch1(void) {
	/*
	 *  Reference for Checks:
	 *		Datasheet Page 781 CAN Status Register
	 */
	if (AVR32_CANIF.channel[1].CANSR.ces == 1) { // check if channel is enabled
		// For debugging: a unused GPIO PIN can be set to 1 when this case is true
		while(AVR32_CANIF.channel[1].CANSR.ts == 1){ // while sending
			// TODO: Add code to handle received transmit message
		}
	}
}

// DAC Schnittstelle initialisieren
void dac_init(void) {
	// GPIO Ports initialisieren
	
	// Interne Register initialisieren
}

// ADC Schnittstelle initialisieren
void adc_init(void) {
	// GPIO Ports initialisieren
	
	// Interne Register initialisieren
}

int main(void) {
    init();
    while (1) {
    }
}

