#pragma once
#include <vector>

using namespace std;

class TitleQueue {
private:
	vector<int> data;
	int front;
public:
	// init Queue and set up queue is empty
	TitleQueue();

	// check queue has empty or not 
	bool checkempty();

	// add value into queue
	void push(int value);

	// take first element out of the queue
	int pop();

	// only watch not remove first element
	int peek();

};