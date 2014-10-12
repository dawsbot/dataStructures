//Author: Dawson Botsford
#include <iostream>
#include "btree.h"
#include "dawson.h"
#include <math.h>
using namespace std;

// Note that the keys and children arrays are OVERSIZED to allow for
// some approaches to work, where nodes are allowed to temporarily
// have too many keys or children. 
// 
// A valid btree node can have at most:
//   BTREE_ORDER-1 keys.
//   BTREE_ORDER children.


 int belonging_child(btree* &root, int key);
 btree* split(btree* tree);
 btree* init_tree();
 int get_median(btree* tree);
 bool is_full(btree* tree);
 void print_array_contents(int arr[]);
 btree* build_node(int size, int* keys);
 //btree* init_node();
//btree* parent;


//================== init_tree =================
// When a new node needs to be created, we call this. 

btree* init_tree(){

	btree* cursor = new btree;

	cursor->num_keys = 0;
	cursor->keys[BTREE_ORDER];
	cursor->children[BTREE_ORDER + 1];
	for (int i = 0; i < BTREE_ORDER; ++i){

		cursor->children[i] = NULL;

	}
	cursor->is_leaf = true;

	return cursor;

}



//================ get_median ===================
//returns the median value of the array
int get_median( btree* tree ){

//	cout << "median: " << tree->num_keys / 2.0  << endl;
	int med =  tree->num_keys / 2.0 ;

//cout << "arr[med]: " << tree->keys[med] << endl;
//	cout << "arr[med]: " << tree->keys[med] << endl;

	return tree->keys[med];
} 







// ============= is_full ==========================
// returns a bool if the node's keys is full
bool is_full( btree* tree ){

	cout << "Array size: " << tree->num_keys << endl;
	return tree->num_keys >= BTREE_ORDER - 1;

}





// ------------- P U T _ I N --------------
// When a value needs to be inserted into a node, 
// we call this. It finds the correct location and puts it in.
btree* put_in(btree* &root, int key ){
	
	btree* cursor = root;  //create copy for easier manipulation

	//int length = get_array_size(cursor->keys);  //The amount of non-null entries
	int length = cursor->num_keys;

	//Special Case: if the node is initially empty
	if ( length == 0){

		cursor->keys[0] = key;//add the new value to the end
		
		++cursor->num_keys;
	}
	else{//The node has keys

		//cout << "cursor->keys[5]: " << cursor->keys[5] << endl;
		int i = 0;//used as index

		//Iterate until i is the index where key belongs
		while ( cursor->keys[i] < key && i < length) 
			++i;
	
		//shift everything after index i one index further	
		for (int p = length; p > i; --p){	

			cursor->keys[p] = cursor->keys[p-1];
		}

		cursor->keys[i] = key;//place key into the index where it belongs
		++cursor->num_keys;

	}

	return cursor;

}





//================= split =====================
//take the current node and split it into two
//the new root is empty
btree* split(btree* cursor, btree* parent){

	//initialize the new root and two of it's children
//	btree* head = init_tree(); 
	btree* child1 = init_tree();
	btree* child2 = init_tree();

	//fill the two children with the > and < of the median	
	for (int i = 0; i < BTREE_ORDER/2; ++i){
		
		put_in( child1, cursor->keys[i] );	
		put_in( child2, cursor->keys[i + 1 + (BTREE_ORDER/2)]);

	}	
	
	//if the cursor is a leaf, it's children are just our two new children
	if (cursor->is_leaf){
	
	//	head->children[0] = child1;
	//	head->children[1] = child2;
	//	return head;

	}

//	cout << "\nIN SPLIT: " << endl;
//	print_array_contents(head->keys);	
}






//=================== print array contents=======
//give friendly little output to see the values in
//the given array. Beware, there is still random
//number junk inside the node after num_keys
void print_array_contents(int arr[]){
cout << "[ ";
// for (int i = 0; arr[i] != NULL; ++i){
//cout << arr[i] << ", ";       

for (int i = 0; i < BTREE_ORDER; ++i){

	cout << arr[i] << ", "; 
}
cout << " ] " << endl;
 
}







