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
	 * PIN PORT INTERFACE USAGE
	 *  47 PD00 SPI0MOSI  Dig.Pot.
 	 *  48 PD01 SPI0MISO  Dig.Pot.
	 */
	
	 
	// Interne Register initialisieren 
}

// CANIF0/1 Schnittstelle initialisieren
void can_init(void) {
	// GPIO Ports initialisieren
	/*
	 * PIN PORT INTERFACE USAGE MODE
	 *  39 PC15 CANIFRX1  LMM   D
 	 *  40 PC16 CANIFTX1  LMM   D
	 *  45 PC21 CANIFRX0  UCD   B
	 *  46 PC22 CANIFTX0  UCD   B
	 */
	
	// GPIO Pins aktiviren
	AVR32_GPIO.port[2].pmr0 = 1<<15; AVR32_GPIO.port[2].pmr1 = 1<<15; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 15 CANRX MODE D
	AVR32_GPIO.port[2].pmr0 = 1<<16; AVR32_GPIO.port[2].pmr1 = 1<<16; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 16 CANTX MODE D
	AVR32_GPIO.port[2].pmr0 = 1<<21; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 21 CANRX MODE B
	AVR32_GPIO.port[2].pmr0 = 1<<22; AVR32_GPIO.port[2].pmr1 =     0; AVR32_GPIO.port[2].pmr2 = 0;// Port C Pin 22 CANTX MODE B
	
	// Interne Register initialisieren
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

