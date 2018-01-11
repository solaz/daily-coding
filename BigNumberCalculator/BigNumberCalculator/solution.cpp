#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#define MAX_LENGTH 64

using namespace std;

class bigint
{
public:
	bigint() {
		memset(num, 0, sizeof(int)*MAX_LENGTH);
		length = 0;
	}
	bigint(string _in) {
		memset(num, 0, sizeof(int)*MAX_LENGTH);
		length = _in.length();
		for (int i = length-1; i>=0; i--) {
			num[length-1-i] = (int)_in[i]-(int)'0';
		}
	}
	bigint operator+(bigint _bi2);
	bigint operator-(bigint _bi2);
	bigint operator*(bigint _bi2);
	bigint operator/(bigint _bi2);
	int calc_length();
	void print(bigint* _bi);
	bool is_same(bigint _bi);

	int num[MAX_LENGTH];
	int length;
protected:

};

bool bigint::is_same(bigint _bi)
{
	bigint* comp_value = &_bi;
	if (comp_value->length != this->length) return false;
	for (int i = 0; i<comp_value->length; i++) {
		if (comp_value->num[i] != this->num[i]) return false;
	}
	
	return true;
}

void bigint::print(bigint* _bi)
{
	for (int i = _bi->length-1; i>=0; i--) {
		printf("%d", _bi->num[i]);
	}
}

int bigint::calc_length() {
	int length = 0;
	for (int i = MAX_LENGTH-1; i>=0; i--) {
		if (this->num[i] < 0) {
			length = -1;
			break;
		}
		if (this->num[i] > 0) {
			length = i+1;;
			break;
		}
	}
	this->length = length;
	return length;
}

int max(int _a, int _b)
{
	if (_a>=_b) return _a;
	else return _b;
}

bigint bigint::operator+(bigint _bi2)
{
	bigint ans;
	bigint* bi1 = this;
	bigint* bi2 = &_bi2;
	int length = max(bi1->length, bi2->length);

	for (int i = 0; i<length; i++) {
		ans.num[i] += (bi1->num[i] + bi2->num[i]);
		if (ans.num[i] >= 10) {
			ans.num[i] -= 10;
			ans.num[i+1] += 1;
		}
	}
	ans.calc_length();

	print(bi1); printf("+"); print(bi2); printf("="); print(&ans); printf("\n");
	return ans;
};

bigint bigint::operator-(bigint _bi2)
{
	bigint ans;
	bigint* bi1 = this;
	bigint* bi2 = &_bi2;

	if (bi1->length < bi2->length) {
		ans.length = -1;
		return ans;
	}

	for (int i = 0; i < bi1->length; i++) {
		ans.num[i] = bi1->num[i] - bi2->num[i];
		if (ans.num[i] < 0) {
			ans.num[i] += 10;
			ans.num[i+1] -= 1;
		}
	}

	ans.calc_length();
	print(bi1); printf("-"); print(bi2); printf("="); print(&ans); printf("\n");

	return ans;
};

bigint bigint::operator*(bigint _bi2)
{
	bigint ans;
	bigint* bi1 = this;
	bigint* bi2 = &_bi2;
	int temp;

	for (int i = 0; i < bi1->length; i++) {
		for (int j = 0; j < bi2->length; j++) {
			temp = bi1->num[i] * bi2->num[j];

			ans.num[i+j] += temp % 10;
			if (ans.num[i+j] >= 10) {
				ans.num[i+j] -= 10;
				ans.num[i+j+1] += 1;
			}

			ans.num[i+j+1] += temp / 10;
			if (ans.num[i+j+1] >= 10) {
				ans.num[i+j+1] -= 10;
				ans.num[i+j+2] += 1;
			}

		}
	}

	ans.calc_length();
	print(bi1); printf("*"); print(bi2); printf("="); print(&ans); printf("\n");
	return ans;
};

string int_to_str(long long int lli)
{
	long long int level = 1;
	long long int divisor = 1;
	string num = "";
	while (1) {
		divisor *= 10;
		num = (char)((char)((lli%divisor)/(divisor/10))+(char)'0') + num;
		if (lli / divisor == 0) break;
	}
	return num;
}

bigint bigint::operator/(bigint _bi2)
{
	bigint* bi1 = this;
	bigint* bi2 = &_bi2;
	bigint temp1, temp2;
	bigint temp3, temp4;

	long long int jump = 10;

	for (int i = 0; i<(bi1->length-bi2->length); i++) {
		jump *= 10;
	}
	long long int step = jump;

	while (1) {
		temp1 = int_to_str(jump);
		temp2 = int_to_str(jump+1);
		step /= 2;

		temp3 = (*bi1)-temp2*(*bi2);
		temp4 = (*bi1)-temp1*(*bi2);

		if (temp3.length == -1 && temp4.length != -1) break;
		if (temp3.length == -1 && temp4.length == -1) {
			jump = jump - step;
			continue;
		}
		if (temp3.length != -1 && temp4.length != -1) {
			jump = jump + step;
			continue;
		}

	}
	
	return bigint(int_to_str(jump));
};

int main(int argc, char** argv)
{
	int i;
	int answer;
	string no1;
	string no2;

	//freopen("input.txt", "r", stdin);

	no1 = "9999999999999999999999";
	no2 = "9999999";
	answer = 0;

	bigint bi1(no1);
	bigint bi2(no2);
	bigint res;
	

	bigint bi3;
	bi3 = bi1 + bi2;

	bigint bi4;
	bi4 = bi1 - bi2;

	bigint bi5("99999989999999999999990000001");
	res = bi1 * bi2;
	if(res.is_same(bi5)) printf("-->CORRECT!\n");
	else printf("-->INCORRECT!");

	bigint bi6("1000000100000010");
	res = bi1 / bi2;
	if (res.is_same(bi6)) printf("-->CORRECT!\n");
	else  printf("-->INCORRECT!");

	return 0;
}