#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

typedef unsigned char byte;
// Comment these lines out when own Priority Queue developed
#include<PriorityQueue.h> // Bailey's PriorityQueue
typedef cs112::PriorityQueue PriorityQueue;
typedef cs112::HuffmanTree HuffmanTree;

using namespace std;

// int bit_str_to_byte(string bitstr) {
// 	// int c = 0;
// 	// while (bitstr.size() > 0) {
// 	// 	int num = atoi("" + bitstr[0]);
// 	// 	cout << "num is " << num;
// 	// 	c += (num * pow(2, bitstr.size()));
// 	// 	bitstr = bitstr.substr(1);
// 	// }
// 	// return c;
// 	int ans = 0;
// 	int m = 128;
// 	for (size_t i = 0; i < 8; i++) {
// 		if (bitstr[i] == '1') ans += m;
// 		//cout << "answer: " << (char)ans;

// 		m /= 2;
// 	}
// 	return ans;
// }

// void make_pri_queue(PriorityQueue & q, int * o) {
// 	for (size_t i = 0; i < 256; i++) {
// 		if (o[i] > 0) {
// 			q.enqueue(new HuffmanTree((char)i, o[i]));
// 		}
// 	}
// }

// string make_bitstr(int c) {
// 	string bitstr = "";
// 	for (size_t i = 128; i > 0; i /= 2) {
// 		if (c >= (int)i) {
// 			bitstr += "1";
// 			c -= i;
// 		}
// 		else {
// 			bitstr += "0";
// 		}
// 	}
// 	return bitstr;
// }


// void write_bit(char bit, ostream & out=cout) {
// 	static string buffer;
// 	if (bit == 'F') {
// 		if (buffer.size() > 0) {
// 			while (buffer.size() < 8 ){
// 				buffer += '0';
// 				//cout << buffer << endl;
// 			}
// 			out << (char)bit_str_to_byte(buffer);
// 			buffer = "";
// 		}
// 	}
// 	else {
// 		buffer += bit;
// 		//cout << buffer << endl;
// 		if (buffer.size() == 8) {
// 			//cout << "flushing" << (char)bit_str_to_byte(buffer);
// 			out << (char)bit_str_to_byte(buffer);
// 			buffer = "";
// 		}
// 	}
// }


// void write_tree(HuffmanTree * tree, ostream & out) {
// 	if (tree->Left == NULL)
// 		out << 'L' << tree->Value;
// 	else {
// 		out << 'I';
// 		write_tree(tree->Left, out);
// 		write_tree(tree->Right, out);
// 	}
// }




// HuffmanTree * make_huff_tree(PriorityQueue & q) {
// 	// take top two nodes of q and make a new node with the smaller 
// 	//as the left tree and the larger as the right tree put that new 
// 	// node back in the queue;
// 	while (q.length() != 1) {
// 		HuffmanTree * smaller = q.front(); q.dequeue();
// 		HuffmanTree * larger = q.front(); q.dequeue();
// 		HuffmanTree * interior = new HuffmanTree('I',smaller->Freq +
//												 larger->Freq, 
// 								   smaller, larger);	
// 		q.enqueue(interior);
// 	}
// 	return q.front();
// }



// //compute_codes(root, codes, "");
// void compute_codes(HuffmanTree * tree, string * codes, string code) {
// 	if (!tree->Left) {
// 		codes[tree->Value] = code;
// 	}
// 	else {
// 		compute_codes(tree->Left, codes, code + '0');
// 		compute_codes(tree->Right, codes, code + '1');
// 	}
// }



/*
• a function that reads the entire contents of a file and determines 
its size and counts the frequencies of
all characters


//• a function that creates a byte from a string containing eight '1' or 
'0' characters (a bit-string)


//• a function that creates a bit-string from a byte


• a function that takes a bit-string of arbitrary length, buffers the bits 
 into blocks of 8, and outputs the binary encoding of a character


• a function that reads a single “bit” from a file (using buffering)


• a function that builds a single Huffman tree from a queue of Huffman trees


• a function that builds an array of string encodings from a Huffman tree


• a function that reads all uncompressed characters from a file and 
generates 
compressed character output


• a function that outputs the character representation of a Huffman tree


• a function that creates a Huffman tree by reading a character
 representation
 of the tree


• a function that uncompresses a stream of characters using a Huffman tree


• a function that determines if the program has been invoked correctly and 
determines whether to compress
or uncompress


~acampbel/compress FILENAME
~acampbel/compress FILENAME | hexdump -C
~acampbel/compress -b FILENAME
*/

void uncompress()
{
	// const char * in_file = argv[1];
	// int occurances[256] = {};
	// ifstream input(in_file);
	// char ch;
	// size_t byte_count = 0;
	// while (input.get(ch)) {
	// 	unsigned char c = ch;
	// 	occurances[c]++;
	// 	byte_count++;
	// }
	// input.close();

	// PriorityQueue q(256);
	// make_pri_queue(q, occurances);
	// HuffmanTree * tree = make_huff_tree(q);
	// string codes[256] = {};
	// compute_codes(tree, codes, "");
	// input.open(in_file);
	// cout << byte_count;
	// write_tree(tree, cout);
	// while(input.get(ch)) {
	// 	unsigned char c = ch;
	// 	for (size_t i = 0; i < codes[c].size(); i++)
	// 		write_bit(codes[c][i], cout);
	// }
	// write_bit('F', cout);
	 int size;
	 cin >> size;
	 cout << size;
}















// int * get_occurances(const char * in, size_t & size) 
// {
// 	ifstream in_file(in);
// 	char ch;
// 	int occurances[256];
// 	while (in_file.get(ch)) {
// 		cout << ch;
// 		occurances[ch]++;
// 		size++;
// }

// int main(int argc, char const *argv[])
// {
// 	const char * to_compress = argv[1];
// 	string out_file = string(to_compress) + ".z";
// 	ofstream outf(out_file.c_str());
// 	size_t size = 0;
// 	int occurances[256];
// 	ifstream in_file(in);
// 	char ch;
// 	int occurances[256];
// 	while (in_file.get(ch)) {
// 		cout << ch;
// 		occurances[ch]++;
// 		size++;
// 	outf << size;
// 	cout << size << endl;
// 	for (size_t i = 0; i < 256; i++) {
// 		cout << occurances[i] << endl;
// 	}


// }