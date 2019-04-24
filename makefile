all: compress uncompress

uncompress: compress
	ln -s compress uncompress

compress: compress.cc PriorityQueue.cc
	c++ -o compress compress.cc PriorityQueue.cc
