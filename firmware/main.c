#include <xc.h>

#include "config.h"

void main(void)
{
  TRISAbits.TRISA5 = 0;
  PORTAbits.RA5 = 1;
}
