// Baejun online judge #1927
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

/* TODO
코딩은 마쳤음
그런데 0, 1이 출력된 후 FC가 발생하여 종료됨
인덱스 처리에 문제가 있어 보임. 디버깅 중
*/
int min(int a, int b) {
	if (a<b) return a;
	else return b;
}

static const int MAX_HEAP_SIZE = 1000;
class Heap {
public:
	Heap();
	~Heap() {};
	virtual int insertValue(int _value) = 0;
	virtual int popRootValue() = 0;

protected:
	int mHeapArray[MAX_HEAP_SIZE] = { 0 };
	int mElementCnt;	// indicate next position to insert
};

Heap::Heap() {
	mElementCnt = 1;
	mHeapArray[MAX_HEAP_SIZE] ;
}

class MinHeap : Heap {
public:
	MinHeap() {};
	~MinHeap() {};
	int insertValue(int _val);
	int popRootValue();
};

int MinHeap::insertValue(int _val) {
	int temp; int childNodeId; int parentNodeId;

	if (mElementCnt > MAX_HEAP_SIZE) return -1;

	mHeapArray[mElementCnt] = _val;
	if (mElementCnt == 1) {
		mElementCnt++;
		return 1;
	}
	
	childNodeId = mElementCnt;
	while (1) {
		parentNodeId = childNodeId/2;
		if (mHeapArray[parentNodeId] > mHeapArray[childNodeId]) {
			temp = mHeapArray[parentNodeId];
			mHeapArray[parentNodeId] = mHeapArray[childNodeId];
			mHeapArray[childNodeId] = temp;
		}
		if (parentNodeId == 1) break;
		childNodeId /= 2;
	}
	mElementCnt++;
	return 1;
}

int MinHeap::popRootValue() {
	int res = mHeapArray[1]; int temp = 0;
	int parentNodeId; int leftChildNodeId; int rightChildNodeId; int childNodeIdToSwitch;
	int lastNodeId;

	if (res == 0) return 0;
	if (mElementCnt == 1) return res;
	else if (mElementCnt < 1) {
		printf("ERROR:1\n");
		return 0;	// error case
	}

	lastNodeId = --mElementCnt;
	mHeapArray[1] = mHeapArray[lastNodeId];
	mHeapArray[lastNodeId] = 0;
	
	parentNodeId = mHeapArray[1];

	while (1) {
		leftChildNodeId = parentNodeId*2; rightChildNodeId = parentNodeId*2+1;
		if ((mHeapArray[leftChildNodeId] > 0 && mHeapArray[parentNodeId] < mHeapArray[leftChildNodeId])
			&& (mHeapArray[rightChildNodeId] > 0 && mHeapArray[parentNodeId] < mHeapArray[rightChildNodeId])) {
			childNodeIdToSwitch = min(parentNodeId*2, parentNodeId*2+1);
		}
		else if (mHeapArray[leftChildNodeId] > 0 && mHeapArray[parentNodeId] < mHeapArray[leftChildNodeId]) {
			childNodeIdToSwitch = leftChildNodeId;
		}
		else if (mHeapArray[rightChildNodeId] > 0 && mHeapArray[parentNodeId] < mHeapArray[rightChildNodeId]) {
			childNodeIdToSwitch = rightChildNodeId;
		}
		else break;

		temp = mHeapArray[parentNodeId];
		mHeapArray[parentNodeId] = mHeapArray[childNodeIdToSwitch];
		mHeapArray[childNodeIdToSwitch] = temp;
		parentNodeId = childNodeIdToSwitch;
	}
	return res;
}

int main()
{
	int cnt = 0; int i = 0; int input = 0; int output = 0;
	freopen("heap_array_input.txt", "r", stdin);
	scanf("%d", &cnt);

	MinHeap mh;
	for (i = 0; i<cnt; i++) {
		scanf("%d", &input);
		if (input != 0) mh.insertValue(input);
		else {
			output = mh.popRootValue();
			printf("%d\n", output!=0?output:0);
		}
	}

	return 0;
}