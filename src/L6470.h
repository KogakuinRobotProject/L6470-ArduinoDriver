#ifndef _L6470_H_
#define _L6470_H_

#include<Arduino.h>
#include<SPI.h>
#include<inttypes.h>

class L6470{

private:
	SPIClass *pSPI;
	byte SPICS;

public:
	L6470(byte _cs);
};

#endif