#ifndef _L6470_dfs_H_
#define _L6470_dfs_H_

#define	L6470_COMMAND_NOP				(byte)(0x00)
#define L6470_COMMAND_SETPARAM(x)		(byte)(0x00 | x)
#define L6470_COMMAND_GETPARAM(x)		(byte)(0x20 | x)
#define L6470_COMMAND_RUN(dir)			(byte)(0x50 | dir)
#define L6470_COMMAND_STEPCLOCK(dir)	(byte)(0x58 | dir)
#define L6470_COMMAND_MOVE(dir)			(byte)(0x40 | dir)
#define L6470_COMMAND_GOTO				(byte)(0x60)
#define L6470_COMMAND_GOTO_DIR(dir)		(byte)(0x68 | dir)
#define L6470_COMMAND_GOUNTIL(act,dir)	(byte)(0x82 | (act << 3) | dir)
#define L6470_COMMAND_RELESESW(act,dir)	(byte)(0x92 | (act << 3) | dir)
#define L6470_COMMAND_GOHOME			(byte)(0x70)
#define L6470_COMMAND_GOMARK			(byte)(0x78)
#define L6470_COMMAND_RESETPOS			(byte)(0xd8)
#define L6470_COMMAND_RESETDEVICE		(byte)(0xc0)
#define L6470_COMMAND_SOFTSTOP			(byte)(0xb0)
#define L6470_COMMAND_HARDSTOP			(byte)(0xb8)
#define L6470_COMMAND_SOFTHIZ			(byte)(0xa0)
#define L6470_COMMAND_HARDHIZ			(byte)(0xa8)
#define L6470_COMMAND_GETSTATUS			(byte)(0xd0)

#define L6470_DEFAULT_ACC				0x08A
#define L6470_DEFAULT_DEC				0x08A
#define L6470_DEFAULT_MAX_SPEED			0x041
#define L6470_DEFAULT_MIN_SPEED			0x000

typedef enum{
	ABS_POS = 0x01,
	EL_POS,
	MARK,
	SPEED,
	ACC,
	_DEC,			//–¼‘O‹£‡‰ñ”ð‚Ì‚½‚ß
	MAX_SPEED,
	MIN_SPEED,
	KVAL_HOLD,
	KVAL_RUN,
	KVAL_ACC,
	KVAL_DEC,
	INT_SPEED,
	ST_SLP,
	FN_SLP_ACC,
	FN_SLP_DEC,
	K_THERM,
	ADC_OUT,
	OCD_TH,
	STALL_TH,
	FS_SPD,
	STEP_MODE,
	ALARM_EN,
	CONFIG,
	STATUS,
}L6470_REG;

typedef enum{
	L6470_OK,
};

#endif