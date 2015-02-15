#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// struture to hold index 
typedef struct 
{ 
	int key; /* Record's key */ 
	long off; /* Record's offset in file */ 
} index_S; 
vector<index_S> prim; /* Primary key index */ 

// structure to hold availability list
typedef struct 
{ 
	int size; /* Hole's size */ 
	long off; /* Hole's offset in file */ 
} avail_S;
vector<avail_S> avail_list; /* availability list containing the size */ 

main()
{
	index_S dummy;
	avail_S dummy2;
	FILE *out; /* Output file stream */ 
	if (( out = fopen( "index", "r+b" ) ) == NULL)
	{
		out = fopen( "index", "w+b" );
	}
	else
	{
		while(!feof(out))
	 	{
	 		fread(&dummy,sizeof(index_S),1,out);
	 		prim.push_back(dummy);
	 	}
		 
	}
	fclose(out);
	// Reading the input from availability list to the vector
	if (( out = fopen( "availabilitylist", "r+b" ) ) == NULL)
	{
		out = fopen( "availabilitylist", "w+b" );
	}
	else
	{
		while(!feof(out))
	 	{
	 		fread(&dummy2,sizeof(avail_S),1,out);
	 		avail_list.push_back(dummy2);
	 	}
		 
	}
	fclose(out);
	
}