// -------------------------------------------- I N S E R T ---------
//
// Insert the given key into a b-tree rooted at 'root'.  If the key is
// already contained in the btree this should do nothing.  
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void insert(btree* &root, int key){

	//parent->is_leaf = false;
	//cout << "\n\n\n this should say 1: " << root->is_leaf << endl;

	//the key is already found in the tree
	if (contains(root, key)){
		cout << "ERROR THE TREE ALREADY CONTAINS THIS KEY!" << endl;
		return;
	}

	btree* mytree = root;  //create a copy of the root
	btree* parent = init_tree();
	if (root->is_leaf){
		
		//the current node is full, so we need to split it 
		if (is_full(mytree)){
		
//			cout << "INSIDE THE IF!" << endl;	
			put_in( mytree, key );  //insert key where it belongs in the cursor node
			int median = get_median(mytree);
	
			//btree* new_node = split(mytree);	
//			cout << "Calling split!" << endl;	
			root = split(mytree, parent);

			//print_array_contents(root->keys);
			put_in( root, median );
		
			//put_in( mytree, key );  //insert key where it belongs in the cursor node
			root->is_leaf = false;	
		}
		
		else{ 
			put_in( mytree, key );  //insert key where it belongs in the cursor node
		}
	}


	//node is not a leaf	
	else{

		btree* parent = root;
		insert(mytree->children[belonging_child(mytree, key)], key);

//		contains(cursor->children[belonging_child(cursor, key)], key);

	}
	
}








// -------------------------------------------- R E M O V E --------- //
// Remove the given key from a b-tree rooted at 'root'. If the key is
// not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void remove(btree* &root, int key){

//	cout << "Inside remove!" << endl;

	//create a copy of the root node for easier manipulation
	btree* cursor = root;
	
	if (!contains(cursor, key)){
		cout << "ERROR Cannot remove this key because it is not contained in the tree" << endl;
		return;	
	}
	//cout << "Is this cursor a leaf? " << cursor->is_leaf << endl;	
	if (cursor->is_leaf){
//		cout << "cursor is a leaf!" << endl;	
		int i = 0;
		while (cursor->keys[i] < key){

			++i;
	
		}	
//		cout << "About to change what's at the " << i << "th location" << endl;
		cursor->keys[i] = NULL;

		for (int p = i; i < cursor->num_keys; ++i){

			cursor->keys[i] = cursor->keys[i + 1];

		}
		cursor->keys[ cursor->num_keys ] = NULL;
		--cursor->num_keys;	
	}
	//node is not a leaf
	else{
			
		remove(cursor->children[belonging_child( root, key)], key);


	}


}






// ----------------------------------------- C O N T A I N S --------
//
// Return true if any node accessed from the given root node contains
// the provided key value.
bool contains(btree* &root, int key){

	if (root == NULL){
		cout << "ROOT IS NULL (IN CONTAINS)" << endl;
		return false;
}

	btree* cursor = root;
	//print_array_contents(cursor->keys);	

	//iterate through the current root to check if key exists
	for ( int i = 0; i < cursor->num_keys; ++i ){

		if (cursor->keys[i] == key) return true;
//		cout << "VALUE AT CURSOR->KEYS[I]: " << cursor->keys[i] << endl;
	}
	
	//it has no children and key was not in root
	if (cursor->is_leaf){
//		cout << "CURSOR IS A LEAF  RETURNING FALSE (IN CONTAINS)" << endl;
		 return false;
	}
	//recursively call contains again with the child node that
	//the key would belong to (if it exists)
	cout << "\ncalling contains" << endl;	
	contains(cursor->children[belonging_child(cursor, key)], key);



}



//================ belonging_child ===========
//returns the index of where that child would belong (if it exists)
//assumes that root is not a leaf
int belonging_child(btree* &root, int key){

	btree* cursor = root;

	//check far left child
	if (key < cursor->keys[0])
		return 0;
		
	//check far right child
	if (key > cursor->keys[cursor->num_keys - 1]){

		return cursor->num_keys;		
}

	//now we check the stuff that's not on either edge
	int index = 1;
	//increment index until it is at the index of the child where the key would be
	while (key > root->keys[index]){
		++index;

}

	return index;
}


