
/*===================================================================================

	Author: Bryan Newsom, Dawson Botsford, ... (Fill in your names)

	Date: 4/22/2013

	Purpose: Final Game project for CSCI-2400 with Gabe Johnson
				At CU Boulder Spring Semester 2013

	Description: This is the classic hangman game. One user enters
	the word which they would like their friend to be guessing and
	for the rest of the game the friend tries to guess one character
	at a time until he has won	


====================================================================================*/	


using namespace std;
#include <iostream>

#include "master.hpp"



//Here are the functions we are making:
//The main is at the bottom of this file

//Constructor
Hangman::Hangman(){

	dead = false;


}

bool Hangman::getDead(){

return dead;


}

void Hangman::setDead(bool new_dead){

	dead = new_dead;	

}




int main(){

Hangman my_game;//create an instance of the class

//print out dead information for testing
cout << "Dead: " << my_game.getDead() << endl;

my_game.setDead(true);
cout << "After changing dead: " << my_game.getDead() << endl;

//print welcome message and take in user input
cout << "Welcome to hangman!" << endl;
cout << "Enter the word you or your friend will try and guess: " << endl;
//cin <<  

/*

Variables we will use:
	
Vectors:
	Alphabet


Strings:	
	answer (The string inputted in the beginning/the word to guess)

	
Int:
	wrong_answer_count
	max_wrong_guesses_possible


Char:
	current_guess (The letter the kiddos think is in the answer)


Booleans:
	is_dead

Function names:
	get_dead (returns whether the player is dead(used up all turns))
	
	//iterates through the string answer to see if char current_guess is within it
	void contains (


*/



}










