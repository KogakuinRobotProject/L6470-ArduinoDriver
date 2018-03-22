#include"L6470.h"

#define	L6470_COMMAND_NOP				(0x00)
#define L6470_COMMAND_SETPARAM(x)		(0x00 | x)
#define L6470_COMMAND_GETPARAM(x)		(0x20 | x)
#define L6470_COMMAND_RUN(dir)			(0x50 | dir)
#define L6470_COMMAND_STEPCLOCK(dir)	(0x58 | dir)
#define L6470_COMMAND_MOVE(dir)			(0x40 | dir)
#define L6470_COMMAND_GOTO				(0x60)
#define L6470_COMMAND_GOTO_DIR(dir)		(0x68 | dir)
#define L6470_COMMAND_GOUNTIL(act,dir)	(0x82 | (act << 3) | dir)
#define L6470_COMMAND_RELESESW(act,dir)	(0x92 | (act << 3) | dir)
#define L6470_COMMAND_GOHOME			(0x70)
#define L6470_COMMAND_GOMARK			(0x78)
#define L6470_COMMAND_RESETPOS			(0xd8)
#define L6470_COMMAND_RESETDEVICE		(0xc0)
#define L6470_COMMAND_SOFTSTOP			(0xb0)
#define L6470_COMMAND_HARDSTOP			(0xb8)
#define L6470_COMMAND_SOFTHIZ			(0xa0)
#define L6470_COMMAND_HARDHIZ			(0xa8)
#define L6470_COMMAND_GETSTATES			(0xd0)

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
	pSPI->beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
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

void L6470::send_bytes(byte* send,byte *recive,byte len)
{
	if(recive == NULL){
		for(int i =0;i < len;i++){
			send_byte(send[i]);
		}
	}
	else if{
		for(int i =0;i < len;i++){
			recive[i] = send_byte(send[i]);
		}
	}
}

void L6470::NOP(void)
{
	byte command[] = {L6470_COMMAND_NOP};
	send_bytes(command,NULL,1);
}

void L6470::SetParam(byte addr,byte* data,byte len)
{
}

void L6470::GetOaram(byte addr,byte* data,byte len)
{
}

void L6470::Run(byte dir,unsigned long SPD)
{
	byte command[] = {L6470_COMMAND_RUN(dir),0,0,0};
	command[1] = (SPD >> 16) & 0x0f;
	command[2] = (SPD >> 8) & 0xff;
	command[3] = (SPD & 0xff);

	send_bytes(command,NULL,4);
}

void L6470::StepClock(byte dir)
{
	byte command[] = {L6470_COMMAND_STEPCLOCK(dir)};
	send_bytes(command,NULL,1);
}

void L6470::Move(byte dir,unsigned long n_step)
{
	byte command[] = {L6470_COMMAND_MOVE(dir),0,0,0}
	command[1] = (n_step >> 16) & 0x0f;
	command[2] = (n_step >> 8) & 0xff;
	command[3] = (n_step & 0xff);
	
	send_bytes(command,NULL,4);
}

void L6470::GoTo(unsigned long pos)
{
	byte command[] = {L6470_COMMAND_GOTO,0,0,0}
	command[1] = (pos >> 16) & 0x0f;
	command[2] = (pos >> 8) & 0xff;
	command[3] = (pos & 0xff);
	
	send_bytes(command,NULL,4);
}

void L6470::GoTo_Dir(byte dir,unsigned long pos)
{
	byte command[] = {L6470_COMMAND_GOTO_DIR(dir),0,0,0}
	command[1] = (pos >> 16) & 0x0f;
	command[2] = (pos >> 8) & 0xff;
	command[3] = (pos & 0xff);
	
	send_bytes(command,NULL,4);
}

void L6470::GoUntil(byte act,byte dir,unsigned long spd)
{
	byte command[] = {L6470_COMMAND_GOUNTIL(act,dir),0,0,0}
	command[1] = (spd >> 16) & 0x0f;
	command[2] = (spd >> 8) & 0xff;
	command[3] = (spd & 0xff);
	
	send_bytes(command,NULL,4);
}

void L6470::ReleaseSW(byte act,byte dir)
{
	byte command[] = {L6470_COMMAND_GOUNTIL(act,dir)}
	send_bytes(command,NULL,1);
}

void L6470::GoHome(void)
{
	byte command[] = {L6470_COMMAND_GOHOME}
	send_bytes(command,NULL,1);
}

void L6470::GoMark(void)
{
	byte command[] = {L6470_COMMAND_GOMARK}
	send_bytes(command,NULL,1);
}

void L6470::ResetPos(void)
{
	byte command[] = {L6470_COMMAND_RESETPOS}
	send_bytes(command,NULL,1);
}

void L6470::ResetDevice(void)
{
	byte command[] = {L6470_COMMAND_RESETDEVICE}
	send_bytes(command,NULL,1);
}

void L6470::SoftStop(void)
{
	byte command[] = {L6470_COMMAND_SOFTSTOP}
	send_bytes(command,NULL,1);
}

void L6470::HardStop(void)
{
	byte command[] = {L6470_COMMAND_HARDSTOP}
	send_bytes(command,NULL,1);
}

void L6470::SoftHiZ(void)
{
	byte command[] = {L6470_COMMAND_SOFTHIZ}
	send_bytes(command,NULL,1);
}

void L6470::HardHiZ(void)
{
	byte command[] = {L6470_COMMAND_HARDHIZ}
	send_bytes(command,NULL,1);
}

void L6470::GetStatus(unsigned long status)
{
	
}

L6470::L6470(byte _cs)
{
	pSPI=&SPI;
	SPICS = _cs;
}