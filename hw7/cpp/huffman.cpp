/*
 * huffman.cpp
 *
 * Your Name: Dawson Botsford
 * Your Collaborators: Bob, Lane, my TA, the guy with the curly har
 * 		       who sat with me during help hours on Tuesday
 *		       morning.
 *
 * This implementation file contains some functions that are fully
 * built. Others are empty. Some empty ones are optional, others are
 * not.
 *
 * Consider implementing this by iteratively getting manual_driver()
 * to work. The steps are spelled out for you.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#include <cctype>
#include "huffman.h"

using namespace std;

void encode_helper(freq_info*& huffman_root, string &current_char, map<char, string> &ret);

void manual_driver () {

  /*  1. Create a priority queue of one-node trees using some big text
      file. This gives you a priority queue containing freq_info
      objects. These are meant to be used as nodes in a tree. At the
      moment, they are all disconnected, so you have a forest of tiny
      one-node seedlings. 
  */
  tree_queue queue = read_corpus("pkd.txt");

  /*  2. Now do something like the following:
      
      while priority queue has more than one item: 
      
        Pop top two items, A and B. They are lowest frequency nodes.
        Create non-leaf node C who points to children A and B. C's
        frequency is the sum of A and B's frequency.  Insert C back
        into the priority queue. We are left with a single node in the
        priority queue. This is the root node of our huffman encoding
        tree. Retain a reference to that root node.
   */
  freq_info* huffman_root = build_huffman_tree(queue);
  // if you want to show debugging info of a huffman tree, uncomment:
  //  int level = 0;
  //  debug_tree(huffman_root, level);
  

  /*  3. The leaf layer of the huffman tree contains symbols. The path
      from root to a leaf is the huffman encoding for that leaf's
      symbol. Every time a left child is followed, that corresponds to
      a zero bit; right children are one bits.

      Traverse the tree and create a bitstring for each leaf. If the
      path from the root to the leaf happens to be Left Left Right
      Left, the bitstring for that leaf is 0010. Store these
      bitstrings in a map. The resulting map use symbols for keys and
      strings that use LEFT_CHAR for 0 and RIGHT_CHAR for 1
      (right). By default these are '.' and '^' respectively:

      key   bitstring
      ---------------
       a     .^.^
       b     ..^.^
       z     ^^.^..^
       #     .^^....^
       e     ^^.

       Notice that 'e' uses three bits while '#' uses 8. Think about
       why this is awesome.
   */
  map<char, string> encoding_map = build_encoding_map(huffman_root);
  // uncomment this if you want to show debugging info of your map.
  // debug_encoding_map(encoding_map);
  
  /*  4. Now that we have a Map of symbols to bitstrings, we can use
      it to encode text data. I'll give little sentences to encode.
      For the output, we're using strings rather than actual bits so
      (a) we can read and debug it more easily, and (b) so we don't
      have to deal with chopping up individual bytes in memory (which
      isn't the point of the exercise).
   */
  string short_string = "And no one sings me lullabyes...";
  string medium_string = "We don't need no education.\nWe don't need no thought control.\nNo dark sarcasm in the classroom.\nTeacher leave those kids alone!\n";
  string long_string = "The lunatic is on the grass.\nThe lunatic is on the grass.\nRemembering games and daisy chains and laughs.\nGot to keep the loonies on the path.\n\nThe lunatic is in the hall.\nThe lunatics are in my hall.\nThe paper holds their folded faces to the floor\nAnd every day the paper boy brings more.\n\nAnd if the dam breaks open many years too soon\nAnd if there is no room upon the hill\nAnd if your head explodes with dark forebodings too\nI'll see you on the dark side of the moon.\n\nThe lunatic is in my head.\nThe lunatic is in my head\nYou raise the blade, you make the change\nYou re-arrange me 'til I'm sane.\nYou lock the door\nAnd throw away the key\nThere's someone in my head but it's not me.\n\nAnd if the cloud bursts, thunder in your ear\nYou shout and no one seems to hear.\nAnd if the band you're in starts playing different tunes\nI'll see you on the dark side of the moon.";

  string short_encoded = encode(short_string, encoding_map);
  string medium_encoded = encode(medium_string, encoding_map);
  string long_encoded = encode(long_string, encoding_map);

  /*  5.  After encoding some strings into your huffman coded 'bit'
      string, you can use the decode function to get back the
      original. The way you do this is to read the input character by
      character, starting from the root of your huffman tree. When you
      see LEFT_CHAR, you move left; a RIGHT_CHAR, move right. When you
      reach a leaf node, you have found the coded character. Record
      that character. Move back to the root and continue reading the
      input string until it is complete. The sequence you read should
      be the original message.
   */

  string redone_short = decode(short_encoded, huffman_root);
  string redone_medium = decode(medium_encoded, huffman_root);
  string redone_long = decode(long_encoded, huffman_root);

  // consider using do_encoding_test (a function defined later on) to
  // see if these things are working properly.
}

