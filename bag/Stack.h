/***************************************************
* A generic stack container, implementing last in
* first out (LIFO) behaviour using a singly-linked
* list. Supports iterating, push, and pop methods.
*
****************************************************/
#include <iterator>
#include <stdexcept>

template<class T>
class Stack {
	class Node;

public:

	class Iterator;

	Stack() : N_(0), first_(NULL) {}

	~Stack() {
//		printf("Destructing stack\n");
		clear();
	}

	Stack(const Stack& other) : N_(0), first_(NULL) {
//		printf("Copying stack\n");
		copy(other);
	}

	Stack& operator=(const Stack& other) {
//		printf("Assigning stack\n");
		if (&other == this) return *this;

		// Deallocate memory
		clear();

		// Copy elements
		copy(other);

		return *this;
	}
	
	void push(T item) {
		Node* oldfirst = first_;
		first_ = new Node(item);
		first_->next_ = oldfirst;
		N_++;
	}

	T pop() {
		if (isEmpty()) throw std::out_of_range("Stack is empty");
		T item = first_->item_;
		Node* oldfirst = first_;
		first_ = first_->next_;
		delete oldfirst;
		N_--;
		return item;
	}

	T peek() {
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
	}

	void copy(const Stack& other) {
		Node* current = other.first_;
		while (current != NULL) {
			push(current->item_);
			current = current->next_;
		}
	}
	
	int size() { return N_; }

	bool isEmpty() { return N_ == 0; }

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
		Node(T item) : item_(item), next_(NULL) {}

		T item_;
		Node* next_;
	};

	int N_;				// number of elements in stack
	Node* first_;		// pointer to top of stack
};