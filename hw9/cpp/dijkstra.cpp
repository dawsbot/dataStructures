/*
   dijkstra.cpp

   ------------------------------------------------------------

   A reprise of the 'graph.cpp' file, but modified for doing
   Dijkstra's algorithm.  All the graphs in this assignment are DAGs,
   though be aware that Dijkstra's does not require this. Only
   implement the parts you really need!

   You are responsible for implementing:

   Graph::isDAG(),

   Graph::dijkstra(Node*), and

   Graph::dijkstra(Node*, Node*).

   You will likely need to write some helper functions to babysit your
   Tree* and priority queue (or pq substitute). How you do this is up
   to you!

   ------------------------------------------------------------



   Your Name: Dawson Botsford

   Your Collaborators:

 */

#include <algorithm> // std::find
#include <iostream>
#include <string>
#include <set>
#include <limits>
#include <queue>
#include "dijkstra.hpp"

using namespace std;

Graph::Graph() {
  // graphs are undirected by default
  directed = false;
}

Graph::~Graph() {

}

vector<Node*> Graph::getNodes() {
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  return edges;
}

int Graph::getClock() {
  return clock;
}

void Graph::addNode(Node& n) {
  nodes.push_back(&n);
}

void Graph::addEdge(Edge& e) {
  edges.push_back(&e);
}
 
