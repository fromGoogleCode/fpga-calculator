#include "calculator.h"
#include "ps2.h"
#include "vga.h"
#include "config.h"


float operand1     = 0;
float operand2     = 0;
/*start state */
unsigned int clear   = 0;
/* 404 means no valid button pushed*/
unsigned int BTN     = 404;
unsigned int clear_counter=0;


void startCalculator(void);
void add_new1(unsigned int btn);
void add_new11(unsigned int x,unsigned int btn);
void got_number(unsigned int btn,unsigned int task);
void got_number2(unsigned int x); /* after decimal point*/
unsigned int got_operand(unsigned int btn);
void write_result(unsigned int x);



void startCalculator(void)
{
	/* operator */
	unsigned int task=0;
	/* current number of characters */
	unsigned int counter = 0;
	/*buffer to read operands*/
	unsigned int temp[MAX_NUM_OF_CHARACTERS];
	/* for cycle variable */
	unsigned int i;
	unsigned int counter2=0;
	
	#ifdef DECIMAL_POINT
		unsigned int state=0;
	#endif
	
	
	clearDisplay();
	
	while(TRUE)
	{
		/* watchdog timer set up should be here if necessary */
		/*wait_ms(200);*/
		
		/* first execution of the loop (initialzation)*/
		if(clear)
		{
			task=0;
			counter=0;
			BTN=404;
			counter2=0;
			#ifdef DECIMAL_POINT
					state=0;
			#endif
			operand2=0;
			operand1=0;
			clear=0;
			clearDisplay();

			for(i=0; i < MAX_NUM_OF_CHARACTERS; i++)
			{
				temp[i] = 0;
			}
			i=0;
		}
		BTN = getCaracter();
		/* if BTN has a valid value */
		if(BTN!=404)			  
		{
		#ifdef DECIMAL_POINT
		switch (state)			   
		{
			case 0:	
		#endif
				if((BTN < 10) &&                       /* got a number 0...9 */
					(counter < MAX_NUM_OF_CHARACTERS)) /* the character buffer is not full */
				{
					got_number(BTN, task);
					temp[counter]=BTN;
					counter++;
					#ifdef DECIMAL_POINT
						state=0;
					#endif
				}
				else if(((BTN == 10) &&                  /* decimal pont character*/
					(counter < MAX_NUM_OF_CHARACTERS))   /* the character buffer is not full */
					&&(counter))                         /* an not empty*/
				{
	
				    /* TODO */
					/* Append to the temp[counter-1] character a decimal point*/
					#ifdef DECIMAL_POINT
						state=1;
					#endif
				}
				else if((task)&&  /* an operator already given and*/
					(BTN == 15))  /* the enter was typed display the result*/
				{
					write_result(task);
					task=0;
					counter=0;
					counter2=0;
					operand1=0;
					#ifdef DECIMAL_POINT
						state=0;
					#endif
				}
				else if((BTN > 10) && (BTN < 15)) /* got an operand */  
				{
					operand2=operand1;
					operand1=0;
					task=got_operand(BTN);
					#ifdef DECIMAL_POINT
						state=0;
					#endif
					counter=0;
					counter2=0;
				}
				#ifdef DECIMAL_POINT
				break;



			//ha tizedes pontot irtunk
			case 1:
				if((BTN < 10)&&
					(counter < MAX_NUM_OF_CHARACTERS))
					{
						add_new11(counter2,BTN);
						temp[counter]=BTN;
						//send_char(convert_char(BTN));
						counter++;
						counter2++;
						state=1;
					}
				else if((BTN > 10)&&(BTN < 15))   
				{
					operand2=operand1;
					operand1=0;
					task=got_operand(BTN);
					state=0;
					counter=0;
					counter2=0;
				}
				else if((task) && (BTN == 15))
				{
					write_result(task);
					task=0;
					counter=0;
					counter2=0;
					operand1=0;
					state=0;
				}
				break;

		}
		#endif
		}
	}
}



void add_new1(unsigned int btn)
{
	operand1=btn+(operand1*10);
}	

void add_new11(unsigned int x,unsigned int btn)
{
	if(x==0)operand1=(float)(operand1+(0.1*btn));
	if(x==1)operand1=(float)(operand1+(0.01*btn));	
	if(x==2)operand1=(float)(operand1+(0.001*btn));
	if(x==3)operand1=(float)(operand1+(0.0001*btn));
	if(x==4)operand1=(float)(operand1+(0.00001*btn));
}




void got_number(unsigned int btn, unsigned int task)
{
	add_new1(btn);	
	/* write operand to the display*/
	if(task)
	{
		printNumber((int)operand1, 1, 1);
	}
	else
	{
		printNumber((int)operand1, 1, 2);
	}
}




unsigned int got_operand(unsigned int btn)
{
	 unsigned int task;
	 switch(btn)
	 {
		case 11:
			task = 1;
			printOperand('+');
			break;
		case 12:
			task = 2;
			printOperand('-');
			break;
		case 13:
			task = 3;
			printOperand('*');
			break;
		case 14:
			task = 4;
			printOperand('/');
			break;
	 }	
	return task;
}

void write_result(unsigned int x)
{
	char array[8];
	unsigned int i;
	if(x==1)operand2 += operand1;
	else if(x==2)operand2 = operand2 - operand1; 
	else if(x==3)operand2 = operand1 * operand2;
	else if(x==4)
	{
		/* division by zero*/
		if((operand1==0)&&(x==4))
		{
			printError();
			operand1=0;
			operand2=0;
			return;
		}
		else operand2=operand2/operand1;
	}
	/* overflow necessary? */
	if((operand2>999999)||(operand2<((-1)*99999)))
	{
		printError();
		operand2=0;
	}
	/* division by zero*/
	else if((operand1==0)&&(x==4))
	{
		printError();
		operand2=0;
	}
	else 
	{
		printNumber(operand2, 10, 10);
		/*if(operand2<0)
		{
			operand2=(-1)*operand2;
			//send_char(0xBF);
			//sprintf(array , "%5f" , operandus2);	
			for(i=0;i<6;i++)
			{
				if(array[i+1]=='.')
				{
					//send_char(convert_char2(array[i])-offs);
					i++;
				}
				//else send_char(convert_char2(array[i]));
			}
		}
		else if(operand2==0)
		{
			//clear_7seg();
			//send_char(null);
		}
		else
		{
			//sprintf(array , "%6f" , operandus2);	
			for(i=0;i<7;i++)
			{
				if(array[i+1]=='.')
				{
					//send_char(convert_char2(array[i])-offs);
					i++;
				}
				//else send_char(convert_char2(array[i]));
			}
		}*/
	}
	operand1=0;
}


