// Baekjoon online judge #1991
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef struct node {
	char data;
	struct node* left;
	struct node* right;
	int level;
	node() {
		init();
	}
	node(char _d) {
		init();
		data = _d;
	}
	void init() {
		data = '\0';
		left = NULL;
		right = NULL;
	}
} Node;

class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();

	Node* getRoot();
	Node* search(char _d);
	void destroyTree();
	void insert(char _p, char _l, char _r);

private:
	Node* root;
	int maxLevel;
	Node* search(char _d, Node* _leaf);
	void destroyTree(Node* _leaf);
};

BinaryTree::BinaryTree() {
	root = NULL;
	maxLevel = 0;
}

BinaryTree::~BinaryTree() {
	destroyTree(root);
}

Node* BinaryTree::getRoot() {
	return root;
}

void BinaryTree::insert(char _p, char _l, char _r)
{
	if(root == NULL) {
		root = new Node(_p);
		root->level = 1;
		maxLevel = 1;
	}

	Node* parent = search(_p);
	if (parent == NULL) {
		std::cout << "CRITICAL ERROR" << std::endl;
		return;
	}

	if (_l != '.') {
		parent->left = new Node(_l);
		parent->left->level = parent->level + 1;
		if (maxLevel < parent->left->level) maxLevel = parent->left->level;
	}

	if (_r != '.') {
		parent->right = new Node(_r);
		parent->right->level = parent->level + 1;
		if (maxLevel < parent->right->level) maxLevel = parent->right->level;
	}
}

Node* BinaryTree::search(char _d, Node* _leaf) {
	Node* node = NULL;
	if (_d == _leaf->data) return _leaf;

	if (_leaf->left != NULL) {
		node = search(_d, _leaf->left);
		if (node != NULL) return node;
	}

	if (_leaf->right != NULL) {
		node = search(_d, _leaf->right);
		if (node != NULL) return node;
	}

	return NULL;
}

Node* BinaryTree::search(char _d) {
	return search(_d, root);
}

void BinaryTree::destroyTree(Node* _leaf) {
	if (_leaf->left != NULL) destroyTree(_leaf->left);
	if (_leaf->right != NULL) destroyTree(_leaf->right);
	delete _leaf;
}

void BinaryTree::destroyTree() {
	destroyTree(root);
}

void preOrder(Node* _leaf) {
	std::cout << _leaf->data;
	if (_leaf->left != NULL) preOrder(_leaf->left);
	if (_leaf->right != NULL) preOrder(_leaf->right);
}

void inOrder(Node* _leaf) {
	if (_leaf->left != NULL) inOrder(_leaf->left);
	std::cout << _leaf->data;
	if (_leaf->right != NULL) inOrder(_leaf->right);
}

void postOrder(Node* _leaf) {
	if (_leaf->left != NULL) postOrder(_leaf->left);
	if (_leaf->right != NULL) postOrder(_leaf->right);
	std::cout << _leaf->data;
}

int main()
{
	int i = 0;
	int cnt = 0;
	BinaryTree* bt = new BinaryTree();
	char p; char l; char r;

	freopen("input.txt", "r", stdin);
	scanf("%d", &cnt);

	for (i = 0; i<cnt; i++) {
		scanf(" %c %c %c ", &p, &l, &r);
		bt->insert(p, l, r);
	}

	preOrder(bt->getRoot()); std::cout << std::endl;
	inOrder(bt->getRoot()); std::cout << std::endl;
	postOrder(bt->getRoot()); std::cout << std::endl;

	delete(bt);

	return 0;
}
