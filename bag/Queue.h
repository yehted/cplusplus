/****************************************************
* A generic queue container, implementing first in
* first out (FIFO) behavior, using a singly linked
* list. Supports iterating, enqueue, and dequeue
* methods.
*
*****************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iterator>

template <class T>
class Queue {
	class Node;

public:
	
	class Iterator;

	Queue() : N_(0), first_(NULL), last_(NULL) {}

	~Queue() {
//		printf("Destructing queue\n");
		clear();
	}

	Queue(const Queue& other) : N_(0), first_(NULL), last_(NULL) {
//		printf("Copying queue\n");
		copy(other);
	}

	Queue& operator=(const Queue& other) {
//		printf("Assigning queue\n");
		if (&other == this) return *this;

		// Deallocate
		clear();

		// Copy
		copy(other);

		return *this;
	}

	void enqueue(const T& item) {
		Node* oldlast = last_;
		last_ = new Node(item);		
		if (oldlast == NULL) first_ = last_;
		else oldlast->next_ = last_;
		N_++;
	}

	T dequeue() {
		if (isEmpty()) throw std::out_of_range("Queue is empty");
		Node* oldfirst = first_;
		T item = oldfirst->item_;
		first_ = first_->next_;
		delete oldfirst;
		if (isEmpty()) last_ = NULL;	// to avoid loitering
		N_--;
		return item;
	}

	T& peek() {
		return first_->item_;
	}

	void clear() {
		Node* current = first_;
		while (current != NULL) {
			first_ = first_->next_;
			delete current;
			current = first_;
			N_--;
		}
		last_ = NULL;
	}

	void copy(const Queue& other) {
		Node* current = other.first_;
		while (current != NULL) {
			enqueue(current->item_);
			current = current->next_;
		}
	}

	int size() { return N_; }

	bool isEmpty() { return first_ == NULL; }

	Iterator begin() { return Iterator(first_); }

	Iterator end() { return Iterator(NULL); }

	class Iterator : public std::iterator < std::forward_iterator_tag, T > {
	public:
		Iterator() : ptr_(NULL) {}
		Iterator(Node* ptr) : ptr_(ptr) {}
		~Iterator() {}
		Iterator(const Iterator& other) : ptr_(other.ptr_) {}
		Iterator& operator=(const Iterator& other) { ptr_ = other.ptr_; return *this; }
		Iterator& operator++() { ptr_ = ptr_->next_; return *this; }
		bool operator==(const Iterator& other) { return ptr_ == other.ptr_; }
		bool operator!=(const Iterator& other) { return ptr_ != other.ptr_; }
		T& operator*() { return ptr_->item_; }
		T* operator->() { Iterator tmp = *this; T& value = *tmp; return &value; }

	private:
		Node* ptr_;
	};

private:
	struct Node {
		Node() : next_(NULL) {}
		Node(const T& item) : item_(item), next_(NULL) {}

		T item_;
		Node* next_;
	};

	int N_;				// number of items in queue
	Node* last_;		// pointer to back of queue
	Node* first_;		// pointer to front of queue
};
#endif // !QUEUE_H