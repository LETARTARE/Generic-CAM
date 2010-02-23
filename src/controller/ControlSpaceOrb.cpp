// SpaceOrb.cpp: implementation of the CSpaceOrb class.
// adapted from Linux Kernels spaceorb.c
//////////////////////////////////////////////////////////////////////

#include "ControlSpaceOrb.h"

ControlSpaceOrb::ControlSpaceOrb()
{
	InitDevice();
}

ControlSpaceOrb::~ControlSpaceOrb()
{

}

void ControlSpaceOrb::InitDevice()
{
	idx = 0;
}

bool ControlSpaceOrb::ProcessPacket()
{
	static unsigned char spaceorb_xor[] = "SpaceWare";
	//static unsigned char spaceorb_errors[7][256] = { "EEPROM storing 0 failed", "Receive queue overflow", "Transmit queue timeout","Bad packet", "Power brown-out", "EEPROM checksum error", "Hardware fault" };
	unsigned char c = 0;
	int i;
	if(idx < 2) return false;
	for(i = 0; i < idx; i++)
		c ^= Data[i];
	if(c) return false;
	switch(Data[0]){
	case 'R': /* Reset packet */
		Data[idx - 1] = 0;
		for(i = 1; i < idx && Data[i] == ' '; i++)
			;
		//printk(KERN_INFO "input%d: %s [%s] on serio%d\n",spaceorb->dev.number, spaceorb_name, spaceorb->data + i, spaceorb->serio->number);
		break;
	case 'D': /* Ball + button data */
		if(idx != 12) return false;
		for(i = 0; i < 9; i++)
			Data[i + 2] ^= spaceorb_xor[i];
		Axis[0] = (Data[2] << 3) | (Data[3] >> 4);
		Axis[2] = ((Data[3] & 0x0f) << 6) | (Data[4] >> 1);
		Axis[1] = ((Data[4] & 0x01) << 9) | (Data[5] << 2) | (Data[4] >> 5);
		Axis[3] = ((Data[6] & 0x1f) << 5) | (Data[7] >> 2);
		Axis[4] = ((Data[7] & 0x03) << 8) | (Data[8] << 1) | (Data[7] >> 6);
		Axis[5] = ((Data[9] & 0x3f) << 4) | (Data[10] >> 3);
		for(i = 0; i < 6; i++)
			Axis[i] -= ((Axis[i] & 0x200)? 1024 : 0);
		for(i = 0; i < 7; i++)
			Button[i] = (Data[1] >> i) & 1;
		break;
	case 'K': /* Button data */
		if(idx != 5) return false;
		for(i = 0; i < 7; i++)
			Button[i] = (Data[2] >> i) & 1;
		break;
	case 'E': /* Error packet */
		if(idx != 4) return false;
		//printk(KERN_ERR "joy-spaceorb: Device error. [ ");
		//for (i = 0; i < 7; i++) if (data[1] & (1 << i)) printk("%s ", spaceorb_errors[i]);
		//printk("]\n");
		break;
	}
	return true;
}

void ControlSpaceOrb::DataIn(unsigned char c)
{
	if(~c & 0x80){
		if(idx) ProcessPacket();
		idx = 0;
	}
	if(idx < CONTROLSPACEORB_MAXDATALENGTH){
		Data[idx++] = c & 0x7f;
	}
}

