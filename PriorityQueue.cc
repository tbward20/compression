#include <cassert>
#include <cstdlib>
#include "PriorityQueue.h"
using namespace std;


	typedef unsigned char byte;

	HuffmanTree::HuffmanTree(byte value, size_t freq, 
						HuffmanTree* left, HuffmanTree* right) {
		Value = value; Freq = freq; Left = left; Right = right;
	}
	bool HuffmanTree::operator< (const HuffmanTree & other) const {
		return Freq < other.Freq;
	}

	typedef HuffmanTree* ItemTy;
	
	
	// Purpose: Constructor
	//
	// Pre: None
	// Post: An empty priority queue of given capacity is created
	PriorityQueue::PriorityQueue(size_t capacity) {
		_size = 0;
		_capacity = capacity;
		heap_ary = new ItemTy[capacity];
		for (size_t i = 0; i < _capacity; i++)
			heap_ary[i] = NULL;
	}

	// Purpose: Destructor
	//
	// Pre: None.
	// Post: All memory associated with the queue has been freed.
	PriorityQueue::~PriorityQueue() {
		while (_size > 0) {
			dequeue();
		}
		delete [] heap_ary;
	}

	// Purpose: Returns the number of items in the queue
	//
	// Pre: None.
	// Post: The number of items in the queue is returned.
	size_t PriorityQueue::length() const {
		return _size;
	}


	// Purpose: Adds an item to the end of the queue
	//
	// Pre: The queue is not full.
	// Post: The item is inserted at the end of the queue.
	void PriorityQueue::enqueue(const ItemTy& item) {
		assert(_size < _capacity);
		heap_ary[_size] = item;
		_reheap_up(_size);
		_size++;
	}

	// Purpose: Removes an item from the front of the queue
	//
	// Pre: The queue is not empty.
	// Post: The front item in the queue is removed.
	void PriorityQueue::dequeue() {
		assert(!empty());
		heap_ary[0] = heap_ary[_size - 1];
		_size--;
		_reheap_down(0);
	}

	// Purpose: Inspect the front item in the queue.
	//
	// Pre: The queue is not empty.
	// Post: The item at the front of the queue is returned.
	ItemTy PriorityQueue::front() const {
		assert(!empty());
		return heap_ary[0];
	}

	// Purpose: Determines if the queue is full
	//
	// Pre: None.
	// Post: If the queue contains the maximum capacity of items true 
	// is returned. Otherwise, false.
	bool PriorityQueue::full() const {
		return _size == _capacity;
	}
	
	// Purpose: Determines if the queue is empty
	//
	// Pre: None.
	// Post: If the queue contains items, false is returned. Otherwise, 
	// true.
	bool PriorityQueue::empty() const {
		return _size == 0;
	}

	// Purpose: Helper for enqueue that organizes the heap properly
	//
	// Pre: Same as enqueue.
	// Post: Heap is in proper order
	void PriorityQueue::_reheap_up(size_t pos) {
		// If position is the root of the tree stop
		if (pos == 0) return;
		ItemTy parent = heap_ary[(pos - 1) / 2];
		cout << "Freq at pos: " << heap_ary[pos]->Freq << endl;
		cout << "Freq at parent: " << heap_ary[(pos - 1) / 2]->Freq << endl;
		// Determine if two positions need to switch to maintain the heap. 
		// If so, make the switch.
		if (heap_ary[pos]->Freq < parent->Freq) {
			cout << "Swapping" << endl;
			ItemTy temp = parent;
			heap_ary[(pos - 1) / 2] = heap_ary[pos];
			heap_ary[pos] = temp;
			_reheap_up((pos - 1) / 2);
		}
		else {
			return;
		}
	}


	// Purpose: Get left child of a given position
	//
	// Pre: None.
	// Post: Return the value at the position of a left child
	ItemTy PriorityQueue::left_child(size_t pos) {
		// If the child would ve at a position larger than the number of
		// items in the heap return NULL otherwise return the value of the
		// child
		return (pos * 2 + 1 > _size) ? NULL : heap_ary[pos * 2 + 1];
	}


	// Purpose: Get right child of a given position
	//
	// Pre: None.
	// Post: Return the value at the position of a right child
	ItemTy PriorityQueue::right_child(size_t pos) {
		// If the child would ve at a position larger than the number of
		// items in the heap return NULL otherwise return the value of the
		// child
		return (pos * 2 + 2 > _size) ? NULL : heap_ary[pos * 2 + 2];
	}


	bool PriorityQueue::is_good_heap(size_t pos) {
		for (size_t i = 0; i < _capacity; i++) {
			if (heap_ary[i] == NULL && i < _size){ cout << "failed: null \
				before size reached" << endl; return false;}
			if (heap_ary[i] != NULL && i >= _size && i < _capacity){ cout << 
				"failed: non null after size wtf how idiot" << endl;
				return false;}
			if ((left_child(i) && heap_ary[i] < left_child(i)) || 
				(right_child(i) && heap_ary[i] < right_child(i))){ cout << 
				"failed: 1 or more children > parent" << endl;return false;}
		}
		return true;
	}


	// Purpose: Helper for dequeue that organizes the heap properly
	//
	// Pre: Same as dequeue.
	// Post: Heap is in proper order
	void PriorityQueue::_reheap_down(size_t pos) {
		//cout << "Reheap down " << pos << endl;

		// If position represents a leaf
		if (!left_child(pos)) return;

		// Boolean flag to keep track of whether the left or right child is
		// smaller. Initially set to left.
		bool left = true;
		ItemTy child = left_child(pos);

		// First checks whether a right child exists, if so, checks whether it
		// is smaller than the left child
		if (right_child(pos) && right_child(pos) < child) {

			// If right child is smaller update which child will be compared
			// to root position and update boolean flag.
			left = false;
		    child = right_child(pos);
		}

		// Compare the smaller of a roots children to the root. If it is smaller
		// swap the two indices
		if (child < heap_ary[pos]) {
		    ItemTy temp = heap_ary[pos];
		    heap_ary[pos] = child;

		    // Uses left boolean flag to determine whether to add 2 or 1 to 
		    // arrive at correct child position
		    heap_ary[pos * 2 + (left ? 1 : 2)] = temp;
		    _reheap_down(pos * 2 + (left ? 1 : 2));
		}
		else {
		    return; 
		}


	}