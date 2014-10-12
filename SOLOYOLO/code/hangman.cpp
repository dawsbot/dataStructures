/*#############################################################################################


	Author: Dawson Botsford 
	Student ID: 102003505

	Date: 4/22/2013

	Purpose: Final Game project for CSCI-2400 with Gabe Johnson
				At CU Boulder Spring Semester 2013

	Description: This is the classic hangman game. One user enters
	the word which they would like their friend to be guessing and
	for the rest of the game the friend tries to guess one character
	at a time until he has won or ran out of guesses	


	Sources: http://www.cplusplus.com/articles/E6vU7k9E/


##############################################################################################*/



using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "hangman.hpp"


//Constructor to initialize the variables to certain values
Hangman::Hangman(){

	//initialize variables
	dead = false;

	max_wrong = 6;//the amount of wrong answers you want the user to be allowed to make before losing
	wrong_answers = 0;
	num_correct = 0;

	//print out welcome message and rules
	cout << "\n\nWelcome to Hangman!" << endl;
	cout << "Remember to use all lowercases during this game!" << endl;
	cout << "Initially you have " << max_wrong << " guesses until you lose." << endl;

}

void Hangman::buildBlankedOut(){
	
	//iterate through to create the output of blanks and spaces
	for ( int i = 1; i < 2 * len_guess; ++i){

		if (i % 2 == 0){//i is even insert a ' ' 

			blanked_out.push_back(' ');

		}
		else //i is odd. insert a '_'
		{

			blanked_out.push_back('_');

		}
	}

}


void Hangman::printVector(vector<char>my_vector){

	vector<char>::iterator iter;
	for (iter = my_vector.begin(); iter != my_vector.end(); ++iter)
		
		cout << *iter;

}




bool Hangman::contains(){

	it_contains = false;

	for (int i = 0; i < len_guess; ++i){

		//if the character at i is the same as the guessed char
		if (int(answer[i]) == int(guess)){
			
			blanked_out[(2*i)] = guess;	
			++num_correct;	
			answer[i] = '*';	

			contains();	
			it_contains = true;
		}	

	}

//if the above if statement was never entered, it_contains is set to false
return it_contains;

}




void Hangman::runGameLoop(){

	//loop this
	while (true){

	//print out the progress the user has made in guessing
	printVector(blanked_out);
	cout << "\n";

	//take in a guess
	cout << "\nEnter a single character guess: ";
	cin >> guess;

	in_wrong_guesses = false;
	for (int i = 0; i < wrong_guesses.size(); ++i){

		if (guess == wrong_guesses[i]){

			in_wrong_guesses = true;
		
		}		

	}	

	//if the user has already tried this letter before
	if (in_wrong_guesses){

		cout << "\nYou already guessed that letter silly goose!" << endl;	
		cout << "You have " << (max_wrong - wrong_answers) << " wrong guesses left until you lose" << endl;
	
	}
	else{//this is a new letter attempt

	//add that char to vector<char>guessed
	wrong_guesses.push_back(guess);

	

	
	//check if that is in answer
	if (contains()){

		//cout << "Your guess '" << guess << "' IS contained in the answer!" << endl;
		cout << "'" << guess << "' IS in the answer!" << endl;
		//cout << "You have guessed correctly " << num_correct << " times" << endl;
		cout << "You have " << (max_wrong - wrong_answers) << " wrong guesses left until you lose" << endl;

	
	//	printVector(blanked_out);
	
		//user has won!	
		if (num_correct == len_guess){

			//print victory information
			cout << "____________________________________________" << endl;	
			cout << "\nYOU WON!" << endl;
			cout << "The final word was: ";		
			printVector(blanked_out);
			cout << "\n\n\n";	
			return;

	}	

	}

	else //the user guessed a wrong letter 
	{

		//print failure message
		//cout << "Your guess '" << guess << "' is NOT contained in the answer!" << endl;
		cout << "'" << guess << "' is NOT in the answer!" << endl;

		++wrong_answers;//increment the wrong answer counter	

		cout << "You have " << (max_wrong - wrong_answers) << " wrong guesses left until you lose" << endl;

		//if the user ran out of guesses display error message
		if (wrong_answers >= max_wrong){
		
			cout << "You used up all of your guesses!" << endl;
			cout << "GAME OVER" << endl;
			cout << "The word was: " << answer << endl;	
			return;//quit the loop and function	
	
		}

	}

}
}

}




//take in the user input and play the hangman game
int main(){

Hangman my_game;//create an instance of the class

//take in the word to be guessed as a password without displaying the input as it goes
my_game.answer = getpass("\nEnter the word to guess: ");

//get and store the length of the word to be guessed
my_game.len_guess = (my_game.answer).size();

//build the blanked out vector according to the size of the word to be guessed
my_game.buildBlankedOut();

//allow the user's friend to guess and try to figure out the answer
my_game.runGameLoop();

}


