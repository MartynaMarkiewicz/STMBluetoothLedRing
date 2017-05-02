#include "ws2812.h"

void clear_s(int s)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].green=0;
		diode[i].red=0;
		diode[i].blue=0;
		delay_ms(s);
	}
}

void clear()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].green=0;
		diode[i].red=0;
		diode[i].blue=0;
		delay_ms(550);
	}
}

void clear_all()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].green=0;
		diode[i].red=0;
		diode[i].blue=0;
	}
	delay_ms(500);
}

void clear_app(int k, int j)
{
	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].red=0;
		diode[i].blue=0;
		diode[i].green=0;
	}
}
