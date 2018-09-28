// borrowed from https://github.com/AdmiralCurtiss/nds-savegame-manager/
#ifndef __SLOT2_H__
#define __SLOT2_H__

enum cartTypeGBA {
	CART_GBA_NONE = 0,
	CART_GBA_GAME,
	CART_GBA_EMULATOR,
	CART_GBA_3IN1_256_V1,
	CART_GBA_3IN1_256_V2,
	CART_GBA_3IN1_512_V3,
	CART_GBA_FLASH
};

enum saveTypeGBA {
	SAVE_GBA_NONE = 0,
	SAVE_GBA_EEPROM_05, // 512 bytes
	SAVE_GBA_EEPROM_8, // 8k
	SAVE_GBA_SRAM_32, // 32k
	SAVE_GBA_FLASH_64, // 64k
	SAVE_GBA_FLASH_128 // 128k
};

struct dataSlot2 {
	cartTypeGBA type;
	saveTypeGBA save;
	uint32 ez_ID;
	union {
		char cid[5];
		uint32 iid;
	};
	char name[13];
};


cartTypeGBA GetSlot2Type(uint32 id);
saveTypeGBA GetSlot2SaveType(cartTypeGBA type);

// --------------------
bool gbaIsGame();
uint8 gbaGetSaveType();
uint32 gbaGetSaveSize(uint8 type = 255);
uint32 gbaGetSaveSizeLog2(uint8 type = 255);

bool gbaReadSave(u8 *dst, u32 src, u32 len, u8 type);
bool gbaWriteSave(u32 dst, u8 *src, u32 len, u8 type);
bool gbaFormatSave(u8 type);


#endif // __SLOT2_H__