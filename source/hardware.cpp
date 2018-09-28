// adapted from github page listed in gba.harderr
#include <nds.h>
#include <fat.h>
#include <nds/arm9/dldi.h>

#include <nds/interrupts.h>
#include <nds/arm9/console.h>
#include <sys/dir.h>
#include <sys/unistd.h>
#include <dswifi9.h>
#include <nds/card.h>

#include <stdio.h>
#include <algorithm>

#include "dsCard.h"
#include "gba.h"
#include "globals.h"

#include "hardware.h"
// reinclude this
#include "auxspi.h"

using namespace std;

static u32 pitch = 0x40000;

// Work in progress
// GBA rom Dumper
void DumpGBARom(){
	// do something here
}

// some form of writer thingy
void writeGBAtoDS(u8* whatthefuck) {
	slot_1_type = auxspi_has_extra();
	uint8 size = auxspi_save_size_log_2(slot_1_type);
	int size_blocks = 1 << max(0, (int8(size) - 18)); // ... in units of 0x40000 bytes - that's 256 kB
	uint8 type = auxspi_save_type(slot_1_type);
	// format game if required
	if (type == 3) {
		//displayStateF(STR_HW_FORMAT_GAME);
		auxspi_erase(slot_1_type);
	}
	// alright, lets right this shit to the ds game!
	//displayStateF(STR_HW_WRITE_GAME);
	u32 LEN = 0, num_blocks = 0, shift = 0;
	switch (type) {
	case 1:
		shift = 4; // 16 bytes
		break;
	case 2:
		shift = 5; // 32 bytes
		break;
	case 3:
		shift = 8; // 256 bytes
		break;
	default:
		return;
	}
	LEN = 1 << shift;
	num_blocks = 1 << (size - shift);
	for (unsigned int i = 0; i < num_blocks; i++) {
		if (i % (num_blocks >> 6) == 0)
			//displayProgressBar(i+1, num_blocks);
		sysSetBusOwners(true, true);
		auxspi_write_data(i << shift, whatthefuck, LEN, type, slot_1_type);
	}
}


// ---------------------------------------------------------------------
u8 log2trunc(u32 size0)
{	
	u8 size = 1;
	while (size0 > (u32)(1 << size)) {
		size++;
	}
	return size;
}


// This function is called on boot; it detects the hardware configuration and selects the mode.
u32 hwDetect()
{
	
	// Okay, maybe it is a regular GBA game instead
	// make sure its a gba cart
	if (gbaIsGame())
		return 1;
	
	// Nothing unique found, so enter WiFi mode
	return 0;
}

// --------------------------------------------------------
// uncomment this to enable slot 1 operations... but implement "dsiUnlockSlot1()" before!
// the following two functions are *untested* and may not work at all!
//#define SLOT_1_UNLOCKED

void hwBackupGBA(u8 type)
{
	if ((type == 0) || (type > 5))
		return;

	if ((type == 1) || (type == 2)) {
		// This is not to be translated, it will be removed at some point.
		iprintf("Yo i cant fucking read this shit!\n");
		return;
	}
	
	// we arent going to be saving to a file now, we have no where to go!
	// will instead save to another console later
	
	//char path[256];
	//char fname[256] = "";
	//fileSelect("/", path, fname, 0, true, false);
	
	/*if (!fname[0]) {
		find_unused_filename((char*)0x080000a0, path, fname);
	}
	char fullpath[512];
	sprintf(fullpath, "%s/%s", path, fname);*/
	
	uint32 size = gbaGetSaveSize(type);
	iprintf("SAVE SIZE: %x\n", size);
	iprintf("Dumping save...\n");
	gbaReadSave(data, 0, size, type);
	
	/*//displayStateF(STR_HW_WRITE_FILE, fullpath);
	FILE *file = fopen(fullpath, "wb");
	fwrite(data, 1, size, file);
	fclose(file);*/

	iprintf("Save dumped!\n");
	//while(1);
}

// we will be reusing the shit below at a later date.
/*void hwRestoreGBA()
{
	u8 type = gbaGetSaveType();
	if ((type == 0) || (type > 5))
		return;
	
	if ((type == 1) || (type == 2)) {
		// This is not to be translated, it will be removed at some point.
		displayMessageF(STR_STR, "I can't write this save type\nyet. Please use Rudolphs tool\ninstead.");
		return;
	}
	
	uint32 size = gbaGetSaveSize(type);
	
	char path[256];
	char fname[256] = "";
	fileSelect("/", path, fname, 0);
	char fullpath[512];
	sprintf(fullpath, "%s/%s", path, fname);

	//displayStateF(STR_HW_READ_FILE, fname);
	FILE *file = fopen(fullpath, "rb");
	fread(data, 1, size, file);
	fclose(file);
	
	if ((type == 4) || (type == 5)) {
		//displayStateF(STR_HW_FORMAT_GAME);
		gbaFormatSave(type);
	}
	
	//displayStateF(STR_HW_WRITE_GAME);
	gbaWriteSave(0, data, size, type);

	displayStateF(STR_STR, "Done!");

}

void hwEraseGBA()
{
	u8 type = gbaGetSaveType();
	if ((type == 0) || (type > 5))
		return;

	//displayStateF(STR_HW_WARN_DELETE);
	while (!(keysCurrent() & (KEY_UP | KEY_R | KEY_Y))) {};
	gbaFormatSave(type);
	//displayStateF(STR_HW_DID_DELETE);
	while (1);

}*/