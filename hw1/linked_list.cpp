/*

	due friday at 6pm

  linked_list.cpp

  <document your work here: Functions to create and manipulate
  * a linked list in C++.>

 */

// AUTHOR: Dawson Botsford

// WHAT: CSCI 2270 Assignment 1

// COLLABORATORS: <List of EVERYBODY you worked with, including
// instructors, TAs, and other students. Include people you helped.>

// <List of EVERY WEB SITE you consulted substantially> 
// http://www.cplusplus.com/articles/D9j2Nwbp/
// http://www.eskimo.com/~scs/cclass/int/sx8.html
// http://www.daniweb.com/software-development/cpp/threads/99991/deleting-any-node-from-a-singly-linked-list#
// http://stackoverflow.com/questions/20731/in-c-how-do-you-clear-a-stringstream-variable
// http://stackoverflow.com/questions/6587222/initializing-nodes-in-a-list-from-a-txt-file
// http://stackoverflow.com/questions/3031971/im-new-to-c-please-help-me-with-the-linked-list-what-functions-to-add?rq=1


// include the header file that provides function prototypes and the
// node structure. When you turn in your assignment, the grading
// system will use its own copy of this file, so don't edit it, and
// implement all the functions it specifies.
#include "linked_list.h"

// sstream gives you the stringstream object. Google it, and admire
// how much easier this makes life.
#include <sstream>

using namespace std;


// your linked list implementation goes here |;)>


// creates a new node structure that points to NULL and holds the
// provided integer. return a pointer to that new node.
node* init_node(int data){
	
	node* new_node = new node;
	
	new_node->data = data; //gives the data of that node num
	new_node->next = NULL; //we need it to point to NULL
	
	return new_node;
	
}


// create a space-separated string representing the contents of the
// list, in the same order they are found beginning from the head of
// the list. return that string object.  For example, this might
// return "" (the empty string) if the list is empty, or it might
// return "1 7 3" or "1 7 3 " (note the space at the end, you can have
// that there and it is OK).
string report(node* list){
	//cout << "\nStart of report..." << endl;
	string returnval = ""; //blank returnable string
	
	node* cursor = list;
	stringstream convert;//initialize ss object
	
	
	while ( cursor != NULL ){//until the end of the list
		
		//convert the (int) data to a string and append to the empty string
		convert << cursor->data;    
		returnval += convert.str();
		convert.str(std::string());
		returnval.append(" ");//the space which goes between each data value
		
		cursor = cursor->next;//now let's do that again with the next data value
		
	}

return returnval;

}

// this is the same as append_data, except we're adding a node, rather
// than a value. 
void append( node** head, node* newNode ){
		
		//special case of an empty list
		if (*head == NULL){
			*head = newNode;
			
		}
		
		else 
			{
				node* cursor = *head;
			
				while (cursor->next != NULL){//until the end of the list
					
					cursor = cursor->next;
					
					}
				cursor->next = newNode;//attach the newNode to the end
			
			}
		
}

// insert an integer into the list pointed to by head. the resulting
// list is one element longer, and the newly appended node has the
// given data value. consider using the 'append' function to help.
void append_data(node** head, int data){
	
	node* new_node = init_node(data);//initialize new node with the data 'data'
	append(head, new_node);//let append do the heavy lifting
	
}


// similar to append_data. insert a new node that contains the given
// data value, such that the new node occupies the offset
// indicated. Any nodes that were already in the list at that offset
// and beyond are shifted down by one. For example if the list
// contains 23, 74, 93, and we insert 42 at index 1, the resulting
// list should be 23, 42, 74, 93.
void insert_data(node** head, int offset, int data){
	
	node* new_node = init_node(data);//create a new node with data 'data'
	insert(head, offset, new_node);//let append do the heavy lifting
	
	}





// this is the same as insert_data, except we're inserting a node,
// rather than a value.
void insert(node** parent, int offset, node* new_node){
	
	int num = size(*parent);
	
	//assure offset size is possible
	if ((offset > num) || (offset < 0)){
		
		cout << "ERROR: offset num invalid (either too small of too large)" << endl;
		return;
		}
		
	node* cursor = *parent;	
	
	//special case when user want to insert index 0
	if (offset == 0){
		
		cout << "offset == 0" << endl;
		new_node->next = *parent;
		*parent = new_node;
				
	}	
	
	
	
	else{
		 
		int index = 0; //used to figure out the node we want to remove
	
	//stop one sooner to make it easier to wire around
		while (index + 1 < offset){
		
			index++;
			cursor = cursor->next;
			}
		cout << "Do you want to insert after " << cursor->data << " ? " << endl;
		cout << "Val of cursor->next: " << cursor->next << endl;
		new_node->next = cursor->next;
		cursor->next = new_node;
			
		}
	}



// remove the node indicated by the given offset. For example if our
// list contains 23, 74, 93, and we remove offset 1, the resulting
// list should then contain 23, 93.
void remove(node** parent, int offset){
	
	int num = size(*parent);
	
	//assure offset size is possible 
	if ((offset >= num) || (offset < 0)){
		cout << "ERROR: offset num invalid (either too small of too large)" << endl;
		return;
	}
	
	node* cursor = *parent;
	
	//special case when user want to remove index 0
	if (offset == 0){
		
		*parent = cursor->next;
		delete(cursor);//to avoid a memory leak
		
	}	
	
	else{
		 
	int index = 0; //used to figure out the node we want to remove
	
	//stop one sooner to make it easier to wire around
	while (index + 1 < offset){
		
		index++;
		cursor = cursor->next;
	}
	
	node* node_to_remove = cursor->next;
	cursor->next = cursor->next->next;
	
	delete(node_to_remove);//to avoid a memory leak
	}
}


// report the number of nodes in the linked list pointed to by head.
int size(node* head){
	
	int count = 0;
	node* cursor = head;
	
	//iterate through while counting
	while ( cursor != NULL ){
		count += 1;
		cursor = cursor->next;
		}
		
	return count;
	
	}

// return true if the linked list pointed to by head contains a node
// with the specified value.
bool contains(node* head, int data){
	
	node* cursor = head;
	
	//continue until the end of the ll
	while (cursor != NULL){
		
		if (cursor->data == data) return true;
		else cursor = cursor->next;
	
	}
	return false;//only reached if cursor->data is never equal to data
	
	
	}
