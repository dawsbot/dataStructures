/*===================================================================================

	Author: Dawson Botsford 
	Student ID: 102003505
		
	*I was the one who talked to you about splitting off from my group
	because I did not believe the project was big enough for a group of
	5 people. So here goes nothing solo-style! Thanks.

	Date: 4/22/2013

	Purpose: Final Game project for CSCI-2400 with Gabe Johnson
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



using namespace std;


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

	char guess;//the user's current guess

	bool dead;//whether the user has used all of it's guesses	
	bool it_contains;//used within contains to loop through until all instances of the char
						  //have been examined

	bool in_wrong_guesses;//whether the user has tried that letter before or not
	
	vector<char>blanked_out;//holds the current progress of guessing (start's as _ _ _ _...)
	vector<char>wrong_guesses;//letters guessed so far

	//Member functions	
	//Takes in the user input, updates blanked_out, add's it to guessed vector	
	void runGameLoop();	
	bool contains();//returns whether the char guess is found within string answer

	void printVector(vector<char>my_vector);//prints out the user inputted vector by iterating through	

	void buildBlankedOut();//builds the blanked_out variable empty with just "_"'s 

};




#endif 
