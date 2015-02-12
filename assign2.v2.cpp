#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long rec_off;// struture to hold index 
typedef struct 
{ 
	int key; /* Record's key */ 
	long off; /* Record's offset in file */ 
} index_S; 

typedef struct // structure to hold availability list
{ 
	int size; /* Hole's size */ 
	long off; /* Hole's offset in file */ 
} avail_S;

bool binSearch(index_S *index, long key, int start, int end )
{
	if (start >= end)
		return false;

	if(key==index[start+end/2].key)
        return true;
    else
    {
        if (key < index[end/2].key)
        {
        	return binSearch(index,key,start,end/2);
        }
        else
        {
        	return binSearch(index,key,end/2,end);
        }
    }
}

int add(FILE *fp_student, index_S* index_list, long key, int indexend)
// function adds a new record if the record is not present in the file else prints record not added
{
	if (binSearch(index_list,key,0,indexend))
	{
		cout << "Record with SID=" << key << " exists";
		return 0;
	}
	else
	{

	}
	
}

int del()
{
	return 0;
}

int find()
{
	return 0;
}

int main(int argc, char *argv[])
{
	index_S dummy;// variable to load the data from file to the sturct
	avail_S dummy2;
	char *buf;
	string command ="Not END";
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
			while(!feof(fp_index))
			{
				fread(&dummy,sizeof(index_S),1,fp_index);
				index_list[indexend]=dummy;
				indexend++;
			}
			
			// reading the input from the file availibility to the array of structs avail
			fp_avail=fopen("availibility","r+b");
			while(!feof(fp_avail))
			{
				fread(&dummy2,sizeof(avail_S),1,fp_avail);
				avail_list[availend]=dummy2;
				availend++;
			}
		}
	long key=command[2];
	
	cin >> command; //reads command from the user
	while(!command.compare("end"))
	{
		if (command.find("add")==0)
			add(fp_student,index_list,indexend,key);
		else if (command.find("find")==0)
			find();
		else if(command.find("del")==0)
			del();
		else 
			cout << "Command not found" << "\n" << "Please enter a valid command";
		cin >> command; //reads command from the user
	}
	fp_index=fopen("index","r+b"); //writing the index file back to the disc
	for (int i=0; i < indexend; i++)
	{
		dummy=index_list[i];
		fwrite(&dummy,sizeof(index_S),1,fp_index);
		i++;
	}
	fclose(fp_index);

	fp_avail=fopen("availability","r+b"); // writing the availibility file back to the disc
	for (int i=0; i < availend; i++)
	{
		dummy2=avail_list[i];
		fwrite(&dummy2,sizeof(avail_S),1,fp_avail);
		i++;
	}
	fclose(fp_avail);	
}
