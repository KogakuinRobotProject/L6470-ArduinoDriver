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

	void write_command(byte);
	void write_command(byte,byte*,byte);
	void write_command(byte,unsigned long);
	void read_command(byte,byte*,byte);

private:
//	コマンドメソッド
	void			NOP(void);
	void			SetParam(byte,byte*,byte);
	void			GetParam(byte,byte*,byte);
	void			Run(byte,unsigned long);
	void			StepClock(byte);
	void			Move(byte,unsigned long);
	void			GoTo(unsigned long);
	void			GoTo_Dir(byte,unsigned long);
	void			GoUntil(byte,byte,unsigned long);
	void			ReleaseSW(byte,byte);
	void			GoHome(void);
	void			GoMark(void);
	void			ResetPos(void);
	void			ResetDevice(void);
	void			SoftStop(void);
	void			HardStop(void);
	void			SoftHiZ(void);
	void			HardHiZ(void);
	void			GetStatus(unsigned long);

//	レジスタ操作メソッド
	void			SetAbsPos(unsigned long);
	unsigned long	GetAbsPos(void);
	void			SetElPos(word);
	word			GetElPos(void);
	void			SetMark(unsigned long);
	unsigned long	GetMark(void);
	//void			SetSpeed(unsigned long);//Read Only
	unsigned long	GetSpeed(void);
	void			SetAcc(word);
	word			GetAcc(void);
	void			SetDec(word);
	word			GetDec(word);
	void			SetMaxSpeed(word);
	word			GetMaxSpeed(void);
	void			SetMinSpeed(word);
	word			GetMinSpeed(void);
	void			SetFsSpd(word);
	word			GetFsSpd(void);
	void			SetKVALHold(byte);
	byte			GetKVALHold(void);
	void			SetKVALRun(byte);
	byte			GetKVALRun(void);
	void			SetKVALAcc(byte);
	byte			GetKVALAcc(void);
	void			SetKVALDec(byte);
	byte			GetKVALDec(void);
	void			SetIntSpeed(word);
	word			GetIntSpeed(void);
	void			SetStSlp(byte);
	byte			GetStSlp(void);
	void			SetFnSlpAcc(byte);
	byte			GetFnSlpAcc(void);
	void			SetFnSlpDec(byte);
	byte			GetFnSlpDec(void);
	
public:
	L6470(byte _cs);
};

#endif