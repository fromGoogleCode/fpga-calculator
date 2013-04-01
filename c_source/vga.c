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


void printNumber(float number, int posx, int posy)
{
	#ifdef VSDEBUG
		printf("num: %f, posx: %d, posy: %d\n", number, posx, posy);
	#endif
	/* use printchar()*/
	/* how to display a float ???? (I have a solution, but it uses the sdtio lib) */
	/* and how many char should be displayed? */
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

}