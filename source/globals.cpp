// from github
#include "globals.h"
// hey welcome back
#include "auxspi.h"

u8 *data;
u32 size_buf;

auxspi_extra slot_1_type = AUXSPI_FLASH_CARD;

char ftp_ip[16] = "ftp_ip";
char ftp_user[64] = "ftp_user";
char ftp_pass[64] = "ftp_pass";
int ftp_port = 0;
bool ftp_active = false;

int ir_delay = 1200;

char device[16] = "/";

char txt[256] = "";

u32 mode = 0;
u32 ezflash = 0;

int slot2 = -1;

bool sdslot = false;

u32 extra_id[EXTRA_ARRAY_SIZE];
u8 extra_size[EXTRA_ARRAY_SIZE];