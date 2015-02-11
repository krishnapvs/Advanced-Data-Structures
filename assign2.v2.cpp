#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

long rec_off;
// struture to hold index 
typedef struct 
{ 
	int key; /* Record's key */ 
	long off; /* Record's offset in file */ 
} index_S; 


// structure to hold availability list
typedef struct 
{ 
	int size; /* Hole's size */ 
	long off; /* Hole's offset in file */ 
} avail_S;


int main()
{
	index_S dummy;// variable to load the data from file to the sturct
	avail_S dummy2;
	char *buf;
	long rec_off;
	int rec_siz;
	FILE *fp_index; /* Output file stream */ 
	FILE *fp_avail; // Output file stream for availability list
	FILE *fp_student; // output file stream for student database file
	index_S *index_list;
    avail_S *avail_list;
	int indexend=0;  // pointer to keep track of the index struct
	int availend=0; // pointer to keep track of the index struct
	index_list = new index_S[10000];
	avail_list = new avail_S[10000];

	
	if ( ( fp_student = fopen( "student.db", "r+b" ) ) == NULL ) 
		{
			fp_student = fopen( "student.db", "w+b" ); 
		} 
		else 
		{ 
			rec_off = 0; 
			fseek( fp_student, rec_off, SEEK_SET ); 
			fread( &rec_siz, sizeof( int ), 1, fp_student ); 
			buf = new char( rec_siz + 1 ); 
			fread( buf, 1, rec_siz, fp_student ); 
			buf[ rec_siz ] = '\0'; 
			// reading the input from the file index to the array of structs index
			fp_index=fopen("index","r+b");
			while(!feof(fp_index));
			{
				fread(&dummy,sizeof(index_S),1,fp_index);
				index_list[indexend]=dummy;
				indexend++;
			}
			
			// reading the input from the file availibility to the array of structs avail
			fp_avail=fopen("availibility","r+b");
			while(!feof(fp_avail));
			{
				fread(&dummy2,sizeof(avail_S),1,fp_avail);
				avail_list[availend]=dummy2;
				availend++;
			}



		}
	
}
