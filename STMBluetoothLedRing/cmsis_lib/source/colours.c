#include "ws2812.h"

//kolory g-l

void rgb(int r,int g, int b)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].red=r;
		diode[i].green=g;
		diode[i].blue=b;
	}
}

void rgb2(int r,int g, int b)
{
	int i=8;
	for(i=8;i<16;i++)
	{
		diode[i].red=r;
		diode[i].green=g;
		diode[i].blue=b;
	}
}
