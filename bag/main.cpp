#include "Bag.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include "vld.h"

int main(int argc, char* argv[]) {
	using namespace std;
	int foo[5] = { 1, 3, 5, 6, 8 };
	Bag<int> bag;
	Queue<int> queue;
	Stack<int> stack;
	for (int i = 0; i < 5; i++) {
		bag.add(foo[i]);
		queue.enqueue(foo[i]);
		stack.push(foo[i]);
	}
	
	// Bag
	cout << "Bag" << endl;
	Bag<int> b_copy = bag;
	//b_copy = bag;
	for (int s : b_copy)
		cout << s << " ";
	cout << endl;
	cout << b_copy.size() << endl;
	bag.clear();
	cout << bag.size() << endl;

	// Queue
	cout << "Queue" << endl;
	Queue<int> q_copy = queue;
	//q_copy = queue;
	
	int N = queue.size();
	for (int i = 0; i < N; i++)
		cout << queue.dequeue() << " ";
	cout << endl;
	cout << queue.size() << endl;

	for (int s : q_copy)
		cout << s << " ";
	cout << endl;
	cout << q_copy.size() << endl;

	// Stack
	cout << "Stack" << endl;
	Stack<int> cstack;
	cstack = stack;

	int M = stack.size();
	for (int i = 0; i < M; i++)
		cout << stack.pop() << " ";
	cout << endl;
	cout << stack.size() << endl;

	stack.push(22);

	for (int s : stack)
		cout << s << " ";
	cout << endl;
	cout << stack.size() << endl;

	return 0;
}