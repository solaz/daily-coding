// Baejun online judge #1927
#include <stdio.h>

int min(int a, int b) {
	if (a<b) return a;
	else return b;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

static const int MAX_HEAP_SIZE = 100005;

class MinHeap {
public:
	MinHeap();
	int isEmpty();
	void push(int _val);
	int pop();

protected:
	int mSize;
	int mHeap[MAX_HEAP_SIZE];
};

MinHeap::MinHeap() {
	mSize = 0;
	for (int i = 0; i<MAX_HEAP_SIZE; i++) {
		mHeap[i] = 0;
	}
}

int MinHeap::isEmpty() {
	if (mSize == 0) return 1;
	return 0;
}

void MinHeap::push(int _val) {
	int i;
	i = ++mSize;

	while (i != 1 && _val < mHeap[i/2]) {
		mHeap[i] = mHeap[i/2];
		i /= 2;
	}
	mHeap[i] = _val;
}

int MinHeap::pop() {
	int parent, child, item, temp;

	item = mHeap[1];

	temp = mHeap[mSize]; mHeap[mSize--] = 0;
	parent = 1; child = 2;

	while (child <= mSize) {
		if (mHeap[child] > 0 && mHeap[child+1] > 0
			&& mHeap[child] > mHeap[child+1]) {
			child = child+1;
		}
		if (mHeap[child] > temp) break;
		mHeap[parent] = mHeap[child];
		parent = child; child *= 2;
	}
	mHeap[parent] = temp;

	return item;
}

int main()
{
	int nodeCnt = 0; int i = 0; int input = 0; int output = 0;
	scanf("%d", &nodeCnt);

	MinHeap* mh = new MinHeap();
	for (i = 0; i<nodeCnt; i++) {
		scanf("%d", &input);
		if (input > 0) mh->push(input);
		else {
			if(mh->isEmpty()) printf("0\n");
			else printf("%d\n", mh->pop());
		}
	}
	delete mh;
	return 0;
}