#include "init_dev.h"
#include "spi.h"
#include "button.h"
#include "misc.h"
#include "globaldefs.h"
#include "stdio.h"




float operandus1     = 0;
float operandus2     = 0;
unsigned int clear   = 0;
unsigned int BTN     = 404;
unsigned int clear_counter=0;


void mainloop();
void add_new1(unsigned int btn);
void add_new11(unsigned int x,unsigned int btn);
void got_number(unsigned int btn);
void got_number2(unsigned int x); //ha tizedes pont után
unsigned int got_muvelet(unsigned int btn);
unsigned int convert_char(unsigned int x);
unsigned int convert_char2(char x);
void write_result(unsigned int x);



/*void test()
{
	unsigned int x=404;
	NMR=0;
	wait_ms(1);
	NOE=0;
	NMR=1;
	while(1)
	{	   
		BTN=get_button();
		if(BTN!=404)
		{
			if(clear){
			x=convert_char(1);
			send_char(x);
			wait_ms(1000);
			}
		}
		else send_char(0xFF);		   
	//	for (x=0;x<16;x++){
	//	send_char(x);
		wait_ms(500);	   }	
	}

}		*/


int main ()
{

	Init_Device();
//	test();
	mainloop();
	return 0;
}

void mainloop()
{
	unsigned int task=0, counter = 0;  //milyen operator es hany karaktert kaptunk
	unsigned int temp[6],i,counter2=0, state=0;
	clear_7seg();
	
	while(1)
	{
	//	WDTCN = 0xA5;			   //watchdog timer felhúzása
		wait_ms(200);
		if(clear)
		{
			task=0;
			counter=0;
			BTN=404;
			counter2=0;
			state=0;
			operandus2=0;
			operandus1=0;
			clear=0;
			clear_7seg();
			for(i=0;i<6;i++)temp[i]=0;
			i=0;
		}
		BTN=get_button();
		if(BTN!=404)			   //ha nincs gomb lenyomva
		{
		switch (state)			   
		{
			case 0:
				if((BTN<10)&&(counter<6))
				{
					got_number(BTN);
					temp[counter]=BTN;
					counter++;
					state=0;
				}
				else if(((BTN==10)&&(counter<6))&&(counter))
				{
	
					clear_7seg();
					for(i=0;i<counter;i++)
					{
						if(i==(counter-1))	send_char(convert_char(temp[i])-offs); 
						else send_char(convert_char(temp[i]));
					}
					state=1;
				}
				else if((task)&&(BTN==15))
				{
					write_result(task);
					task=0;
					counter=0;
					counter2=0;
					operandus1=0;
					state=0;
				}
				else if((BTN>10)&&(BTN<15))  
				{
					operandus2=operandus1;
					operandus1=0;
					task=got_muvelet(BTN);
					state=0;
					counter=0;
					counter2=0;
				}
				break;



			//ha tizedes pontot irtunk
			case 1:
				if((BTN<10)&&(counter<6))
					{
						add_new11(counter2,BTN);
						temp[counter]=BTN;
						send_char(convert_char(BTN));
						counter++;
						counter2++;
						state=1;
					}
				else if((BTN>10)&&(BTN<15))   
				{
					operandus2=operandus1;
					operandus1=0;
					task=got_muvelet(BTN);
					state=0;
					counter=0;
					counter2=0;
				}
				else if((task)&&(BTN==15))
				{
					write_result(task);
					task=0;
					counter=0;
					counter2=0;
					operandus1=0;
					state=0;
				}
				break;


		}	
		}
	}
}



void add_new1(unsigned int btn)
{
	operandus1=btn+(operandus1*10);
}	

unsigned int convert_char(unsigned int x)
{	
	unsigned int y;
	switch (x)
	{
		case 0:
			y=null;
			break;
		case 1:
			y=one;
			break;
		case 2:
			y=two;
			break;
		case 3:
			y=three;
			break;	
		case 4:
			y=four;
			break;
		case 5:
			y=five;
			break;
		case 6:
			y=six;
			break;
		case 7:
			y=seven;
			break;
		case 8:
			y=eight;
			break;
		case 9:
			y=nine;
			break;
	}
	return y;
}

