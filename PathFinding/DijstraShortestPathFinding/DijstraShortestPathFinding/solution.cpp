#include <stdio.h>

static const int MAX_HEAP_SIZE = 100001;

class MinHeap
{
public:
	MinHeap();
	int push(int _val);
	int pop();
	int isEmpty();
	int mSize;
	int mHeap[MAX_HEAP_SIZE];
};

MinHeap::MinHeap() {
	mSize = 0;
	for (int i = 0; i<MAX_HEAP_SIZE; i++) {
		mHeap[i] = 0;
	}
}

int MinHeap::isEmpty(){
	if (mSize == 0) return 1;
	return 0;
}

int MinHeap::push(int _val) {
	if (++mSize >= MAX_HEAP_SIZE) return -1;
	
	int child = mSize; int parent = child / 2;
	while (child != 1 && _val < mHeap[parent]) {
		mHeap[child] = mHeap[parent];
		child = parent; parent = child / 2;
	}
	mHeap[child] = _val;

	return 1;
}

int MinHeap::pop() {
	int item = mHeap[1]; 
	int temp = mHeap[mSize]; mHeap[mSize--] = 0;

	int parent = 1, child = 2;
	while (child <= mSize) {
		if (mHeap[child] > 0 && mHeap[child+1]>0 && mHeap[child] > mHeap[child+1]) child = child + 1;
		if (mHeap[child] > temp) break;
		mHeap[parent] = mHeap[child];
		parent = child; child *= 2;
	}
	mHeap[parent] = temp;

	return item;
}

int main() {
	int nodeCnt = 0; int i = 0; int input = 0; int output = 0;
	freopen("input.txt", "r", stdin);
	scanf("%d", &nodeCnt);

	MinHeap* mh = new MinHeap();
	for (i = 0; i<nodeCnt; i++) {
		scanf("%d", &input);
		if (input > 0) mh->push(input);
		else {
			if (mh->isEmpty()) printf("0\n");
			else printf("%d\n", mh->pop());
		}
	}
	delete mh;
	return 0;
}