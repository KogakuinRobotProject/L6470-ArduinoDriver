#include"L6470.h"

L6470::L6470(byte _cs)
{
	pSPI=&SPI;
	SPICS = _cs;
}