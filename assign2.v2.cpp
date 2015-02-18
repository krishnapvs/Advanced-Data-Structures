#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

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
	if (start > end)
		return false;
	int mid = (start+end)/2;
	if(key==index[mid].key)
        return true;
    else
    {
        if (key < index[mid].key)
        {
        	return binSearch(index,key,start,mid-1);
        }
        else
        {
        	return binSearch(index,key,mid+1,end);
        }
    }
}

int availaibility(long key,avail_S* avail_list,int* availend, int fit_type)
{
	switch(fit_type){
		0: //best fit

		break;
		1: // first fit
		break;
		2: //worst fit
		break;
	}

}


int add(FILE *fp_student, index_S* index_list,
	 long key, int* indexend,int fit_type, avail_S* avail_list,
	 int* availend)
// function adds a new record if the record is not present in the file else prints record not added
{
	if (binSearch(index_list,key,0,*indexend-1))
	{
		cout << "Record with SID=" << key << " exists";
		return 0;
	}
	else
	{
		// we check to see if there is availibility in the availablilty list
		int availOff=availaibility(key,avail_list,availend, fit_type);

		// adding the record to the sudent file
		fseek( fp_student, rec_off, SEEK_SET ); 
			fread( &rec_siz, sizeof( int ), 1, fp_student ); 
			buf = new char( rec_siz + 1 ); 
			fread( buf, 1, rec_siz, fp_student ); 
			buf[ rec_siz ] = '\0'; 
		
		// entry must be created in the index 
		*indexend++;
		index_list[*indexend].key=key;
		index_list[*indexend].off=rec_off;
	}

	
}

int del()
{
	return 0;
}

int find()
{// adding a function
	return 0;
}

int main(int argc, char *argv[])
{
	index_S dummy;// variable to load the data from file to the sturct
	avail_S dummy2;
	int fit_type;
	char *buf;
	string command ="Not END";
	//long rec_off;
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
			//fp_student = fopen( "student.db", "w+b" ); 
		} 
		else 
		{ 
			/*rec_off = 0; 
			fseek( fp_student, rec_off, SEEK_SET ); 
			fread( &rec_siz, sizeof( int ), 1, fp_student ); 
			buf = new char( rec_siz + 1 ); 
			fread( buf, 1, rec_siz, fp_student ); 
			buf[ rec_siz ] = '\0'; 
			// reading the input from the file index to the array of structs index */
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
	
	if (strcmp(argv[1],"--best-fit")==0)
	{
		fit_type=0;
	}
	if (strcmp(argv[1],"--first-fit")==0)
	{
		fit_type=1;
	}
	if (strcmp(argv[1],"--worst-fit")==0)
	{
		fit_type=2;
	}
	getline(cin,command); //reads command from the user

	
	while(command.compare("end"))
	{
		
		string space=" ";
		size_t begin=0;
		
		size_t pos=command.find(space);
		begin = pos+1;
		string id=command.substr(begin,command.find(" ",begin));
		long key=atoi(id.c_str());
		cout <<"key is"<< key<<endl;
		if (command.find("add")==0)
			add(fp_student,index_list,key,&indexend,fit_type);
		else if (command.find("find")==0)
			find();
		else if(command.find("del")==0)
			del();
		else 
			cout << "Command not found" << "\n" << "Please enter a valid command";
		getline(cin,command); //reads command from the user
	}
	// fp_index=fopen("index","r+b"); //writing the index file back to the disc
	// for (int i=0; i < indexend; i++)
	// {
	// 	dummy=index_list[i];
	// 	fwrite(&dummy,sizeof(index_S),1,fp_index);
	// 	i++;
	// }
	// fclose(fp_index);

	// fp_avail=fopen("availability","r+b"); // writing the availibility file back to the disc
	// for (int i=0; i < availend; i++)
	// {
	// 	dummy2=avail_list[i];
	// 	fwrite(&dummy2,sizeof(avail_S),1,fp_avail);
	// 	i++;
	// }
	// fclose(fp_avail);	
}
