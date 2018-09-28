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

// shit stolen from ds game maker
char DSGM_buffer[4096];
size_t DSGM_wirelessDataLength = 0;
bool DSGM_newWirelessData = false;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}

// dswifi shit
inline void setWirelessMode(enum WIRELESS_MODE mode) {
  if(mode == WIRELESS_MODE_WIFI || mode == WIRELESS_MODE_NIFI) wirelessMode = mode;
}

// shit stolen from ds game maker
// apparently handles wireless shit
void DSGM_WirelessHandler(int packetID, int readlength) {
	Wifi_RxRawReadPacket(packetID, readlength, (unsigned short *)DSGM_buffer);
	
	DSGM_wirelessDataLength = readlength - 32;
	DSGM_newWirelessData = true;
}

// more shit from dsgame maker
// this time, you use it for sending shit
void DSGM_SendWirelessData(unsigned short *buffer, int length) {
	if(Wifi_RawTxFrame(length, 0x0014, buffer) != 0) iprintf("SEND ERROR\n");
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
	// clear the screen
	iprintf("\x1b[2J");
	swiWaitForVBlank();
		
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
	iprintf("MEM FREE: %x\n", size_buf);
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
	// unfished feature: nifi sending to a dsi to save
	// i couldnt get the dsi to write to sd,so this idea got cut
	// init nifi from DS game maker
	/*iprintf("INIT NIFI...\n");
	// code stolen from DSGM_Wireless.c
	setWirelessMode(WIRELESS_MODE_NIFI);
	Wifi_InitDefault(false);
	Wifi_SetPromiscuousMode(1);
	Wifi_EnableWifi();
	Wifi_RawSetPacketHandler(DSGM_WirelessHandler);
	Wifi_SetChannel(10);
	iprintf("NIFI INIT DONE\n");
	// if theres nothing, do nothing, obviously
	iprintf("Now entering NIFI send loop\n");*/
	// Delete the save file from the cartridge
	iprintf("Writing GBA Save to DS game...\n");
	writeGBAtoDS(data);
	iprintf("Press START to shutdown...\n");
	
	// BUT WAIT!
	// convert this thing first
	//unsigned short buffer[(2 * sizeof(int)) / sizeof(unsigned short)];
	//memcpy(buffer, data, gbaGetSaveSize(gbaGetSaveType()));
	
 
	while(1) {
	
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		// send data over nifi?
		//DSGM_SendWirelessData(buffer, gbaGetSaveSize(gbaGetSaveType()));


		// print at using ansi escape sequence \x1b[line;columnH 
		//dont do anything rofl
	}

	return 0;
}
