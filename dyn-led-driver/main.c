/*
 * Controller : AT32UC3C2512C
 * Author     : flo071
 *
 */ 

#include <avr32/io.h>

// Funktionsprototypen - Start
void init(void);
void spi_init(void); 
void can_init(void);
void dac_init(void);
void adc_init(void);

void can_receive(void);
void can_send(void);
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
	
	// CAN 1
	// for peripheral functions, the GPER must be 0
	AVR32_GPIO.port[2].gper = 0<<15;
	AVR32_GPIO.port[2].gper = 0<<16;
	AVR32_GPIO.port[2].pmr0 = 1<<15; AVR32_GPIO.port[2].pmr1 = 1<<15; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 15 CANRX MODE D
	AVR32_GPIO.port[2].pmr0 = 1<<16; AVR32_GPIO.port[2].pmr1 = 1<<16; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 16 CANTX MODE D
	// CANIF channel 1
	AVR32_CANIF.channel[1].CANCFG.ovrm  = 1; // Overrun Mode
	AVR32_CANIF.channel[1].CANCFG.cmode = 2; // Loopback Mode
	AVR32_CANIF.channel[1].CANCFG.sm    = 1; // Sampling Method
	AVR32_CANIF.channel[1].CANCFG.sjw   = 1; // Sync Jump width
	AVR32_CANIF.channel[1].CANCFG.prs   = 1; // Propagation segment
	
	// CAN 0
	// for peripheral functions, the GPER must be 0
	AVR32_GPIO.port[2].gper = 0<<21;
	AVR32_GPIO.port[2].gper = 0<<22;
	AVR32_GPIO.port[2].pmr0 = 1<<21; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 21 CANRX MODE B
	AVR32_GPIO.port[2].pmr0 = 1<<22; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 22 CANTX MODE B
	
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

