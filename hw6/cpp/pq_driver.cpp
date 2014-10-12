// Author: Dawson Botsford
// pq_driver.cpp
//
// This is an empty unit test file that you can implement (or not) to
// create unit tests for your code.
//
// You'll likely want one for insert, remove, and peek. Try to think
// about how your queue could break, and write tests that help you
// test your deepest priority-queue-related fears.
//
// The test code will appear on RetroGrade late in the game.

#include "UTFramework.h"
#include "pq.h"

using namespace Thilenius;

pq* hand_make();


pq* cursor = init_priority_queue();
pq* list = hand_make();

SUITE_BEGIN("Priority Queue")




//pq* cursor = init_priority_queue();

TEST_BEGIN("Init")
{



  IsTrue("cursor->next == null?", cursor->next == NULL, "cursor->next should be null!");
  IsTrue("cursor->priority == null?", cursor->priority == NULL, "cursor->next should be null!");
  IsTrue("cursor->prev == null?", cursor->prev == NULL, "cursor->prev should be null!");
	string atext = "XXX";
	insert(cursor, atext, 1000.0); 
 IsTrue("Inserting to an empty list (data)?", cursor->data == "XXX", "Should be == XXX!"); 
 IsTrue("Inserting to an empty list (priority)?", cursor->priority == 1000.0, "Should be == 1000.0!"); 

//	cout << "list->priority: " << cursor->priority << endl;
//	cout << "list->data: " << cursor->data << endl;



}TEST_END




TEST_BEGIN("hand_make()"){


IsTrue("Most important is Most Important?",
	peek(list) == "Most Important", "Should return Most Important!");

remove(list);

IsTrue("Remove from a list with 3 elements?", peek(list) == "Less Important", "Should return Less Important!");
//cout << "A peek at the list after removing: " << peek(list) << endl;

string text = "New Least important";
insert(list, text, -7.0);

//Insert1 inserts to the beginning of the list
IsTrue("Insert1 data?", list->priority == -7.0, "Incorrect Priority"); 
//	cout << "list->priority: " << list->priority << endl;
//	cout << "list->data: " << list->data << endl;

IsTrue("Insert1?", list->data == "New Least important", "Incorrect data"); 

IsTrue("Still correct last element?", peek(list) == "Less Important", "Should return Less Important!");


string words = "Insert2";
insert(list, words, 99.0);
//insert2 is at the end of the list
IsTrue("Insert2?", peek(list) == "Insert2", "Should return Insert2!");



words = "Insert3";
insert(list, words, 6.0);
//insert2 is at the end of the list
IsTrue("Insert3?", list->next->next->next->data  == "Insert3", "Should return Insert3!");
cout << list->next->data << "    " << list->next->next->data << "    " << list->next->next->next->data
	<< "    " << list->next->next->next->next->data << endl;


cout << list->next->priority << "    " << list->next->next->priority << "    " << list->next->next->next->priority
	<< "    " << list->next->next->next->next->priority << endl;



}TEST_END






TEST_BEGIN("Gabe's Test"){

pq* queue = init_priority_queue();
string text = "Speaker of the House";
insert(queue,  text, 7.9);
text = "President";
insert(queue, text, 10.0);
text = "Congressional Staffer";
insert(queue, text, 2.0);
cout << remove(queue) << endl; // President
cout << remove(queue) << endl; // Speaker of the House
cout << remove(queue) << endl; // Congressional Staffer











}TEST_END


SUITE_END

pq* hand_make(){

pq* most = new pq;
pq* less = new pq; 
pq* least = new pq;

most->priority = 10.0;
most->data = "Most Important";
most->next = NULL;
most->prev = less;

less->priority = 5.0;
less->data = "Less Important";
less->next = most;
less->prev = least;

least->priority = 3.0;
least->data = "The Least Important";
least->next = less;
least->prev = NULL;

return least;
}




int main (int argc, char* argv[])
{	
  UTFrameworkInit;
}
