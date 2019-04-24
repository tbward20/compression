#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <iostream>
#include <cstdlib>
using namespace std;

class HuffmanTree {
	 public:
	  typedef unsigned char byte;

	  // Purpose: Constructor
	  // 
	  // Pre:  None
	  // Post: A Huffman tree is created
	  HuffmanTree(byte value, size_t freq, HuffmanTree* left = NULL,
	              HuffmanTree* right = NULL);

	  // Purpose: Comparison operator (<)
	  //
	  // Pre:  None
	  // Post: If this tree's frequency is less than other's, return true, 
	  //       otherwise return false.
	  bool operator < (const HuffmanTree& other) const;
	  HuffmanTree* Left;
	  HuffmanTree* Right;
	  byte Value;
	  size_t Freq;
	};

class PriorityQueue {
  public:

    typedef HuffmanTree* ItemTy;

    // Purpose: Constructor
    //
    // Pre:  None
    // Post: An empty priority queue of given capacity is created
    PriorityQueue(size_t capacity);

    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator = (const PriorityQueue& other);


    // Purpose: Destructor
    //
    // Pre:  None.
    // Post: All memory associated with the queue has been freed.
    ~PriorityQueue();

    // Purpose: Returns the number of items in the queue
    //
    // Pre:  None.
    // Post: The number of items in the queue is returned.
    size_t length() const;

    // Purpose: Adds an item to the end of the queue
    //
    // Pre:  The queue is not full.
    // Post: The item is inserted at the end of the queue.
    void enqueue(const ItemTy& item);

    // Purpose: Removes an item from the front of the queue
    //
    // Pre:  The queue is not empty.
    // Post: The front item in the queue is removed.
    void dequeue();

    // Purpose: Inspect the front item in the queue.
    //
    // Pre:  The queue is not empty.
    // Post: The item at the front of the queue is returned.
    ItemTy front() const;

    // Purpose: Determines if the queue is full
    //
    // Pre:  None.
    // Post: If the queue contains the maximum capacity of items true is 
    //       returned. Otherwise, false.
    bool full() const;

    // Purpose: Determines if the queue is empty
    //
    // Pre:  None.
    // Post: If the queue contains items, true is returned. Otherwise, 
    // false.
    bool empty() const;
  bool is_good_heap(size_t p);
    void display(std::ostream& s=cout) const;

 private:
  ItemTy * heap_ary;
  void _reheap_up(size_t pos);
  void _reheap_down(size_t pos);
  ItemTy left_child(size_t pos);
  ItemTy right_child(size_t pos);
  size_t _size;
  size_t _capacity;
};

// Unoverloaded output operator
std::ostream& operator << (std::ostream& s, const PriorityQueue& queue);

#endif