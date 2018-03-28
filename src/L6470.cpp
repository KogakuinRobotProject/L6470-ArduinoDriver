#include"L6470.h"
#include"L6470_dfs.h"

#ifdef _L6470_DEBUG_
	#define _debug_print(x) Serial.print(x)
#elif _L6470_UNDEBUG_
	#define _debug_print(x) 
#else
	#error undefine mode
#endif

void L6470::cs_select(void)
{
	digitalWrite(SPICS, LOW);
}

void L6470::cs_unselect(void)
{
	digitalWrite(SPICS, HIGH);
}

void L6470::spi_begin(void)
{
	pSPI->beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE3));
}

void L6470::spi_stop(void)
{
	pSPI->endTransaction();
}

byte L6470::send_byte(byte _send_char)
{
	this->spi_begin();
	this->cs_select();
	byte ret = pSPI->transfer(_send_char);
	this->cs_unselect();
	this->spi_stop();
	return ret;
}

void L6470::write_command(byte command)
{
	send_byte(command); 
}

void L6470::write_command(byte command,byte data)
{
	send_byte(command);
	send_byte(data);
}

void L6470::write_command(byte command,word data)
{
	send_byte(command);
	send_byte((byte)((data >> 8) & 0xff));
	send_byte((byte)((data ) & 0xff));
}

//こいつのせいでtemplate化ではなく、オーバロードにしました。
//こいつ3byteしか送ってない。特殊化してもいいんだけどね。
//forで回すより、ビットシフトを選びました。エンディアンの違いをこちらのほうが吸収できそう。
//近年のマイコンでbigエンディアンのCPUいくつあるんだろ・・・ROMの消費を考えろって？しらない。
void L6470::write_command(byte command,unsigned long data)
{

	send_byte(command);
	send_byte((byte)((data >> 16) & 0xff));
	send_byte((byte)((data >> 8) & 0xff));
	send_byte((byte)((data) & 0xff));
}

void L6470::read_command(byte command,byte* data)
{
	send_byte(command);
	(*data) = send_byte(0x00);
}

void L6470::read_command(byte command,word* data)
{
	byte rev_temp[2];
	send_byte(command);
	rev_temp[0] = send_byte(0x00);
	rev_temp[1] = send_byte(0x00);
	(*data) = (rev_temp[0] << 8) | (rev_temp[1]);
}

//write_command(byte,unsigned long)同様
void L6470::read_command(byte command,unsigned long* data)
{
	byte rev_temp[3];
	send_byte(command);
	rev_temp[0] = send_byte(0x00);
	rev_temp[1] = send_byte(0x00);
	rev_temp[2] = send_byte(0x00);
	(*data) = (rev_temp[0] << 16) | (rev_temp[1] << 8) | (rev_temp[2]);
}

void L6470::Nop(void)
{
	write_command(L6470_COMMAND_NOP);
}

void L6470::Run(byte dir,unsigned long SPD)
{
	write_command(L6470_COMMAND_RUN(dir),SPD);
}

void L6470::StepClock(byte dir)
{
	write_command(L6470_COMMAND_STEPCLOCK(dir));
}

void L6470::Move(byte dir,unsigned long n_step)
{
	write_command(L6470_COMMAND_MOVE(dir),n_step);
}

void L6470::GoTo(unsigned long pos)
{
	write_command(L6470_COMMAND_GOTO,pos);
}

void L6470::GoTo_Dir(byte dir,unsigned long pos)
{
	write_command(L6470_COMMAND_GOTO_DIR(dir),pos);
}

void L6470::GoUntil(byte act,byte dir,unsigned long spd)
{
	write_command(L6470_COMMAND_GOUNTIL(act,dir),spd);
}

void L6470::ReleaseSW(byte act,byte dir)
{
	write_command(L6470_COMMAND_RELESESW(act,dir));
}

void L6470::GoHome(void)
{
	write_command(L6470_COMMAND_GOHOME);
}

void L6470::GoMark(void)
{
	write_command(L6470_COMMAND_GOMARK);
}

void L6470::ResetPos(void)
{
	write_command(L6470_COMMAND_RESETPOS);
}

void L6470::ResetDevice(void)
{
	write_command(L6470_COMMAND_RESETDEVICE);
}

void L6470::SoftStop(void)
{
	write_command(L6470_COMMAND_SOFTSTOP);
}

void L6470::HardStop(void)
{
	write_command(L6470_COMMAND_HARDSTOP);
}

void L6470::SoftHiZ(void)
{
	write_command(L6470_COMMAND_SOFTHIZ);
}

void L6470::HardHiZ(void)
{
	write_command(L6470_COMMAND_HARDHIZ);
}

void L6470::GetStatus(word *status)
{
	read_command(L6470_COMMAND_GETSTATUS,status);
}

L6470::L6470(byte _cs):
AbsPos(this),//ここの宣言がすごい無駄に見える
ElPos(this),
Mark(this),
Speed(this),
Acc(this),
Dec(this),
MaxSpeed(this),
MinSpeed(this),
KvalHold(this),
KvalRun(this),
KvalAcc(this),
KvalDec(this),
IntSpeed(this),
StSlp(this),
FnSlpAcc(this),
FnSlpDec(this),
KTherm(this),
AdcOut(this),
OcdTh(this),
StallTh(this),
FsSpd(this),
StepMode(this),
AlarmEn(this),
Config(this),
Status(this)
{
	pSPI=&SPI;
	SPICS = _cs;
	pinMode(SPICS,OUTPUT);
}

byte L6470::begin(void)
{
	pSPI->begin();
	
	this->ResetDevice();
	while(this->isBusy());
	
	return L6470_OK;
}

bool L6470::isBusy(void)
{
	word status;
	status = this->Status;
	return (status & L6470_STATUS_MASK_BUSY) != L6470_STATUS_MASK_BUSY; //Active Lowなので、maskと一致したらNonActive
}

bool L6470::isError(void)
{
	word status;
	status = this->Status;
	return (status & L6470_STATUS_ERROR_MASK) != L6470_STATUS_ERROR_MASK; //Active Lowなので、maskと一致したらNonActive
	
}

bool L6470::isThermalShutdown(void)
{
	word status;
	status = this->Status;
	return (status & L6470_STATUS_MASK_TH_SD) != L6470_STATUS_MASK_TH_SD; //Active Lowなので、maskと一致したらNonActive
}

bool L6470::isThermalWarning(void)
{
	word status;
	status = this->Status;
	return (status & L6470_STATUS_MASK_TH_WRN) != L6470_STATUS_MASK_TH_WRN; //Active Lowなので、maskと一致したらNonActive
}

L6470& L6470::SetConfig(L6470_StepThick::Config cfg)
{
	this->Acc = cfg.acc;
	this->Dec = cfg.dec;
	this->MaxSpeed = cfg.max_speed;
	this->MinSpeed = cfg.min_speed;
}

//ステップ入力
L6470& L6470::operator+=(signed long step)
{
	while(isBusy())delay(10);
	byte dir = (step >> 31) & 0x01;
	unsigned long u_step = step & 0x0003fff;
	this->Move(dir,u_step);
}

L6470& L6470::operator-=(signed long step)
{
	while(isBusy())delay(10);
	byte dir = (~step >> 31) & 0x01;
	unsigned long u_step = step & 0x0003fff;
	this->Move(dir,u_step);
}

namespace L6470_StepThick{
	Config::Config(word _acc ,word _dec ,word _max_speed ,word _min_speed):
	acc(_acc),
	dec(_dec),
	max_speed(_max_speed),
	min_speed(_min_speed)
	{
	}
}

