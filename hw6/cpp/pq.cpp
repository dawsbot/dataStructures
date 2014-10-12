//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Name: Dawson Botsford
#include <iostream>
#include <string>
#include "pq.h"

/**
 * Initialize an empty priority queue.
 *
 * This is needed for unit testing. I'll do something like this:
 *
 *   pq* queue = init_priority_queue();
 *   string text = "Speaker of the House";
 *   insert(queue,  text, 7.9);
 *   text = "President";
 *   insert(queue, text, 10.0);
 *   text = "Congressional Staffer";
 *   insert(queue, text, 2.0);
 *   cout << remove(queue) << endl; // President
 *   cout << remove(queue) << endl; // Speaker of the House
 *   cout << remove(queue) << endl; // Congressional Staffer
 *
 **/


//=========== init_priority_queue() ============
//Initialize a new queue
pq* init_priority_queue() {

	pq* cursor = new pq;
	cursor->data;
	cursor->priority = NULL; 
	cursor->next = NULL;
	cursor->prev = NULL;

	return cursor;
}

/**
 * Insert the given text information into the queue with the specified
 * priority.
 *
 * Larger priority values have precedence. So if I add "foo" at
 * priority 5.0 and "bar" at priority 5.1, "bar" will be removed
 * before "foo".
 *
 * Priority values may be negative, zero, or positive
 *
 * Higher priorities are at the end of the list
 *
 *
**/

void insert(pq* &queue, string &text, float priority) {

pq* new_node = init_priority_queue(); 
new_node->data = text;
new_node->priority = priority;


//Special Case
//Empty List
if (queue->priority == NULL){
	
	queue = new_node;
	return;	

}


//Special Case
//inserting at the beginning of the list
if (priority < queue->priority){
	
	//fix the pointers so that the new_node is first in the list	
	new_node->next = queue;		
	queue->prev = new_node;
	//new_node->data = text;
	//new_node->priority = priority;
	
	queue = new_node;//now set queue to point to new_node	
	return;

}


pq* cursor = queue;
//cout << "!!!!!!!! cursor->data    " << cursor->data << endl;
//Special Case
//inserting at the end of the list
//iterate until we are pointing to the last element
while (cursor->next != NULL)
	cursor = cursor->next;

//cout << "


if (cursor->priority <= priority){

//	cout << "INPUT PRIORITY IS GREATEST! FIX THE LIST" << endl;
	cursor->next = new_node;
	new_node->prev = cursor; 

	return;
}


//fix cursor to point to beginning of queue
//for insert3
cursor = queue;

while (priority > cursor->priority)
	cursor = cursor->next;	
//cout << "queue->prev->next->data:  " << queue->prev->next->data << endl;
//cout << "on line 8 of insert!" << endl;


cursor->prev->next = new_node;
new_node->prev = cursor->prev;
new_node->next = cursor;
cursor->prev = new_node;


}






/*
**
 * Remove the highest priority element from the queue and return it.
 */
string remove(pq* &passed_in) {


	string to_return;

	//Special Case of an empty list
	if (passed_in->next == NULL){

		to_return = passed_in->data;
		passed_in = init_priority_queue(); 
		return to_return;

	}


	pq* queue = passed_in; 

	//iterate until we are at the last element
	while (queue->next != NULL)
		queue = queue->next;
	
	to_return = queue->data;
	queue->prev->next = NULL;	

	return to_return; 

}





/**
 * Return the highest priority element in the queue but do not alter
 * the queue's membership.
 **/
string peek(pq* &passed_in) {
 
	pq* queue = passed_in;	
	//increment until the element points to NULL, which only happens for the last element
	while (queue->next != NULL)
		queue = queue->next; 

return queue->data;

}
