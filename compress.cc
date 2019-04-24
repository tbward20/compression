#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include "PriorityQueue.h"
// #include <PriorityQueue.h>
// typedef cs112::PriorityQueue PriorityQueue;
// typedef cs112::HuffmanTree HuffmanTree;

using namespace std;

typedef unsigned char byte;


int bit_str_to_byte(string bitstr) {
	// Convert string of 8 ones or zeros into an int that represents a single
	// character

	// This number will be the integer value of the character desired
	int ans = 0;

	// Multiplier that starts at the highest place value (2^8)
	int m = 128;

	// Add to answer if character is one and half the multiplier for every
	// "bit" in string
	for (size_t i = 0; i < 8; i++) {
		if (bitstr[i] == '1') ans += m;
		m /= 2;
	}
	return ans;
}

void make_pri_queue(PriorityQueue & q, int * o) {
	// Create a priority queue of HuffmanTree * from an array of char
	// frequencies

	// Step through array and check if there are any instances of a 
	// certain char. If so, enqueue a singleton HuffmanTree * with the char
	// and its frequency
	for (size_t i = 0; i < 256; i++) {
		if (o[i] > 0) {
			cout << (unsigned char)i << " space " << o[i] << endl;
			q.enqueue(new HuffmanTree((unsigned char)i, o[i]));
			//cout << "Is the heap is good? " << boolalpha << q.is_good_heap(0);
		}
	}
}

string make_bitstr(int c) {
	// Input is a character (as an int) output is a string of "bits" for the
	// binary encoding of the char.

	string bitstr = "";
	for (size_t i = 128; i > 0; i /= 2) {
		// If the remaining value of the char is greater than the value of the
		// place value, add a one and subtract that value
		if (c >= (int)i) {
			bitstr += "1";
			c -= i;
		}

		// Otherwise add a zero
		else {
			bitstr += "0";
		}
	}
	return bitstr;
}


void write_bit(char bit, ostream & out=cout) {
	// Buffers bits into blocks of 8 and writes them to output as a single
	// character
	// Input '1' or '0' or 'F' to flush at the end

	// This buffer manages incoming bits and writes to output if it 
	// becomes full
	static string buffer;

	// 'F' is the last value passed to this method for compression. It alerts
	// the buffer to output whatever is left to the output followed by enough
	// zeros to complete a byte.
	if (bit == 'F') {
		if (buffer.size() > 0) {

			// Fill buffer with more zeros till it can make a whole byte
			while (buffer.size() < 8 ){
				buffer += '0';
			}

			// Output
			out << (char)bit_str_to_byte(buffer);
			buffer = "";
		}
	}

	// Input is either a '1' or a '0'
	else {
		buffer += bit;

		// Only output if buffer full
		if (buffer.size() == 8) {
			out << (char)bit_str_to_byte(buffer);
			buffer = "";
		}
	}
}


void write_tree(HuffmanTree * tree, ostream & out) {
	// Function that writes a tree to output using the following method:
	// I : Internal node. This will be immediately followed by its left tree
	// L : Leaf node. Followed by its Value field (a character)

	// This case indicates a leaf
	if (tree->Left == NULL)
		out << 'L' << tree->Value;

	// Indicates an internal node. Outputs 'I' then recursively outputs left
	// then right subtrees
	else {
		out << 'I';
		write_tree(tree->Left, out);
		write_tree(tree->Right, out);
	}
}




HuffmanTree * make_huff_tree(PriorityQueue & q) {
	// Function that takes a PriorityQueue of HuffmanTree * and creates a 
	// single comprehensive HuffmanTree. Returns a pointer to this tree.

	// Continues until the only HuffmanTree in the queue is the final one
	while (q.length() != 1) {
		//cout << "Is the heap is good? " << boolalpha << q.is_good_heap(0);
		// Dequeues the two least significant nodes
		HuffmanTree * smaller = q.front(); q.dequeue();
		HuffmanTree * larger = q.front(); q.dequeue();

		// Creates a HuffmanTree with the recently dequeued Trees as children
		HuffmanTree * interior = new HuffmanTree('I', smaller->Freq + 
									larger->Freq, smaller, larger);

		// Places new HuffmanTree back in the queue	
		q.enqueue(interior);
	}

	// Return the final item in the queue
	return q.front();
}

