/*===================================================================================

	AI CODE!
	Author: Dawson Botsford 
	Student ID: 102003505
		
	*I was the one who talked to you about splitting off from my group
	because I did not believe the project was big enough for a group of
	5 people. So here goes nothing solo-style! Thanks.

	Date: 4/22/2013 

	Purpose: Final Game project AI for CSCI-2270 with Gabe Johnson
				At CU Boulder Spring Semester 2013

	Description: This is the classic hangman game. One user enters
	the word which they would like their friend to be guessing and
	for the rest of the game the friend tries to guess one character
	at a time until he has won	


====================================================================================*/	


#ifndef HANGMAN_HPP_
#define HANGMAN_HPP_


#include <string>
#include <vector>
#include <map>


using namespace std;




//the class which contains the AI logic and processing. The AI iterates through a string called common_words
//and stores the letters in a map. Then another map ordered_map is created with the highest occurance first
// Then the AI guesses characters one by one based upon
//how popular they were in the list of most common words
class AI{
private:

public:

	AI();//class contructor	
	
	//member variables
	string common_words;//stores the 25 most popular words in the english language


	map<char,int> letters;//the map of the chars within the common_words string

	//member functions
	void fillMap();//fills the priority queue with the characters of common_words
	void printInfo(map<char,int> current_map);//prints out the chars and ints of the inputted map
	char getMostOccuring();//orders the letters map and puts it in ordered_map 



};








//The master class for the Hangman manipulation
class Hangman{

//private and public declarations
private:



public:
	
	Hangman();//class constructor

	//Member variables
	int wrong_answers;//the amount of wrong answers the user has guessed
	int max_wrong;//the max amount of wrong answers we are going to allow
	int len_guess;//the length of the string to guess
	int num_correct;//the amount of correct guesses thusfar
	
	string answer;//the user's word they are attempting to guess
	string goal;//same as answer except this is not modified throughout the program and is used if the user loses completely
	
	char guess;//the user's current guess
	
	bool it_contains;//used within contains to loop through until all instances of the char
						  //have been examined

	bool in_wrong_guesses;//whether the user has tried that letter before or not
	
	vector<char>blanked_out;//holds the current progress of guessing (start's as _ _ _ _...)
	vector<char>wrong_guesses;//letters guessed so far

	//Member functions	
	//Takes in the user input, updates blanked_out, add's it to guessed vector	
	void runGameLoop(AI my_ai);	
	bool contains();//returns whether the char guess is found within string answer

	void printVector(vector<char>my_vector);//prints out the user inputted vector by iterating through	

	void buildBlankedOut();//builds the blanked_out variable empty with just "_"'s 

};




#endif 
