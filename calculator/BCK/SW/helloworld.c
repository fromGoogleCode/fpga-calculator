/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xps2.h"

static XPs2 Ps2Inst; 		/* Ps2 driver instance */
u8 RxBuffer;
void print(char *str);

void pputchar(int x, int y, unsigned char c )
{
	unsigned int addr = (x + y *128)*4 + XPAR_VGA_0_MEM1_BASEADDR;
	volatile unsigned int * ptr = (unsigned int *) addr;
	*ptr = c;
}

u8 ggetchar()
{

	unsigned int BytesReceived;
	BytesReceived = XPs2_Recv(&Ps2Inst, &RxBuffer, 1);
	return RxBuffer;
}

int main()
{
    int i = 0;
    XPs2_Config *ConfigPtr;
	u8 ch = 0x14;
    init_platform();
//
    print("Hello World\n\r");

    cleanup_platform();
	ConfigPtr = XPs2_LookupConfig(XPAR_PS2_0_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}
	XPs2_CfgInitialize(&Ps2Inst, ConfigPtr, ConfigPtr->BaseAddress);
	while(1)
	{
		ch = ggetchar();
		for(i = 0; i< 63; i++)
		{
			pputchar(i,i,ch);
		}
	}
    return 0;
}
