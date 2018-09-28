/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>

#include <stdio.h>
#include <sstream>

// used borrowed code
#include "gba.h"
#include "globals.h"
#include "hardware.h"
#include "dsCard.h"



volatile int frame = 0;

// use this later
int gooddump = 0;


//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}

void printOptions(int sel, bool clear){
	// does the screen need to be cleared?
	if (clear){
		// clear it
		iprintf("\x1b[2J");
	}
	// print the text at the top
	iprintf("JonDump GBA mode select\n");
	// print certain strings based on what option is selected
	switch (sel){
		case 1:
			iprintf("Mode: 1\n");
			iprintf("Dump GBA save to DS card\n");
			break;
		case default:
			iprintf("error: invalid mode selected!\n");
			break;
	}
	// finally, print the text at the bottom
	iprintf("Use Dpad to pick, a to confirm\n");
}


// mode gba code borrowed from dssavemanager
// and modifyed to work for what i need
void mode_gba()
{
	// This function takes some time, since it needs to parse the entire GBA module
	//  for a magic string. It is only called when truly necessary. (i.e. once for now)
	iprintf("Getting GBA save type, please wait...\n");
	u8 gbatype = gbaGetSaveType();

	int selection = 1;
	// exit flag for while loop
	int whileexit = 0;
	// clear the screen
	
	// print basic menu thing
	printOptions(selection, true);
	
	swiWaitForVBlank();
	
	while (whileexit == 0){
		
		
	}
	if (selection == 1) {
		// backup mode
		iprintf("preparing to dump save...\n");
		hwBackupGBA(gbatype);
		// check to make sure data has something in it
		if (data == NULL){
			iprintf("ERROR: DUMP FAILED!\n");
			gooddump = 0;
		} else {
			// i guess everything is okay now
			gooddump = 1;
		}
		if (gooddump == 1){
			// if its a good dump, or atleast i hope it is, write the save to nintendo ds game card
			// Delete the save file from the cartridge
			iprintf("Writing GBA Save to DS game...\n");
			writeGBAtoDS(data);
		}
		}
		
		/*if (mode == Restore) {
			// restore mode...unused
			hwRestoreGBA();
		}
		
		if (mode == Erase) {
			// erase mode, unused for now
			hwEraseGBA();
		}*/
}

// apparently we need this
unsigned short toShort(unsigned char* bytes) {
    return (unsigned short)(((unsigned char)bytes[1] << 8) |
                   (unsigned char)bytes[0]);
}

	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	//we dont need this anymore lmao
	//touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("GBA Save Dumper\n");
	iprintf("Verion 1.0\n");
	iprintf("by EzioisAwesome56\n");
	iprintf("With code from dssavemanager and dsgmwifi\n\n");
	// start doing things
	iprintf("INIT...\n");
	// own the bus
	sysSetBusOwners(true, true);
	// detect hardware
	mode = hwDetect();
	// prepare the data buffer
	data = (u8*)malloc(size_buf);
	iprintf("INIT MEMORY...\n");
	while (data == NULL) {
		size_buf >>= 1;
		data = (u8*)malloc(size_buf);
	}
	// find out what hardware we have to work with
	switch (mode) {
		case 1:
			iprintf("GBA Game detected!\n");
			mode_gba();
			break;
		default:
			iprintf("Error: no hardware found!\n");
			break;
	}
	iprintf("Press START to shutdown...\n");
	
 
	while(1) {
	
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;


		// this is just a loop that shutsdown the ds if you press start.
	}

	return 0;
}
