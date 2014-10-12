/*

  fsm.cpp - Finite State Machine

  Read the header file 'fsm.hpp' for all documentation on individual
  functions. I suggest you start by getting the unit test cases to
  pass in order. E.g. start with the Defaults one, then do Add States,
  and so on.

  Your Name: Dawson Botsford 

  Your Collaborators: Bryan Newsom, Gabe Johnson

 */

#include "fsm.hpp"

using namespace std;

FSM::FSM() {

state = -1;
default_state = -1;

}

int FSM::addState(string label, bool is_accept_state) {

	//declare define and initialize a State pointer
	State* st = new State;
	st->label = label;
	st->accept = is_accept_state;
	st->failure_trans = -1;
	int id = states.size();
	states.push_back(st); //push the state onto the states vector

	//if it's the first state added
	if (id == 0){

		default_state = 0;
		state = 0; 	

	}

	return id;

}


int FSM::addState(string label) {

 return addState(label, false);

}


/**
   * Adds a transition between two states that activates when the
   * given signal is received. This is considered duplicate if there
   * is another transition from stateA to stateB with the same
   * signal. The transition label is ignored when determining
   * duplicate status. 
   * 
   * If this is a duplicate, nothing is done and -1 is returned. 
   *
   * If either state is not present in the FSM, nothing is done and -1
   * is returned.
   *
   * Otherwise, a new transition is installed in the FSM and given a
   * non-negative id that is unique among transitions. That id is
   * returned.
   *
   * stateA: the start state's id. The FSM must be in this state for
   *         the transition to take place.
   *
   * stateB: the end state. After taking the transition, the FSM will
   *         be placed in stateB.
   *
   * signal: the signal that (assuming we are in stateA) will trigger
   *         this particular transition. If the signal is
   *         FAILURE_SIGNAL, it is considered the 'failure signal',
   *         which is a catch-all for bad input. If this is the
   *         failure signal, stateA will use this transition if it
   *         receives a signal that it can not otherwise use.
   *
   * transLabel: the label for this transition. 
   **/
int FSM::addTransition(int stateA, int stateB, 
		       int signal, string transLabel) {

//	cout << "\nstateA: " << stateA << endl;
//	cout << "transitions.size(): " << transitions.size() << endl;
	
	if (stateA < 0){
//		cout << "Returning false in addtransition!" << endl;
		return false;
	}	
		
	Transition* my_trans = new Transition;
	int iter;

	//to assure this transition does not already exist in transitions vector
	bool unique = true; 

	my_trans->next_state = stateB;
	my_trans->signal = signal;
	my_trans->label = transLabel;

	State* my_state = getState(stateA);

	//check to see if this transition is not a repeat
	for( iter = 0;iter != my_state->trans.size(); ++iter){

		int trans_id = my_state->trans[iter];
		
		if (getTransition(trans_id)->next_state == my_trans->next_state){
			unique = false;
			cout << "This is a duplicate transition" << endl;
			return -1;	
		}	
	}

	//if the trans is unique make the trans and return the id where the trans was placed 	

		my_state->trans.push_back(transitions.size());
		transitions.push_back(my_trans);

		//return the new id 
  		return transitions.size() - 1;
	


}


int FSM::countStates() {
	return states.size();

}

int FSM::countTransitions() {
	return transitions.size();

}

int FSM::getCurrentState() {
	return state;

}



bool FSM::isAcceptState() {
  
	State* my_state = getState(this->state);
	
	if (my_state == NULL)
		return false;

	else  
		return my_state->accept;	
	
}



/**
   * Returns a pointer to the State object with the given id, or NULL
   * if no such state is in the FSM.
   **/
State* FSM::getState(int id) {

//if id is invalid
	if (id < 0 || id >= states.size())
		return NULL;

	else return states[id];

}


Transition* FSM::getTransition(int id) {
  //return NULL;

	if (id < 0 || id >= transitions.size())
		return NULL;

	else return transitions[id];


}

int FSM::getDefaultState() {
	
	return default_state;

}

void FSM::setState(int id) {

	state = id;

}

/**
  * Handle an input event signal. For the current state, this should
  * be compared to each possible transition's signal. If there is
  * match, that transition is taken and the FSM enters the state on
  * the other end of the transition. 
  *
  * If no regular transition was taken, and if the current state has
  * a nonzero ID for a failure transition, that transition should be
  * used.
  *
  * If a transition was taken, return true. Otherwise return false.
  **/
bool FSM::handleSignal(int signal) {
 
	//cout << "signal: " << signal << endl; 
	int iter;
	State* my_state = getState(state);	
	
	//State* my_state = getState(getCurrentState());	
	if (my_state == NULL){
		cout << "my_state == NULL" << endl;	
		return false;
	}	

	//iterate through and determine if the signal can be taken
	for (iter = 0; iter != my_state->trans.size(); ++iter){
	
		int trans_id = my_state->trans[iter];
		
//		cout << "my_state->label: " << my_state->label << endl;			
		//the signal matches something in the transitions vector	
		if (getTransition(trans_id)->signal == signal){
//			cout << "MATCH FOUND!" << endl;
		
			//set current state to next state	
			state = getTransition(trans_id)->next_state;
			
			return true;

		}
		else {

			my_state->failure_trans = trans_id;
			//return false;

		}
	}

	cout << "\nmy_state->failure_trans:  " << my_state->failure_trans << endl;

	if (my_state->failure_trans != -1){
			cout << "TRANSITIONING INTO FAILURE" << endl;
			state = getTransition(my_state->failure_trans)->next_state;
			//return true;
//			return false;	
 
	}
	cout << "Made it to end of handle signal, returning false" << endl; 
	return false;
}




ostream &operator << (ostream& out, State* st) {
  if (st == NULL) {
    out << "State: NULL";
  } else {
    out << "State: " << st->label;
    if (st->accept) {
      out << " +";
    }
  }
  return out;
}
