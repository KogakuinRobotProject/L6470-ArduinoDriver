#include"L6470.h"
#include"L6470_dfs.h"

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

void L6470::write_command(byte command,byte* send,byte len)
{
	send_byte(command);
	for(int i = 0;i < len;i++){
		send_byte(send[i]);
	}
}

void L6470::write_command(byte command,unsigned long data)
{
	send_byte(command);
	send_byte((byte)((data >> 16) & 0xff));
	send_byte((byte)((data >>  8) & 0xff));
	send_byte((byte)((data) & 0xff));
}

void L6470::read_command(byte command,byte* data,byte len)
{
	send_byte(command);
	for(int i =0;i<len;i++){
		data[i] = send_byte(0x00);
	}
}

void L6470::NOP(void)
{
	write_command(L6470_COMMAND_NOP);
}

void L6470::SetParam(byte addr,byte* data,byte len)
{
	write_command(L6470_COMMAND_SETPARAM(addr),data,len);
}

void L6470::GetParam(byte addr,byte* data,byte len)
{
	read_command(L6470_COMMAND_GETPARAM(addr),data,len);
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

void L6470::GetStatus(unsigned long status)
{
	
}

L6470::L6470(byte _cs):
AbsPos(this),//‚±‚±‚ÌéŒ¾‚ª‚·‚²‚¢–³‘Ê‚ÉŒ©‚¦‚é
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
}

byte L6470::begin(void)
{
	pSPI->begin();
	return L6470_OK;
}