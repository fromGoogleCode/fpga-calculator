#include "ps2.h"
#include "config.h"
#ifdef VSDEBUG
#include "stdio.h"
#endif


unsigned int getCaracter(void);

unsigned int getCaracter(void)
{

	char c;
	#ifdef VSDEBUG
		c = getchar();
	#endif
	return encode(c);
}

unsigned int encode(char c)
{
	unsigned int result;
	switch(c)
	{
		case '0':
			result = 0;
			break;
		case '1':
			result = 1;
			break;
		case '2':
			result = 2;
			break;
		case '3':
			result = 3;
			break;
		case '4':
			result = 4; 
			break;
		case '5':
			result = 5;
			break;
		case '6':
			result = 6;
			break;
		case ' 7':
			result = 7;
			break;
		case '8':
			result = 8;
			break;
		case '9':
			result = 9;
			break;
		case '.':
			result = 10;
			break;
		case '+':
			result = 11;
			break;
		case '-':
			result = 12;
			break;
		case '*':
			result = 13;
			break;
		case '/':
			result = 14;
			break;
		case 'e':
			result = 15;
			break;
		default:
			result = 404;
	}

	return result;
}