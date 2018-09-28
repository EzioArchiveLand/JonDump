#ifndef NDS_DSCARD_V2_INCLUDE
#define NDS_DSCARD_V2_INCLUDE

#include "nds.h"

	#ifdef __cplusplus
	extern "C" {
	#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef BOOL
typedef bool BOOL ;
#endif
// export interface




//---------------------------------------------------
//DS 卡 基本操作
		//Arm9 方面基本操作容许ARM7访问slot1
		void		Enable_Arm7DS(void);

		//Arm9 方面基本操作容许ARM9访问slot1
		void		Enable_Arm9DS(void);

		
		//下面是访问震动卡的函数
#define FlashBase		0x08000000
#define	_Ez5PsRAM 	0x08000000
		void		OpenNorWrite();
		void		CloseNorWrite();
		void      SetRompage(u16 page);
		void 		SetRampage(u16 page);
		void  	OpenRamWrite();
		void 		CloseRamWrite();
		void      SetSerialMode();
		uint32   ReadNorFlashID();
		void 		chip_reset();
		void 		Block_Erase(u32 blockAdd);
		void 		ReadNorFlash(u8* pBuf,u32 address,u16 len);
		void 		WriteNorFlash(u32 address,u8 *buffer,u32 size);
		void 		WriteSram(uint32 address, u8* data , uint32 size );
		void 		ReadSram(uint32 address, u8* data , uint32 size );
		void 		SetShake(u16 data);
		void WritePSram(u8* address, u8* data , uint32 length );
		void ReadPSram(u8* address, u8* data , uint32 length );
	#ifdef __cplusplus
	}
	#endif
#endif