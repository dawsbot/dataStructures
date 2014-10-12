//  
//  Author: Dawson Botsford
//	Assignment: CS2270  Gabe Johnson HW2 binary tree
//  Date: 1/29/2013
//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//
// Peeps collaborated with: Bryan Newsom, David Aleman, Pieter Bork, Bob.
//
// Websites used:
// http://en.wikipedia.org/wiki/Binary_search_tree
// http://math.hws.edu/orr/s04/cpsc225/btrees/index.html
//

#include <iostream>
#include <vector>
#include "binary_search_tree.h"
using namespace std;

//declare and intiailize a new node
bt_node* init_node(int data) {
	
	//initialize new bt_node pointer
	bt_node* cursor = new bt_node;
	
	//set it's pointers
	cursor->left = NULL;
	cursor->right = NULL;
	cursor->data = data;
	
	return cursor;
}


//insert an already intiialized and declared node into a tree
void insert(bt_node** top_ref, bt_node* new_node) {
	
		//special case empty tree
	if (*top_ref == NULL)  {
		
		*top_ref = new_node;
		return;
		
		}
		
	//pointer to the start of the tree
	bt_node* head = *top_ref;	
	
	if (new_node->data < head->data){//go left
		if (head->left == NULL) {//stopping condition
			
			head->left = new_node;
			return;
		}
			
		insert( &head->left, new_node );
		
	}
	
	else { //new_node->data >= head->data
	//go right
		if (head->right == NULL) {//stopping condition
			
			head->right = new_node;
			return;
			
		}
		
		insert( &head->right, new_node);
	

	}
}



//Inserts a new node with int data as the data value
void insert_data(bt_node** top_ref, int data) {
 
	bt_node* new_node = init_node(data);
	insert(top_ref, new_node);
  
}




void remove(bt_node** top_ref, int data) {
	
	//item not in tree
	if (*top_ref == NULL) return;
	
	bt_node* top = *top_ref;
	
	//recurse left
	if (data < (*top_ref)->data) {
		
		remove(&((*top_ref)->left), data);
	
	}

	//recurse right
	else if (data > (*top_ref)->data) {
		
		remove(&((*top_ref)->right), data);
	
	}



	else //data = top->data
	{
		bt_node* temp = new bt_node;
		if ((*top_ref)->left == NULL){//if there is only one child or none
			
			temp = (*top_ref)->right;
			*top_ref = temp;
		
		}
		else if ((*top_ref)->right == NULL){
			
			temp = (*top_ref)->left;
			*top_ref = temp;
			
			
		}
		else {//2 children
			
			//algorith to remove and replace with successor (not predecessor)
			temp = top->right;
			bt_node* parent = new bt_node;
			
			while(temp->left != NULL){
				
					parent = temp;
					temp = temp->left;
				
			}
			
			top->data = temp->data;
			if (parent != NULL) remove (&parent->left, parent->left->data);
			else remove(&top->right, top->right->data);
			
			
		}
	
		
	}
		
}



//returns a boolean of whether the 'data' is found as the value in a node of the tree
bool contains(bt_node* top, int data) {
	
	//empty tree
	if (top == NULL) return false;
	
	if (top->data == data) return true;
	
	//check left of top
	if (data < top->data) {
		
		if (top->left == NULL) return false;//no left child
		contains(top->left, data);
		}
	
	else{//data > top->data
		
		if (top->right == NULL) return false;//no right child
		contains(top->right, data);
		}


}



bt_node* get_node(bt_node* top, int data) {
  
  bt_node* cursor = top;
  
  //empty tree
	if (cursor == NULL) return NULL;
	
	//the top of this tree is the data val we want
	if (cursor->data == data) return cursor;
	
	//check left of top
	if (data < cursor->data) {
		
		if (cursor->left == NULL) return NULL;//no left child
		get_node(cursor->left, data);
		}
	
	else{//data > top->data
		
		if (cursor->right == NULL) return NULL;//no right child
		get_node(cursor->right, data);
		}

}



int size(bt_node* top) {
	
	bt_node* cursor = top;
	
	//if the head is not null count everything below then recurse to both of it's children
	if (cursor != NULL) return 1 + size(cursor->left) + size(cursor->right);
	return 0;//if head is null
}


void array_assist(bt_node* top, int arr[], int* array_a){
	
	bt_node* cursor = top;
	if (cursor == NULL)return;
	else{
		array_assist(cursor->left, arr, array_a);
		arr[*array_a] = cursor->data;
		(*array_a)++;
		array_assist(cursor->right, arr, array_a);
		
	}	
	
}


void to_array(bt_node* top, int arr[]) {
	
		int array_a = 0;
		array_assist(top, arr, &array_a);
	
}
