#include <iostream>
#include "linked_list.h"

using namespace std;

int main () {



  cout << "Testing Linked List" << endl;
  node* empty_list = NULL; // empty list
  cout << "Empty List Contents: " << report(empty_list) << endl; // should be ''
  append_data(&empty_list, 16);
  cout << "Empty List Contents after appending 16: " 
       << report(empty_list) << endl; // should be '16'
       
  cout << "Size (should be 1): " << size(empty_list) << endl;


  // now lets make a proper list that we manipulate
  node* head = init_node(0);
  // append a number
  append_data(&head, 1);
  // append a few more
  
  append_data(&head, 2);
  append_data(&head, 3);
  // Now try appending nodes
  node* seven = init_node(4);
  node* ten = init_node(5);
  append(&head, seven);
  append(&head, ten);
 
  cout << "size of the list: " << size(head) << endl;	
	
	
	//node* fun = init_node(99999);
	insert_data(&head, 6, 99999);
	cout << "report (should say 0 1 2 3 4 5 99999): " << report(head) << endl;
	
	

}
