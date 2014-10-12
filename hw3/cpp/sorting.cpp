/*

  sorting.cpp

  Please refer to sorting.h for documentation on each function.

  Your Name: Dawson Botsford
  
  Your TA:   Xin 
   
  List O' Collaborators:
		Bob
		Bryan Newsom
		Alec
		Fletcher Richman
  
  List O' websites which helped: 

	http://realityisimportant.blogspot.com/2010/10/bubblesort-single-dimension-array.html
	http://www.cplusplus.com/reference/vector/vector/
	http://www.dreamincode.net/forums/topic/33631-c-vector-tutorial/
	http://www.cplusplus.com/reference/vector/vector/empty/
	http://en.wikipedia.org/wiki/Quicksort
	http://en.wikipedia.org/wiki/Merge_sort

 */

#include "sorting.h"
//#include <iostream>
#include <math.h>

using namespace std;

//user made function helpers:
void contents(vector<int> &data);
void swap(vector<int> &data, int pivot, int high);


void quicksort(vector<int> &data, int low_idx, int high_idx) {
	if (low_idx < high_idx){ 
	
	
	//cout << "   Contents: "; contents(data) ;
	//cout << endl;
	
	
	int pivot_index = ((high_idx+low_idx)/2);
	//swap(data, pivot_index, high_idx);
	
	
	//cout << "pivot_index: " << pivot_index << endl;
	
	pivot_index = quicksort_partition(data, low_idx, high_idx, pivot_index);
	
	//cout << "pivot_index: " << pivot_index << endl;
	quicksort(data, low_idx, pivot_index - 1);
	
	//cout << "entering right side" << endl;
	quicksort(data, pivot_index + 1, high_idx);
	//
	}
//cout << "   Contents: "; contents(data) ;
//	cout << endl;
	
}


int quicksort_partition(vector<int> &data, int low_idx, int high_idx,
			int pivot_index) {
	
	//swap pivot and last
	swap(data, pivot_index, high_idx);
	pivot_index = low_idx;
	
	int i = low_idx;
	
	while (i < high_idx){
	
		if (data[i] < data[high_idx]){
		
			//swap(data, data[i], data[pivot_index]);
			swap(data, i, pivot_index);
			++pivot_index;
		
		}
		
		++i;
	}
				
	swap(data, pivot_index, high_idx);			
	return pivot_index;			

}


void bubblesort(vector<int> &data) {
	
	bool finished = false;
	int temp;//value stored temporarily to help switch values later on
	
	while (!finished){
		
		finished = true;
		
		for ( int index = 0; index < data.size()-1; ++index){
			
			
			if (data[index] > data[index + 1]){
				
				//cout << "Swapping " << data[index] << " and " << data[index + 1] << endl;
				temp = data[index];
				data[index] = data[index + 1];
				data[index + 1] = temp;
				
				finished = false;
			
			}
		
		}
	}
}


void mergesort(vector<int> &data) {
	
  //no multiples to split
  if (data.size() <= 1) return;
    
  //element we will compare each side to  
  int middle = floor((data.size()/2.0));
  
  
  //declare vectors
  vector<int> left;
  vector<int> right;
  
  //split data into left and right with middle going to right
  for (int i = 0; i < (data.size()); ++i){
	  
	  if (i < middle) left.push_back(data[i]);
	  else right.push_back(data[i]);
	  
  }
  
  //keep splitting until the vector length is 1
  if (left.size() > 1) mergesort( left );
  if (right.size() > 1) mergesort( right );
  
  //merge these two sides
  data = merge(left, right);  

}

//sort the two inputs into the return vector
//we input left and right by reference to avoid wasting memory in making
//another copy. Although the & does not help with the function in any
//way, it assists in the memory usage by avoiding making a copy of each
vector<int> merge(vector<int> &left, vector<int> &right) {
	
	vector<int> to_return;
	
	//while there is still something in either left or right vector
	while (left.size() > 0 || right.size() > 0){
		
		//when both left and right have values we need to do some comparisons
		if ((left.size() > 0) && (right.size() > 0)){
			
			if (left[0] <= right[0]){//put into left
				
				to_return.push_back(left[0]);
				left.erase(left.begin());				
				
			}	
			else {//put into right
				
					to_return.push_back(right[0]);
					right.erase(right.begin());
				
				}	
			
		}//right vector is empty (put into left)
		else if ( left.size() > 0 ){
				
				to_return.push_back(left[0]);
				left.erase(left.begin());				
		}//left vector is empty (put into right)
		else if ( right.size() > 0){
			
				to_return.push_back(right[0]);
				right.erase(right.begin());
			
		}
			
	}	
	return to_return;

}



//I CHOSE SELECTION SORT!
void mystery_sort(vector<int> &data) {
	
	if (data.empty())
			return;
		
	int min;//minimum value in the data set after the first set of already organized values	
		
	for (int starting_index = 0; starting_index < data.size(); ++starting_index){
		
		min = starting_index;//the lowest value in the unordered portion of the set
							 //is the starting index
							 
		for (int compare_to = starting_index; compare_to < data.size(); ++compare_to){
			
			if (data[compare_to] <= data[min])
				min = compare_to;//the index of the lowest value in the set
						
		}		
		
		//switch the first value of the unordered portion of data with the lowest in all of data
		int temp = data[starting_index];
		data[starting_index] = data[min];
		data[min] = temp;
		//cout << "First value after changes: " << data[starting_index] << endl << endl;

	}	
	
}


//exchange pivot and high
void swap(vector<int> &data, int pivot_index, int high_idx){
	
	//switch pivot and high			
	int temp;
	temp = data[pivot_index];
	data[pivot_index] = data[high_idx];
	data[high_idx] = temp;

}

