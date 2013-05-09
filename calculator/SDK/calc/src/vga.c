#include "vga.h"
#include "config.h"
#include "xparameters.h"

void printNumber(int number, int posx, int posy);
void printChar(char c, int posx, int posy);
void printOperand(char c);
void printError(void);
void clearDisplay(void);

#define RESULT_LINE 13

void printNumber(int number, int posx, int posy)
{
	int i, tmp, divider = 10000000;
	char valid = 0, c;

	/* use printchar()*/
	/* how to display a float ???? (I have a solution, but it uses the sdtio lib) */
	/* and how many char should be displayed? */
	/* Display negative numbers!!!*/
	


	/* sign? */
	if(number < 0)
	{
		printChar(14, 2, 13);
		number = -number;
	}
	/* parse the number */
	for(i = 0; i < 8; i++)
	{
		tmp = number/divider;
		number = number % divider;
		divider = divider / 10;
		if(tmp > 0)
		{
			valid++;
		}
		if(valid || (i == 7))
		{
			switch(tmp)
			{
				case 0:
					c = 17;
					break;
				case 1:
					c = 18;
					break;
				case 2:
					c = 19;
					break;
				case 3:
					c = 20;
					break;
				case 4:
					c = 21;
					break;
				case 5:
					c = 22;
					break;
				case 6:
					c = 23;
					break;
				case 7:
					c = 24;
					break;
				case 8:
					c = 25;
					break;
				case 9:
					c = 26;
					break;
				default:
					c = '?';
			}
			printChar(c, posx + i - 12, posy);
		}
	}
}



void printChar(char c, int x, int y)
{
	unsigned int addr = (x + y *128)*4 + XPAR_VGA_0_MEM1_BASEADDR;
	volatile unsigned int * ptr = (unsigned int *) addr;
	*ptr = c;
}

void printOperand(char c)
{
	unsigned char i;
	/*This should have a fix position*/
	printChar(c, 2, 11);
	/* draw splitter line*/
	for(i = 0; i < 7; i++)
	{
		printChar(14, 10-i, 12); /*14 '-'*/
	}

}
void printError(void)
{
	/* Error */
	printChar(38, 5, RESULT_LINE);
	printChar(51, 6, RESULT_LINE);
	printChar(51, 7, RESULT_LINE);
	printChar(48, 8, RESULT_LINE);
	printChar(51, 9, RESULT_LINE);
}

void clearDisplay(void)
{
	int i, j;
	for(i = 0; i < 80; i++)
	{
		for(j = 0; j < 60; j++)
		{
			printChar(0x63, i, j);
		}
	}
}
