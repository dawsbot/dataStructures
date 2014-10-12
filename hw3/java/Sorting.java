/*
 * Sorting.java
 *
 * Your Name: Dawson Botsford	
 * Your TA: Xin
 * Your Collaborators:  Dr. Johnson
 * 						Peyman
 */

import java.util.List;
import java.util.ArrayList;


public class Sorting implements SortingIntf {


	private List<Integer> data = null;
	
	
    public void bubblesort(List<Integer> data) {
		
		boolean finished = false;
		int temp;
		
		while (!finished){
			
				finished = true;
				
				for (int index = 0; index < (data.size() - 1); ++index){
					
					if (data.get(index + 1) < data.get(index)){
						
						//user created method: switches index and index + 1
						swap(data, index, index + 1);				
						finished = false;
						
					}
					
				}
			
		}		
		
    }
    
    
    
    public void quicksort(List<Integer> data, int low_idx, int high_idx) {

    }

    public int quicksort_partition(List<Integer> data, int low_idx, int high_idx, 
			     int pivot_index) {
	return -1;

    }

    public void mergesort(List<Integer> baddata) {

		if (data.size() <= 1) return;
		
		int middle = data.size() / 2;
		
		List<Integer> left;
		List<Integer> right;
		
		System.out.println("SUBLIST: " + data.subList(0, middle ));
		left = data.subList(0, middle );
		right = data.subList(middle, data.size() );
		
		
		if (left.size() > 1) mergesort(left);
		if (right.size() > 1) mergesort(right);
		
		System.out.println("\nData: " + data);
		//data = merge(left, right);
	while (merge
    }

    public List<Integer> merge(List<Integer> left, List<Integer> right) {
		
		List<Integer> toReturn = null;
		
		//while there is still something to do
		while (!left.isEmpty() || !right.isEmpty()){
			
			//requires logic left and right has stuff
			if (!left.isEmpty() && !right.isEmpty()){
				
				if (left.get(0) < right.get(0)){
					
					toReturn.add(left.get(0));
					left.remove(0);
				}
				
				else {
					toReturn.add(right.get(0));
					right.remove(0);
				}
			}
			else if (right.isEmpty()){
				
				toReturn.add(left.get(0));
				left.remove(0);
			}
			else if (left.isEmpty()){
				
				toReturn.add(right.get(0));
				right.remove(0);
				
			}
				
		}
	return toReturn;		
				
	}
		

	//SELECTION SORT!
    public void mystery_sort(List<Integer> data) {
		
		if (data.size() == 0) return;
		
		//default min value is at index 0 incase this is the smallest
		int min;// = data.get(0);
		
		//iterate through the data while incrementing the start_index
		for (int start_index = 0; start_index < data.size(); ++start_index){
		
			min = start_index;
		
			//iterate through everything and pull out the minimum
			for (int compare_to = start_index;  compare_to < data.size(); ++compare_to){
			
				//set minimum 
				if (data.get(compare_to) < data.get(min)){
				
					min = compare_to;
				
				}
			
			}
		
			swap (data, start_index, min);
			
		}

    }


	//USER CREATED METHOD
	//switches the values in 'data' at index 'first 'and index 'second'
	public void swap(List<Integer> data, int first,int second){
		
		int temp = data.get(first);
		data.set(first, data.get(second));
		data.set(second, temp);
		
	}
}
