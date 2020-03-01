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
	
	// Interne Register initialisieren 
}

// CANIF0/1 Schnittstelle initialisieren
void can_init(void) {
	// GPIO Ports initialisieren
	
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

int main(void)
{
    init();
    while (1) 
    {
    }
}

