#ifndef GLOBALS_H
#define GLOBALS_H

#include <nds.h>
#include "auxspi.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 3
#define VERSION_MICRO 0
#define VERSION_EXTRA "RC2"

// this enables a custom font. it does not work yet, stuff is missing, so please uncomment
//  this line only for testing and development purposes!
#define ENABLE_CUSTOM_FONT

extern u8 *data;
extern u32 size_buf;

extern auxspi_extra slot_1_type;

extern char ftp_ip[16];
extern char ftp_user[64];
extern char ftp_pass[64];
extern int ftp_port;
extern bool ftp_active;

extern int ir_delay;

// all libfat access will be using this device. default value = "/", i.e. "default" DLDI device
extern char device[16];

// text buffer for composing various messages
extern char txt[256];

extern u32 mode;
extern u32 ezflash;

extern int slot2;

extern bool sdslot;

// this should be enough for the forseeable future
#define EXTRA_ARRAY_SIZE 16

extern u32 extra_id[EXTRA_ARRAY_SIZE];
extern u8 extra_size[EXTRA_ARRAY_SIZE];

#endif // GLOBALS_H