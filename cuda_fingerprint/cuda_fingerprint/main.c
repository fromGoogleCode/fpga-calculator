#include "stdio.h"

#define TANIMOTO_TRESHOLD 93.0

void load_database(int * database);
float compare_fingerprints(int* database);
void getFootprint(unsigned int* pointer);

typedef struct
{
	int idx1;
	int idx2;
	float tanimoto;
} tTanimotoOut;

// or
//64 bit variable
void main()
{
	int*database;
	int* compare_database;
	tTanimotoOut* output_buffer;
	int dbsize, cbdsize;
    database = (unsigned int*) malloc(1000*32*sizeof(unsigned int));
	dbsize = load_database(database);
	cbdsize = load_database(compare_database);
	
	printf("Size of int: %d.",sizeof(int));
	compare_fingerprints(database,compare_database,dbsize,cbdsize,output_buffer);
}


float compare_fingerprints(int* database,int* compare_database,int database_size,int compared_db_size ,tTanimotoOut *output_buffer)
{
	int fingerPrintIdx;
	int comparedFingerPrintIdx;
	int partIdx;
	float s,a,b,c;
	int resultIdx = 0;

	/* Finger prints from database */
	for(fingerPrintIdx = 0; fingerPrintIdx < database_size ; fingerPrintIdx)
	{
		a = b = c = 0;
		s = 0;
		/*  Fingerprints of the other database */
		for(comparedFingerPrintIdx = 0;comparedFingerPrintIdx < compared_db_size;comparedFingerPrintIdx++)
		{
			/* Iterate thorugh fingerprints (32 integers in each)*/
			for(partIdx = 0;partIdx < 32;partIdx++)
			{
				/* Get bit counts  */
				a += count_bits(database[fingerPrintIdx + partIdx]);
				b += count_bits(compare_database[comparedFingerPrintIdx + partIdx]);
				c += count_bits(database[fingerPrintIdx + partIdx] & compare_database[comparedFingerPrintIdx + partIdx]);		
			}
			s = c/(a + b - c);
			/* Check values*/
			if(s < TANIMOTO_TRESHOLD)
			{
				output_buffer->idx1 = fingerPrintIdx;
				output_buffer->idx2  = comparedFingerPrintIdx;
				output_buffer->tanimoto = s;
			}

		}
	}
}

float count_bits(int value)
{
	float count = 0;
	while (value) 
	{
		count++;
		value = (value - 1) & value;
	}
	return count;
}

int load_database(int * database)
{
	//TODO: load text based database
}


void getFootprint(unsigned int *pointer)
{
	unsigned int footprint[992][32];

	unsigned int negated = 0x0u;
	unsigned int number = ~0x0u;
	
	
	unsigned int i, j, k, tmp = 0u, pos = 0u;

	

	for (i = 0u; i < 31u; i++)
	{
		tmp = number >> i; 
		negated = ~tmp;

		printf("%u num: %u\nnegated: %u\n\n", i, tmp, negated);
		
		for(j=0u; j < 32u; j++)
		{
			footprint[pos+j][j] = tmp;
			if(j<31u)
			footprint[pos+j][j+1u] = negated;
			for(k=0u; k < j; k++)
			{
				footprint[pos+j] [k] = 0u;
			}
			for(k=j+2; k < 32; k++)
			{
				footprint[pos+j] [k] = 0u;
			}
		}

		pos += 32;
	}

	
	for(i=0u; i < 992; i++)
	{
		for(j = 0u; j < 32; j++)
		{
			pointer[(i * 32u) + j] = footprint[i][j];
		}
	}
}