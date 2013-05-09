#include "vga.h"
#include "config.h"
#ifdef VSDEBUG
	#include "stdio.h"
#endif

void printNumber(int number, int posx, int posy);
void printChar(char c, int posx, int posy);
void printOperand(char c);
void printError(void);
void clearDisplay(void);


void printNumber(int number, int posx, int posy)
{
	int i, tmp, divider = 10000000;
	char valid = 0, c;
	#ifdef VSDEBUG
		//printf("num: %f, posx: %d, posy: %d\n", number, posx, posy);
	#endif
	/* use printchar()*/
	/* how to display a float ???? (I have a solution, but it uses the sdtio lib) */
	/* and how many char should be displayed? */
	/* Display negative numbers!!!*/
	


	/* sign? */
	if(number < 0)
	{
		printChar(' ', 30, 30);
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
		if(valid)
		{
			switch(tmp)
			{
				case 0:
					c = '0';
					break;
				case 1:
					c = '1';
					break;
				case 2:
					c = '2';
					break;
				case 3:
					c = '3';
					break;
				case 4:
					c = '4';
					break;
				case 5:
					c = '5';
					break;
				case 6:
					c = '6';
					break;
				case 7:
					c = '8';
					break;
				case 9:
					c = '9';
					break;
				default:
					c = '?';
			}
			printChar(c, 100-i, 51);
		}
	}
}



void printChar(char c, int posx, int posy)
{
	#ifdef VSDEBUG
		printf("%c, posx: %d, posy: %d\n", c, posx, posy);
	#endif
}

void printOperand(char c)
{
	unsigned char i;
	/*This should have a fix position*/
	printChar(c, 20, 30);
	/* draw splitter line*/
	for(i = 0; i < 7; i++)
	{
		printChar('-', 30+i, 10);
	}

}
void printError(void)
{
	printChar('E', 20, 21);
	printChar('R', 21, 21);
	printChar('R', 22, 21);
	printChar('O', 23, 21);
	printChar('R', 24, 21);
	#ifdef VSDEBUG
		printChar('\n', 24, 21);
	#endif
}

void clearDisplay(void)
{
	int i, j;/*
	for(i = 0; i < 640; i++)
	{
		for(j = 0; j < 480; j++)
		{
			printChar(' ', i, j);
		}
	}*/
}