void debug_queue(tree_queue &queue) {
  cout << "Debugging queue..." << endl;
}

void debug_tree(freq_info*& node, int& level) {
  cout << "Debugging tree..." << endl;
}

void debug_encoding_map(map<char, string>& huffman_map) {
  cout << "Debugging encoding map..." << endl;
}


//=============== init_freq_info_supernode ============================================
//Create a new node which points to and sums the frequency of a left and right child
freq_info* init_freq_info_supernode(freq_info* left, freq_info* right) {
 
 freq_info* ret = new freq_info;
  // implement me. set the value's members to the proper values. be sure
  // to set the is_leaf member correctly.
 
 ret->left = left;
 ret->right = right;
 ret->is_leaf = false;
 ret->freq = left->freq + right->freq;
 return ret;

}



//=============== build_huffman_tree ============================================
//
freq_info* build_huffman_tree(tree_queue &queue) {
 
//initialize nodes	
 freq_info* root = NULL;
 freq_info* left_node;
 freq_info* right_node;

//while there is more to put into a supernode
 while (queue.size() > 1){
	
	//store left and right nodes and remove from priority queue
	left_node = queue.top();	
	queue.pop();

	right_node = queue.top();
	queue.pop();	

	//create supernode with children of left and right	
	root = init_freq_info_supernode( left_node, right_node );	

	//insert that supernode back into queue	
	queue.push(root);
}

  return root;


}



//========================== build_encoding_map ====================
//build a map which has the keys as the letter of the user inputted 
//string and the values associated as the . ^ combination to 
//reach that leaf in the tree
map<char, string> build_encoding_map(freq_info*& huffman_root) {

  map<char, string> ret;//initialize new encoding map

  string current_char = "";
  encode_helper(huffman_root, current_char, ret);//fills ret with the codes

  return ret;

}


//=============================== encode_helper ============================================
//recursively calls itself to fill the encoding map with the . ^ combination
void encode_helper(freq_info*& node, string &bitstring, map<char, string> &ret){

	//set this key's value as the bitstring combination	
	if (node->is_leaf){

			ret[node->symbol] = bitstring;	

	}

	//the root has children
	//add more . ^ chars to the current bitstring
	else{	
		//go left recursively	
		bitstring.push_back('.');	
		encode_helper(node->left, bitstring, ret);
		bitstring.erase(bitstring.end() - 1);	
	
		//go right recursively
		//only is reached when there is no left node untracked 	
		bitstring.push_back('^');
		encode_helper(node->right, bitstring, ret);
		bitstring.erase(bitstring.end() - 1);	
	}


}




//======================================== encode =====================
//using the encoding map iterate through each character and convert from
//the char to the encoded . ^ combination
string encode(string& original, map<char, string>& encoding_map) {

  string result;//encoded version of input string 'original'

//iterate throught the string adding the code for each character in the
//string to the result
for ( int i = 0; i < original.size(); ++i){

	//append the code for each letter to result
	result += encoding_map[original[i]];

}

  return result;

}



//========================== decode ===========================
//take the . ^ combination and change it back into readable letters
string decode(string& encoded, freq_info*& huffman_root) {

 string result ;
 freq_info* node = huffman_root;

//while there is still more to decode in the . ^ string
while (encoded.size() > 0){

	while (!node->is_leaf){
		//recurse left
		if (encoded.front() == '.'){
			
			node = node->left;
			encoded.erase(encoded.begin());
		
		}
		//recurse right
		else {
			
			node = node->right;
			encoded.erase(encoded.begin());

		}
	}
	
	//add this char to the decoded string	
	result.push_back(node->symbol);
	node = huffman_root;

}

return result;

}



