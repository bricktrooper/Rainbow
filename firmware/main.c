#include <xc.h>

#include "system.h"

#include <stdio.h>

void main(void)
{
	system_initialize();

	while (1)
	{
		printf("Hello\r\n");
	}
}
