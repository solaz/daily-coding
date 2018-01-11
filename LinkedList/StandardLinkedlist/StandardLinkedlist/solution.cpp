#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Item {
	int data;
	struct Item* next;
	struct Item* prev;
	Item() {
		data = 0;
		next = NULL;
		prev = NULL;
	}
	Item(int data_) {
		data = data_;
	}
	void setData(int data_) {
		data = data_;
	}
} stItem;

class BasicLinkedlist {
public:
	stItem* root;
	stItem* tail;

	BasicLinkedlist() {
		root = new stItem;
		tail = new stItem;
		root->next = tail;
		root->prev = NULL;
		tail->prev = root;
		tail->next = NULL;
	}
	~BasicLinkedlist() {
		stItem* node; stItem* temp;
		while (root->next != tail) {
			node = root->next;
			root->next = root->next->next;
			root->next->prev = root;
			temp = node;
			delete temp;
			node = node->next;
		}
		delete root;
		delete tail;
	}

	void addNode(stItem* newItem) {
		root->next->prev = newItem;
		newItem->next = root->next;
		root->next = newItem;
		newItem->prev = root;
	}
	void removeNode() {
		stItem* node;
		node = root->next;
		root->next = root->next->next;
		root->next->prev = root;
		delete node;
	}
	void printNode() {
		stItem* node = root->next;
		while (true) {
			if (node == tail) {
				printf("end\n");
				break;
			}
			else {
				printf("%d ", node->data);
			}
			node = node->next;
		}
	}
};

#define N_MAX_USER 1000
BasicLinkedlist* bll;

int main()
{
	bll = new BasicLinkedlist();

	stItem* node;
	node = new stItem(1);
	bll->addNode(node);
	node = new stItem(3);
	bll->addNode(node);
	node = new stItem(2);
	bll->addNode(node);
	node = new stItem(4);
	bll->addNode(node);
	node = new stItem(5);
	bll->addNode(node);
	
	bll->printNode();
	delete bll;

	return 0;
}

