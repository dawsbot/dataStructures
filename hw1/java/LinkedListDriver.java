public class LinkedListDriver{
	
	public static void main(String[] args){
		
		//LinkedList list = new LinkedList();
		LinkedList list = new LinkedList();
		//LinkedList another = new LinkedList();
		/*
		Node top = new Node();
		top.value = 1;
		top.next = new Node();
		top.next.value = 2;
		top.next.next = new Node();
		top.next.next.value = 3;
		top.next.next.next = null;
		*/
		
		Node top = list.initNode(0);
		list.append(top);
		list.appendData(1);
		list.appendData(2);
		list.appendData(3);
		Node another = list.initNode(9999);
		
		System.out.println("report: " + list.report());
		System.out.println("size: " + list.size());
		System.out.println("contains 1?: " + list.contains(1));
		
		list.remove(3);
		System.out.println("remove index 3: " + list.report());

		list.insert(3, another);
		list.insertData(1, 765432);
		System.out.println("\nadding 9999: " + list.report());
		
		
	}
}
