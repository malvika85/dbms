#ifndef DB_FILE_H
#define DB-FILE_H

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "Defs.h"


// Enum for file types
enum fileType
{
	heap 0,
	sorted,
	tree
};

typedef enum fileType fType;

class DBFile
{
	private:
		FILE * p_currPtr;		

	public:
		DBFile();
		~DBFile();
	
		// Forces the pointer to correspond to the first record in the file
		void MoveFirst();

		// Add new record to the end of the file
		// Note: addMe is consumed by this function and cannot be used again
		void Add (Record &addMe) 

		// Fetch next record (relative to p_currPtr) into fetchMe
		int GetNext (Record &fetchMe);

		// Applies CNF and then fetches the next record
		int GetNext (Record &fetchMe, CNF &applyMe, Record &literal); 
		
		// name = location of the file
		// fType = heap, sorted, tree
		// return value: 1 on success, 0 on failure
		int Create (char *name, fType myType, void *startup); 

		// This function assumes that the DBFile already exists
		// and has previously been created and then closed.
		int Open (char *name); 

		// Closes the file. 
		// The return value is a 1 on success and a zero on failure
		int Close (); 

		// Bulk loads the DBFile instance from a text file, 
		// appending new data to it using the SuckNextRecord function from Record.h
		// loadMe is the name of the data file to bulk load. 
		void Load (Schema &mySchema, char *loadMe);

};

#endif

