#ifndef _L6470_H_
#define _L6470_H_

#include<Arduino.h>
#include<SPI.h>
#include<inttypes.h>

#include"L6470_dfs.h"

class L6470{

private:
	SPIClass *pSPI;
	byte SPICS;
	
//	レジスタ操作クラス
	template<L6470_REG addr,typename data_len>
	class Registers{
		L6470* device;
	public:
		Registers(L6470* _device):device(_device){}
		virtual data_len Get(void){
			data_len ret;
			device->GetParam(addr,(byte*)&ret,sizeof(data_len));
			return ret;
		}
		virtual void Set(data_len data){
			device->SetParam(addr,(byte*)&data,sizeof(data_len));
		}
	};
	
	template<L6470_REG addr,typename data_len>
	friend class Registers;

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

public:
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
	
public:
	Registers<ABS_POS,unsigned long>	AbsPos;
	Registers<EL_POS,word>				ElPos;
	Registers<MARK,unsigned long>		Mark;
	Registers<SPEED,unsigned long>		Speed;
	Registers<ACC,word>					Acc;
	Registers<_DEC,word>				Dec;
	Registers<MAX_SPEED,word>			MaxSpeed;
	Registers<MIN_SPEED,word>			MinSpeed;
	Registers<KVAL_HOLD,byte>			KvalHold;
	Registers<KVAL_RUN,byte>			KvalRun;
	Registers<KVAL_ACC,byte>			KvalAcc;
	Registers<KVAL_DEC,byte>			KvalDec;
	Registers<INT_SPEED,word>			IntSpeed;
	Registers<ST_SLP,byte>				StSlp;
	Registers<FN_SLP_ACC,byte>			FnSlpAcc;
	Registers<FN_SLP_DEC,byte>			FnSlpDec;
	Registers<K_THERM,byte>				KTherm;
	Registers<ADC_OUT,byte>				AdcOut;
	Registers<OCD_TH,byte>				OcdTh;
	Registers<STALL_TH,byte>			StallTh;
	Registers<FS_SPD,word>				FsSpd;
	Registers<STEP_MODE,byte>			StepMode;
	Registers<ALARM_EN,byte>			AlarmEn;
	Registers<CONFIG,word>				Config;
	Registers<STATUS,word>				Status;

public:
	L6470(byte _cs);
	byte begin(void);
};

#endif