HuffmanTree * decode_tree() {
	// Decodes a tree that is encoded using the method described above

	// Read in a character
	char c = cin.get();

	// Internal nodes propt recursive calls to create left and right subtrees
	if (c == 'I') {
		return new HuffmanTree(0, 0, decode_tree(), decode_tree());
	}
	else {
		// Acts as base case. If it is a leaf node read in next char and set
		// the new HuffmanTree value field to the letter
		c = cin.get();
		return new HuffmanTree(c, 0, NULL, NULL);
	}
}


void compute_codes(HuffmanTree * tree, string * codes, string code) {
	// Function to traverse a HuffmanTree generating paths to each character

	if (!tree->Left) {
		// If you reach a leaf set index corresponding to the int value of a
		// character as the code
		codes[tree->Value] = code;
	}
	else {
		// Continue traversal but add a '0' for the left path and a '1' for
		// the right.
		compute_codes(tree->Left, codes, code + '0');
		compute_codes(tree->Right, codes, code + '1');
	}
}


string end_of(string op) {
	// Function to compute whether the end of a file path is the run command
	// for the compress or uncompress executable.

	for (size_t i = 0; i < op.size() - 1; i++) {
		// If there is a '.' followed by a '/' return the rest of the path
		// as the name of the executable
		if (op[i] == '.' && op[i + 1] == '/') return op.substr(i + 2);
	}

	// If no call is made, return the original path and deal with it in main
	return op;
}

int main(int argc, char const *argv[])
{
	// The core of the uncompress and compress algorithms.

	// Check the operation to be performed by looking at the end of argv[0]
	string operation = argv[0];
	operation = end_of(operation);

	if (operation == "compress") {
		// Compression has been called. What follows is compress logic

		// Open input file.
		const char * in_file = argv[1];
		ifstream input(in_file);

		// Initialize array that will be filled with occurances of each char
		int occurances[256] = {};

		char ch;
		size_t byte_count = 0;

		// First pass of input file. Populates occurances array with number
		// of times each character appears and counts length of file (bytes)
		while (input.get(ch)) {
			unsigned char c = ch;
			occurances[c]++;
			byte_count++;
		}
		input.close();

		// Here we deal with an empty file by outputting nothing and returning
		if (byte_count == 0) {
			cout << "";
			return 1;
		}

		// We know there is at least one byte in this file so:

		// create PriorityQueue and fill it with singleton Huffmantrees of
		// letters and their occurances
		PriorityQueue q(256);
		make_pri_queue(q, occurances);

		// Build a HuffmanTree out of the PriorityQueue full of singleton
		// HuffmanTrees
		HuffmanTree * tree = make_huff_tree(q);

		// Create an array of strings to store the codes for each letter and
		// populate with path codes
		string codes[256] = {};
		compute_codes(tree, codes, "");

		// Output number of bytes originally in file and the encoding of the
		// HuffmanTree
		cout << byte_count;
		write_tree(tree, cout);

		// Second pass of input file to write the encoded paths as bits
		input.open(in_file);
		while(input.get(ch)) {
			unsigned char c = ch;

			// For each "bit" in the path code of each character, write it
			// to output using the buffer defined above to output single bytes
			for (size_t i = 0; i < codes[c].size(); i++)
				write_bit(codes[c][i], cout);
		}

		// Flush the buffer and close file again
		write_bit('F', cout);
		input.close();
	}
	else if (operation == "uncompress"){
		// uncompress has been called. What follows is uncompress logic.

		// If the file is empty output empty string and return
		// Cite: http://www.cplusplus.com/reference/istream/istream/peek/
		// How to look at char without removing it
		if (cin.peek() == EOF) {
			cout << "";
			return 1;
		}


		size_t size;
		char ch;
		string chars;
		string paths;

		// Read in number of bytes in original file
		cin >> size;

		// Create tree from encoding in compressed file
		HuffmanTree * tree = decode_tree();

		// Read all the rest of the characters and put them in a string
		while (cin.get(ch))
			chars += ch;

		// From that string generate a new string with the paths that each
		// char represented
		for (size_t i = 0; i < chars.size(); i++) {
			paths += make_bitstr((unsigned char)chars[i]);
		}

		// Traverse HuffmanTree until all chars found
		size_t j = 0;
		for (size_t i = 0; i < size; i++) {

			// Pointer starts at root
			HuffmanTree * p = tree;
			unsigned char letter = p->Value;

			// While loop continues until a letter is found
			while (letter == 0) {

				// p is set to either left or right subtree depending on path
				// value
				p = paths[j] == '0' ? p->Left : p->Right;
				letter = p->Value;
				j++;
			}
			cout << letter;
		}
	}

	// Case for if somehow neither compress nor uncompress is called
	else {
		cerr << "Program not called" << endl;
		exit(1);
	}
}
