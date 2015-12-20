/***************************************************************************
* A generic bag or multiset, implemented using a singly-linked list.
* Iterator does not reverse the items, and the container does not support 
* removal of items from the bag.
*
* It supports insertion and iterating over the items in arbitrary order.
*
* For additional documentation, see Section 1.3 of Algortithms, 4th Ed.
* by Robert Sedgewick and Kevin Wayne
*
****************************************************************************/
#ifndef BAG_H
#define BAG_H

#include <iterator>

template <class T>
class Bag {
	class Node;	

public:

	class Iterator;

	// Constructor
	Bag() : N_(0), first_(NULL) {}

	// Destructor
	~Bag() {
//		printf("Destructing bag\n");
		clear();
	}

	// Copy constructor
	Bag(const Bag& other) : N_(0), first_(NULL) {
//		printf("Copying bag");
		copy(other);
	}

	// Assignment operator
	Bag& operator=(const Bag& other) {
//		printf("Assigning bag");
		if (this == &other) return *this;
		
		// Free memory
		clear();

		// Copy elements
		copy(other);
		
		return *this;
	}

	// Methods
	bool isEmpty() { return first_ == NULL; }

	int size() { return N_; }

	void add(const T& item) {
		Node* oldfirst = first_;
		first_ = new Node(item);
		first_->next_ = oldfirst;
		N_++;
	}

	void clear() {
		Node* current = first_;
		while (current != NULL) {
			first_ = first_->next_;
			delete current;
			current = first_;
			N_--;
		}
	}

	void copy(const Bag& other) {
		Node* current = other.first_;
		while (current != NULL) {
			add(current->item_);
			current = current->next_;
		}
	}

	Iterator begin() { return Iterator(first_); }

	Iterator end() { return Iterator(NULL); }

	// Iterator class
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
		Node(const T& item) : item_(item) {}

		T item_;
		Node* next_;
	};

	int N_;
	Node* first_;
};
#endif // !BAG_H