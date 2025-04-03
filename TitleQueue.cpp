#include "TitleQueue.h"

// init queue empty
TitleQueue::TitleQueue() : front(0) {}

bool TitleQueue::checkempty() {
	return front >= data.size(); //	return true when queue empty or  opposite
}

void TitleQueue::push(int value) {
	data.push_back(value);
}

// take first element and it remove
int TitleQueue::pop() {
	if (checkempty()) return -1;
	return data[front++];
}

// only watch and not remove
int TitleQueue::peek() {
	if (checkempty()) return -1;
	return data[front];
}
