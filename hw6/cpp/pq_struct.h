// 
// pq_struct.h
// 
// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
//
// You will turn in this file and pq.cpp to retrograde.
//
// Your Name: Dawson Botsford
using namespace std;
#include <string>

#ifndef pq_struct_h
#define pq_struct_h

struct pq {

	float priority;
	string data;	
	pq* next; //a pointer to the next element in the list
	pq* prev; //a pointer to the last element in the list
};

#endif
