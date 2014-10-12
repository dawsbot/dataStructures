/**
 * LinkedList.java
 *
 * Consult the LinkedListInterface for method contracts.
 */
public class LinkedList implements LinkedListInterface {
    // It is up to you how this is implemented (aside from not being
    // able to use the standard Java collections or anything else)

    // I might suggest having some member variables here. All you need
    // is a single Node, but you can be fancy if you want.
	
	private Node head = null;

    public Node initNode(int data) { 
	
	Node cursor = new Node();
	cursor.next = null;
	cursor.value = data;	
	
	return cursor;
    }
    
    
    public LinkedList(){
		
		this.head = null;
	}
    
    
    public String report() {
	
	String contents = "";//string to return
	Node cursor = this.head;
	
	while (cursor != null){
		
		contents += cursor.value + " ";
		cursor = cursor.next;
		
		}
	return contents;
    }

    public void appendData(int data) {
	Node cursor = initNode(data);
	append(cursor);
    }

    public void append(Node node) {
		
		if (this.head == null) this.head = node;
		
		else{		
		
		Node cursor = this.head;
		while (cursor.next != null) cursor = cursor.next;
		
		cursor.next = node;		}
		
    }

    public void insertData(int offset, int data) {
		Node cursor = initNode(data);
		insert(offset, cursor);
    }

    public void insert(int offset, Node node) {
		
		Node cursor = this.head;
		//special case
		if (offset == 0){
			
			node.next = cursor;
			this.head = node;
			cursor = null;
			return;
		}
		
		
		int index = 0;
		
		//increment up until we are pointing to one node before where the new one will be
		while ((index + 1) < offset){
			
			++index;
			cursor = cursor.next;
			
		}
		node.next = cursor.next;
		cursor.next = node;
		
		
    }

	//get rid of the node at the index offset
    public void remove(int offset) {
		
		Node cursor = this.head;
		
		if (offset == 0){
			
			this.head = cursor.next;
			cursor = null;
			return;
		}
		
		
		int index = 0;
			
		while (index + 1 < offset){
			
			++index;
			cursor = cursor.next;
		
		}
		Node deleteit = cursor.next;
		cursor.next = cursor.next.next;
		deleteit = null;
    }

    public int size() {
		
	int num = 0;
	Node cursor = this.head;
	
	//iterate through and count
	while (cursor != null){
		++num;
		cursor = cursor.next;
		}
	
	return num;
    }

    public boolean contains(int data) {
		
		Node cursor = this.head;
		
		while (cursor != null) {
			
			if (cursor.value == data) return true;
			cursor = cursor.next;
		}
		
	return false;
    }

}