void Graph::removeNode(Node& n) {
  for (vector<Node*>::iterator it = nodes.begin();
       it != nodes.end(); 
       it++) {
    if (&n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(Edge& e) {
  for (vector<Edge*>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (&e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  directed = val;
}

bool Graph::isDirected() {
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node& n) {
  set<Edge*> ret;
  for (size_t i = 0; i < edges.size(); i++) {
    Edge* edge = edges[i];
    if (edge->getStart() == &n) {
      ret.insert(edge);
    }
    if (!directed && edge->getEnd() == &n) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  // implement. remember the new node members.

	clock = 0;

	vector<Node*>::iterator it = nodes.begin();

	//reset all nodes
	for (;it != nodes.end(); it++){
		Node* n = *it;
		//cout << *n << endl;
		n->clear();	

	}
	vector<Edge*>::iterator eit = edges.begin();

	//reset all edges
	for (;eit != edges.end(); eit++){

		Edge* e = *eit;
		//cout << *e << endl;
		e->setType(UNDISCOVERED_EDGE);	

	}



}

void Graph::tick(string message) {
  // optional
}

void Graph::dfs(Node& start) {
  // implement (just like last week. copy/paste)


	//initialize variables
	Node* other;
	Edge* e;
	int col, dt, ft, rk;

	clock++;
	start.setColor(GRAY, clock);

	set<Edge*> E = getAdjacentEdges(start);
	set<Edge*>::iterator it = E.begin();

	for (; it != E.end(); it++){

		e = *it;		
		if (e->getStart() == &start){
			other = e->getEnd();
		}
		else{
			other = e->getStart();
		} 


		other->getDiscoveryInformation(col, dt, ft, rk);
		
		if (col == WHITE){
	//		cout << "col == WHITE" << endl;
			other->setPredecessor(start);
			e->setType(TREE_EDGE);
			dfs(*other);			

		}else if (col == GRAY){

	//		cout << "col == GRAY" << endl;
			e->setType(BACK_EDGE);

		}else if (col == BLACK){

	//		cout << "col == BLACK" << endl;
			bool ancest = other->isAncestor(start);	

			//start is an ancestor of other	
			if (ancest){

				e->setType(FORWARD_EDGE);	

			}
			else {

				e->setType(CROSS_EDGE);

			}

		}

	}

	clock++;
	start.setColor(BLACK, clock);

}


void Graph::dfs(Node& start, Node& finish) {
  // implement if you think it is necessary
}






/**
 * Perform Dijkstra's algorithm for finding the minimum path length
 * from the given start node to all other reachable nodes in the
 * graph.
 *
 * Return the spanning tree that is rooted at the given start node,
 * with a path to all reachable nodes.
 **/
Tree* Graph::dijkstra(Node* start) {
  
	Tree* shortest_path;
//	shortest_path->setRoot(start);

	//initialize Node vector and node iterator	
	vector<Node*> Q = getNodes() ;
	vector<Node*>::iterator node_iter;

	//initialize Edge set and edge iterator	
	set<Edge*> adj_edges;
	set<Edge*>::iterator edge_iter;
		
	//iterate through all of the nodes in the Q
	for (node_iter = Q.begin(); node_iter != Q.end(); ++node_iter){
		Node* current = Q.back();
		Q.pop_back();
		adj_edges = getAdjacentEdges(*start);

		
		for (edge_iter = adj_edges.begin(); edge_iter != adj_edges.end(); ++edge_iter){




		}


	}



	return NULL;

	}






/**
 * Perform Dijkstra's algorithm like in the other version, but end
 * the algorithm when a definitive path length is found to the given
 * end node. Note that the end node might be unreachable.
 *
 * Return the spanning tree that was found during this search. Note
 * that when an answer is found for the path from start to end, the
 * algorithm stops, so the tree may be incomplete compared with what
 * is produced from the single-argument version of the dijkstra
 * function.
 **/
Tree* Graph::dijkstra(Node* start, Node* end) {
  // implement me
  return NULL;
}



/**
 * Is this graph a DAG or not? Return true if it is, false if not.
 *
 *
**/
bool Graph::isDAG() {

	//prepare the graph
	clear();
	if (!directed)
		return false;
 
	//initialize vars
	Edge* current_edge; 

	//run dfs on the root node
	vector<Node*> my_nodes = getNodes();
	dfs(**my_nodes.begin());	

	vector<Edge*> my_edges = getEdges();
	vector<Edge*>::iterator it;

	//check all edges for a back edge
	for (it = my_edges.begin(); it != my_edges.end(); ++it){
	
		current_edge = *it;

		//if back edges exist
		if (current_edge->getType() == BACK_EDGE){
			return false;
		}

	}

	//no back edges exist in the entire tree
	return true;

}




Node::Node(string s) {
  data = s;
}

Node::~Node() {

}

string Node::getData() {
  return data;
}

void Node::setRank(int r) {
  rank = r;
}

//reset every aspect of this node
void Node::clear() {

	this->color = WHITE;
	color = WHITE;
	discovery_time = -1;
	completion_time = -1;
	rank = -1;
	predecessor = NULL;
	path_distance = 0;

}





void Node::setColor(int search_color, int time) {
  // implement me

	color = search_color;

	if (color == WHITE){
		discovery_time = -1;
	}
	else if (color == GRAY){
		discovery_time = time;
	}
	else if (color == BLACK){
		completion_time = time;
	}

}


void Node::getDiscoveryInformation(int& color, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  // implement me

	color = this->color;
	disco_time = this->discovery_time;
	finish_time = completion_time;
	bfs_rank = rank;



}


bool Node::isAncestor(Node& other) {
  // implement me if you think it is necessary
}

void Node::setPredecessor(Node& other) {
  predecessor = &other;
}

Node* Node::getPredecessor() {
  return predecessor;
}

float Node::getPathDistance() const {
  return path_distance;
}

void Node::setPathDistance(float pd) {
  path_distance = pd;
}

Edge::Edge(Node& n1, Node& n2) {
  a = &n1;
  b = &n2;
  weight = 1.0;
}

Edge::Edge(Node& n1, Node& n2, float w) {
  a = &n1;
  b = &n2;
  weight = w;
}

Edge::~Edge() {
}

float Edge::getWeight() {
  return weight;
}

void Edge::setWeight(float val) {
  weight = val;
}

Node* Edge::getStart() {
  return a;
}

Node* Edge::getEnd() {
  return b;
}

int Edge::getType() {
  return type;
}

void Edge::setType(int edge_type) {
  type = edge_type;
}

ostream &operator << (ostream& out, Graph graph) {
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (size_t i = 0; i < graph.nodes.size(); i++) {
    Node* n = graph.nodes[i];
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (size_t i=0; i < graph.edges.size(); i++) {
    Edge* e = graph.edges[i];
    out << *e << ", ";
  }
  out << "]";
  return out;
}

ostream &operator << (std::ostream& out, Node node) {
  out << node.data << " (";
  if (node.color == WHITE) {
    out << "White ";
  } else if (node.color == GRAY) {
    out << "Gray ";
  } else if (node.color == BLACK) {
    out << "Black ";
  } else {
    out << "??? ";
  }
  out << node.discovery_time << "/" << node.completion_time;
  out << " bfs_rank: " << node.rank;
  out << ")";
  return out;
}

ostream &operator << (std::ostream& out, Edge edge) {
  out << *edge.a << " -- " << *edge.b;
  out << " (";
  if (edge.type == UNDISCOVERED_EDGE) {
    out << "Undiscovered";
  } else if (edge.type == TREE_EDGE) {
    out << "Tree";
  } else if (edge.type == BACK_EDGE) {
    out << "Back";
  } else if (edge.type == FORWARD_EDGE) {
    out << "Forward";
  } else if (edge.type == CROSS_EDGE) {
    out << "Cross";
  }
  out << ")";
  return out;
}

/**
 * Make a new tree node for the given node.
 **/
TreeNode::TreeNode(Node* data) {
  this->node = data;
}

/**
 * Find a TreeNode that has the given data in this tree's member list,
 * or NULL if none are found.
 **/
TreeNode* Tree::find(Node* data) {
  vector<TreeNode*>::iterator tnit = members.begin();
  for (;tnit != members.end(); tnit++) {
    TreeNode* tn = *tnit;
    if (tn->node == data) {
      return tn;
    }
  }
  return NULL;
}

/**
 * Updates the tree such that (a) child is inserted into the tree if
 * necessary, (b) old_parent no longer refers to child, and (c)
 * new_parent does.
 **/
void Tree::update(Node* child, Node* old_parent, Node* new_parent) {
  TreeNode* child_tn = find(child);
  TreeNode* old_parent_tn = find(old_parent);
  TreeNode* new_parent_tn = find(new_parent);
  // if both the child and parent were present, remove the
  // now-outdated relationship.
  if (child_tn != NULL && old_parent_tn != NULL) {
    vector<TreeNode*>::iterator tnit;
    tnit = std::find(old_parent_tn->children.begin(), 
		old_parent_tn->children.end(), child_tn);
    if (tnit != old_parent_tn->children.end()) {
      old_parent_tn->children.erase(tnit);
    }
  }
  // if child_tn is null it means we don't yet know about the
  // child. We should add a new TreeNode to the members list.
  if (child_tn == NULL) {
    child_tn = new TreeNode(child);
    members.push_back(child_tn);
  }
  // if new_parent_tn is null, that's a straight up bug.
  if (new_parent_tn == NULL) {
    cout << "WARNING: New parent has no tree node in tree." << endl;
    cout << "         This is definitely a bug." << endl;
  } else {
    new_parent_tn->children.push_back(child_tn);
  }
}

/**
 * Sets the root node of the tree, clears the membership list, and
 * inserts the root into that membership list.
 **/
void Tree::setRoot(Node* n) {
  root = new TreeNode(n);
  members.clear();
  members.push_back(root);
}

/**
 * Gives you the root of the tree.
 **/
TreeNode* Tree::getRoot() {
  return root;
}

/**
 * Private member function implementation. Prints the tree with
 * multi-level output depending on where you are. This is recursive.
 **/
void Tree::print_tree(TreeNode* tn, int lvl) {
  // leave the cout statements in
  for (int i=0; i < lvl; i++) {
    cout << " . ";
  }
  cout << tn->node->getData() << " dist: " << tn->node->getPathDistance() << endl;
  for (size_t i = 0; i < tn->children.size(); i++) {
    print_tree(tn->children[i], lvl+1);
  }
}

/**
 * Prints the tree in a nice output form to standard output.
 **/
void Tree::print_tree() {
  TreeNode* cursor = root;
  print_tree(cursor, 0);
}

