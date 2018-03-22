#ifndef _L6470_H_
#define _L6470_H_

#include<Arduino.h>
#include<SPI.h>
#include<inttypes.h>

class L6470{

private:
	SPIClass *pSPI;
	byte SPICS;

private:
	void cs_select(void);
	void cs_unselect(void);

	void spi_begin(void);
	void spi_stop(void);

	byte send_byte(byte);
	void send_bytes(byte*,byte*,byte);

private:
	void NOP(void);
	void SetParam(byte,byte*,byte);
	void GetParam(byte,byte*,byte);
	void Run(byte,unsigned long);
	void StepClock(byte);
	void Move(byte,unsigned long);
	void GoTo(unsigned long);
	void GoTo_Dir(byte,unsigned long);
	void GoUntil(byte,byte,unsigned long);
	void ReleaseSW(byte,byte);
	void GoHome(void);
	void GoMark(void);
	void ResetPos(void);
	void ResetDevice(void);
	void SoftStop(void);
	void HardStop(void);
	void SoftHiZ(void);
	void HardHiZ(void);
	void GetStatus(unsigned long);
	
	
public:
	L6470(byte _cs);
};

#endif