void add_new11(unsigned int x,unsigned int btn)
{
	if(x==0)operandus1=operandus1+(0.1*btn);
	if(x==1)operandus1=operandus1+(0.01*btn);	
	if(x==2)operandus1=operandus1+(0.001*btn);
	if(x==3)operandus1=operandus1+(0.0001*btn);
	if(x==4)operandus1=operandus1+(0.00001*btn);
}




void got_number(unsigned int btn)
{
	add_new1(btn);	
	send_char(convert_char(btn));
}




unsigned int got_muvelet(unsigned int btn)
{
	 unsigned int task;
	//waitek  es naneblek hianyoznak
	if(btn==11) 
	{
		clear_7seg();
		send_char(0xBF);	  //-
		send_char(0x8F);	  //I-
		task=1;
	}
	if(btn==12) 
	{
		clear_7seg();
		send_char(0xBF);
		task=2;
		}
	if(btn==13) 
	{
		clear_7seg();
		send_char(0x89);
		task=3;
					
	}
	if(btn==14) 
	{
		clear_7seg();
		send_char(0xCF);
		task=4;
	}	
	return task;
}

void write_result(unsigned int x)
{
	char array[8];
	unsigned int i;
	if(x==1)operandus2+=operandus1;
	else if(x==2)operandus2=operandus2-operandus1; 
	else if(x==3)operandus2=operandus1*operandus2;
	else if(x==4)
	{
		if((operandus1==0)&&(x==4))
		{
			write_err();
			operandus1=0;
			operandus2=0;
			return;
		}
		else operandus2=operandus2/operandus1;
	}
	if((operandus2>999999)||(operandus2<((-1)*99999)))
	{
		write_err();
		operandus2=0;
	}
	//nullaval valo osztas
	else if((operandus1==0)&&(x==4))
	{
		write_err();
		operandus2=0;
	}
	else 
	{
		if(operandus2<0)
		{
			operandus2=(-1)*operandus2;
			send_char(0xBF);
			sprintf(array , "%5f" , operandus2);	
			for(i=0;i<6;i++)
			{
				if(array[i+1]=='.')
				{
					send_char(convert_char2(array[i])-offs);
					i++;
				}
				else send_char(convert_char2(array[i]));
			}
		}
		else if(operandus2==0)
		{
			clear_7seg();
			send_char(null);
		}
		else
		{
			sprintf(array , "%6f" , operandus2);	
			for(i=0;i<7;i++)
			{
				if(array[i+1]=='.')
				{
					send_char(convert_char2(array[i])-offs);
					i++;
				}
				else send_char(convert_char2(array[i]));
			}
		}
	}
	operandus1=0;
}

unsigned int convert_char2(char x)
{
	unsigned int y;
	switch (x)
	{
		case '0':
			y=null;
			break;
		case '1':
			y=one;
			break;
		case '2':
			y=two;
			break;
		case '3':
			y=three;
			break;	
		case '4':
			y=four;
			break;
		case '5':
			y=five;
			break;
		case '6':
			y=six;
			break;
		case '7':
			y=seven;
			break;
		case '8':
			y=eight;
			break;
		case '9':
			y=nine;
			break;
	}
	return y;
}

 //ha hosszabb ideig van lenyomva torol mindent

void my_it() interrupt 14	
{
	char SFRPAGE_SAVE=SFRPAGE;
	//clear_counter++;
	SFRPAGE   = TMR3_PAGE;
	TF3=0;
//	interrupt test
//	if(clear_counter>20)clear_counter=0;  
	if(clear_counter<20)G_LED=0;
	else G_LED=1;	 
	if(BTN==10)	clear_counter++;
	else clear_counter=0;
	if(clear_counter==40) 
	{
		clear_counter=0;
		clear=1;
		G_LED=0x00;
	}
	
	SFRPAGE=SFRPAGE_SAVE;


}