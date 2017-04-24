#include "ws2812.h"

//kolory g-l
int i=0;
uint8_t brightness=0;

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

void zielony()
{
	for(i=0;i<8;i++)
	{
		if(brightness)
		{
			diode[i].red=(24 * brightness) >> 8;
			diode[i].green=(100 * brightness) >> 8;
			diode[i].blue=(0 * brightness) >> 8;
	   }
		else
		{
			diode[i].red=24;
			diode[i].green=100;
			diode[i].blue=0;
		}
	}
}

void t1()
{
	for(i=0;i<8;i++)
	{
		diode[i].red=19;
		diode[i].green=0;
		diode[i].blue=207;
	}
}

void p1()
{

}

void nz()
{
	for(i=0;i<8;i++)
	{
		diode[i].red=0;
		diode[i].green=243;
		diode[i].blue=75;
	}
}

void z1()
{
	for(i=0;i<8;i++)
	{
		diode[i].red=195;
		diode[i].green=111;
		diode[i].blue=0;
	}
}

void roz1()
{
	for(i=0;i<8;i++)
	{
		diode[i].red=255;
		diode[i].green=0;
		diode[i].blue=51;
	}
}

void roz()
{
	for(i=0;i<8;i++)
	{
		diode[i].red=255;
		diode[i].green=0;
		diode[i].blue=255;
	}
}

void red (int r)
{
	diode[0].red=r;
	diode[1].red=r;
	diode[2].red=r;
	diode[3].red=r;
	diode[4].red=r;
	diode[5].red=r;
	diode[6].red=r;
	diode[7].red=r;

}

void green (int g)
{
	diode[0].green=g;
	diode[1].green=g;
	diode[2].green=g;
	diode[3].green=g;
	diode[4].green=g;
	diode[5].green=g;
	diode[6].green=g;
	diode[7].green=g;
}

void blue (int b)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].blue=b;
	}
}
