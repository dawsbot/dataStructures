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
				http://en.wikipedia.org/wiki/Most_common_words_in_English

##############################################################################################*/



using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include "hangman.hpp"

AI::AI(){

	//a string of the 25 most common nouns in the english language
	common_words = "timepersonyearwaydaythingmanworldlifehandpartchildeyewomanplaceworkweekcasepointgovernmentcompanynumbergroupproblemfact";
//	common_words = "sometimesiliketorun";
	//common_words = "timepersonyearw";
	//common_words = "rrunnin";
		//common_words = "abbccc";

//	common_words = "aaaabbbcccddee";
	//common_words = "eeddcccbbbaaaa";	
}




void AI::fillMap(){

	std::string::iterator iter;
	iter = common_words.begin(); 

	for (; iter != common_words.end(); ++iter){

		//cout << *iter << endl;

		if (letters.find(*iter) == letters.end()){//when the letter is unique
		 	letters.insert(pair<char,int>(*iter, 1));			
		}

		else {//when this key is already in the map
			++letters.find(*iter)->second;
		}	

	}

}




void AI::printInfo(map<char,int> current_map){

	std::map<char,int>::iterator iter;

	//iterate through the letters map	
	for (iter = current_map.begin(); iter != current_map.end(); ++iter){

		cout << "Letter: " << iter->first << endl;
		cout << "Amount of occurances: " << iter->second << endl << endl;

	}	

}




char AI::getMostOccuring(){

	//sets the minimum value to be huge so the first time through the loop
	int max_char = -1;//key where the max occurances occured
	int size = letters.size();
	int max_int = 0;
	std::map<char,int>::iterator iter;
	

		//iterate through the whole letters	
		iter = letters.begin();	
		//while (true){
		//	if (iter == letters.end()) break;	
		for (; iter != letters.end(); ++iter){
//			cout << "\nLETTERS.SIZE: " << letters.size() << endl;
//			cout << "iter->first: " << iter->first << endl;	
//			cout << "iter->second: " << iter->second << endl;
			if (iter->second > max_int){
//				cout << "(inside if)Indeed " << iter->second << " is greater than " << max_int; 
//				cout << "iter->first: " << iter->first << endl;	
				max_char = iter->first;	
		 		max_int = iter->second;	
				//ordered_map.insert(pair<char,int>(iter->first, iter->second));			
				//letters.erase(iter->first);
//				cout << "\nNew max_char: " << char(max_char) << endl;	
			}
		//	++iter;
		}	

//			cout << "\n(outside if/inside order map) Done with the string parsing once" << endl;
		 	//ordered_map.insert(ordered_map.end(),pair<char,int>(max_char, max_int));			
//		 	cout << "Inserting the pair of " << char(max_char) << " and " << max_int << endl; 
//			ordered_map.insert(pair<char,int>(max_char, max_int));			
			
//			cout << "(RETURNING) max_char: " << char(max_char) << endl;	
//			cout << "max_int: " << max_int << endl;	

			letters.erase(max_char);
			return max_char;

	

}




//Constructor to initialize the variables to certain values
Hangman::Hangman(){

	//initialize variables

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




void Hangman::runGameLoop(AI my_ai){

	//loop this
	while (true){

	//print out the progress the user has made in guessing
	printVector(blanked_out);
	cout << "\n";
	
	//uses the common words string to get the most popular characters
	guess = my_ai.getMostOccuring();

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
AI my_ai;//create an instance of the class

my_ai.fillMap();

//cout << "\nPrinting info for my_ai.ordered_map: " << endl;
//my_ai.printInfo(my_ai.ordered_map);
//my_ai.orderMap();


//ordered map should be n r u i
//								3 2 1 1
//cout << "\nPrinting info for my_ai.ordered_map: " << endl;
//my_ai.printInfo(my_ai.ordered_map);
//my_ai.printInfo(my_ai.letters);


//the word we want the computer to guess
my_game.answer = "helicopter";

my_ai.getMostOccuring();

//get and store the length of the word to be guessed
my_game.len_guess = (my_game.answer).size();

//build the blanked out vector according to the size of the word to be guessed
my_game.buildBlankedOut();


//allow the user's friend to guess and try to figure out the answer
my_game.runGameLoop(my_ai);


/*

//take in the word to be guessed as a password without displaying the input as it goes
my_game.answer = getpass("\nEnter the word to guess: ");

//get and store the length of the word to be guessed
my_game.len_guess = (my_game.answer).size();

//build the blanked out vector according to the size of the word to be guessed
my_game.buildBlankedOut();

//allow the user's friend to guess and try to figure out the answer
my_game.runGameLoop();

*/


}
