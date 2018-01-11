#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <malloc.h>
using namespace std;

static string fileName = "input.txt";

class RandomStringGenerator {
public:
	RandomStringGenerator() {
		srand(time(NULL));
	}
	int generate(char str[], int length) {
		for (int i = 0; i<length; i++) {
			pos = rand() % 36;
			str[i] = alphaNumericChars[pos];
		}
		str[length] = '\0';
		return 0;
	}
private:
	int pos;
	char str[11];
	char alphaNumericChars[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
};


class RandomNumberGenerator {
public:
	RandomNumberGenerator() {
		srand(time(NULL));
	}
	int generate(int radix) {
		return rand() % radix;
	}
};

#define CNT_STR 1000000
#define CNT_TEST 10000

void generateRandomInputs() {
	int i;

	RandomStringGenerator rsg;
	RandomNumberGenerator rng;
	char str[12];


	FILE* fStr = fopen("str.txt", "w");
	FILE* fTest = fopen("test.txt", "w");

	int cnt = 0;
	fprintf(fStr, "%d\n", CNT_STR);
	fprintf(fTest, "%d\n", CNT_TEST);
	printf("Generating random numbers\n");
	for (i = 0; i<CNT_STR; i++) {
		rsg.generate(str, 11);
		fprintf(fStr, "%s\n", str);
		if (rng.generate(10) == 0) {
			if (cnt<CNT_TEST) {
				//memcpy(testStr[cnt++], str, sizeof(str));
				fprintf(fTest, "%s\n", str);
				cnt++;
			}
		}
	}
	fclose(fStr);
	fclose(fTest);
}

int equals(char a[], char b[]) {
	for (int i = 0; ; i++) {
		if (a[i] != b[i]) return 0;
		if (a[i] == '\0' && b[i] == '\0') break;
	}
	return 1;
}

typedef struct hash {
	struct hash* prev;
	struct hash* next;
	int key;
	char str[12];
	hash() {
		prev = '\0';
		next = '\0';
		key = -1;
		str[0] = '\0';;
	}
} HASH;

#define SIZE_HASHTABLE 10000
class HashTable
{
public:
	HashTable() {
	}
	~HashTable() {
		// TODO: delete allocated memory of arrHash
		for (int i = 0; i<SIZE_HASHTABLE; i++) {
			HASH* head = &arrHash[i];
			HASH* nodeDelete;
			while (head->next != '\0') {
				nodeDelete = head->next;
				if(nodeDelete->next != '\0') nodeDelete->next->prev = head;
				head->next = nodeDelete->next;
				delete nodeDelete;
			}
		}
	}
	int add(char str[]);
	HASH* find(char str[]);
	HASH arrHash[SIZE_HASHTABLE];
private:
	int calcKey(char str[]);
};

int HashTable::calcKey(char str[]) {
	int key = 0;
	if (str[0] != '\0' && str[1] != '\0') key = str[0]*str[1]%SIZE_HASHTABLE;
	else if (str[0] != '\0') key = str[0]*12345%SIZE_HASHTABLE;
	return key;
}

int HashTable::add(char str[]) {
	int key = calcKey(str);

	HASH* cur = &arrHash[key];
	HASH* newHash = new HASH();
	newHash->key = key;
	memcpy(newHash->str, str, 12);

	if (cur->next != '\0') cur->next->prev = newHash;
	newHash->prev = cur;
	newHash->next = cur->next;
	cur->next = newHash;

	return 0;
}

HASH* HashTable::find(char str[]) {
	int key = calcKey(str);

	HASH* cur = &arrHash[key];
	while (strcmp(cur->next->str, str) != 0) {
		cur = cur->next;
		_ASSERT(cur->key != -1);
	}
	return cur;
}

int main(int argc, char** argv)
{
	clock_t before;

	double timeElapsed;
	generateRandomInputs();

	int i = 0, j = 0;
	int totalCnt = 0;
	int testCnt = 0;
	HashTable* ht = new HashTable();

	freopen("str.txt", "r", stdin);
	scanf("%d", &totalCnt);
	char** strs = new char*[totalCnt];
	for (i = 0; i<totalCnt; i++) {
		strs[i] = new char[12];
		scanf("%s", strs[i]);
		ht->add(strs[i]);
	}
	
	freopen("test.txt", "r", stdin);
	scanf("%d", &testCnt);
	char** testStrs = new char*[testCnt];
	for (i = 0; i<testCnt; i++) {
		testStrs[i] = new char[12];
		scanf("%s", testStrs[i]);
	}

	printf("Search with full lookup\n");
	before = clock();
	// Basic search
	for (i = 0; i<testCnt; i++) {
		for (j = 0; j<totalCnt; j++) {
			if (equals(testStrs[i], strs[j]) == 1) {
				break;
			}
		}
	}
	timeElapsed = (double)(clock()-before)/CLOCKS_PER_SEC;
	printf("##Basic search\nelapsed time : %5.5f\n", timeElapsed);

	
	printf("Search with hash\n");
	before = clock();
	// hash search
	for (i = 0; i<testCnt; i++) {
		if(ht->find(testStrs[i]) == '\0') printf("%s\n", "Critical error!");
	}
	timeElapsed = (double)(clock()-before)/CLOCKS_PER_SEC;
	printf("##Hash search\nelapsed time : %5.5f\n", timeElapsed);

	for (i = 0; i<totalCnt; i++) delete[] strs[i];
	delete[] strs;

	for (i = 0; i<testCnt; i++) delete[] testStrs[i];
	delete[] testStrs;

	delete ht;

	return 0;
}
