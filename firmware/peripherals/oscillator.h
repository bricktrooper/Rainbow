#ifndef OSCILLATOR_H
#define OSCILLATOR_H

typedef enum HFFRQ HFFRQ;

enum HFFRQ
{
	HFFRQ_RESERVED = 0b111,
	HFFRQ_32MHZ    = 0b110,
	HFFRQ_16MHZ    = 0b101,
	HFFRQ_12MHZ    = 0b100,
	HFFRQ_8MHZ     = 0b011,
	HFFRQ_4MHZ     = 0b010,
	HFFRQ_2MHZ     = 0b001,
	HFFRQ_1MHZ     = 0b000
};

void oscillator_initialize(void);
void oscillator_frequency(HFFRQ frequency);

#endif /* OSCILLATOR_H */
