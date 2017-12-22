// Baejun online judge #1927
#include <iostream>

static const int MAX_HEAP_SIZE = 1000;
class Heap {
public:
	Heap() {};
	~Heap() {};
	virtual int insertValue(int _value) = 0;
	virtual int popRootValue() = 0;

protected:
	int HeapArray[MAX_HEAP_SIZE];
	int cntElement;
	int getLeft(int _node_id);
	int getRight(int _node_id);
	int getParent(int _node_id);
};

Heap::Heap() {
	cntElement = 0;
	HeapArray[MAX_HEAP_SIZE] = { -1, };
}

class MinHeap :Heap {
public:
	int insertValue(int _val);
	int popRootValue();
};

int MinHeap::insertValue(int _val) {
	int res = 0; int temp = 0;
	this->HeapArray[this->cntElement] = _val;
	int checkNode = cntElement;
	while (1) {
		if (HeapArray[checkNode/2] > HeapArray[checkNode]) {
			temp = HeapArray[checkNode/2];
			HeapArray[checkNode/2] = HeapArray[checkNode];
			HeapArray[checkNode] = temp;
		}
		if (checkNode/2 == 0) break;
		checkNode /= 2;
		// TODO: if max depth exists, add escape condition and return -1
	}

	return res;
}

int min(int a, int b) {
	if (a<b) return a;
	else return b;
}

int MinHeap::popRootValue() {
	int res = HeapArray[0]; int temp = 0;
	HeapArray[0] = HeapArray[cntElement];
	int parentId = 0; int childId = 0;
	while (1) {
		if ((HeapArray[parentId*2] > 0 && cntElement >= parentId*2)
			&& (HeapArray[parentId*2+1] > 0 && cntElement >= parentId*2+1)) {
			childId = min(parentId*2, parentId*2+1);
		}
		else if (HeapArray[parentId*2] > 0 && cntElement >= parentId*2) {
			childId = parentId*2;
		}
		else if (HeapArray[parentId*2+1] > 0 && cntElement >= parentId*2+1) {
			childId = parentId*2+1;
		}
		else break;

		if (HeapArray[parentId]>HeapArray[childId]) {
			temp = HeapArray[parentId];
			HeapArray[parentId] = HeapArray[childId];
			HeapArray[childId] = temp;
			parentId = childId;
		}
	}
	return res;
}

int main()
{
	freopen("heap_array_input.txt", "r", stdin);

	return 0;
}