/*
	Exactly the same as num.cpp just add more '\n'
	to this file :)
*/

#include <map>
#include <set>
#include <list>
#include <stack>
#include <cmath>
#include <mutex>
#include <vector>
#include <memory>
#include <thread>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
ofstream fout ("result.out");
ofstream flog ("num.log");

static mutex mapLock;
static map<ostream *, unique_ptr<mutex> > streamLocks;


static map <int, vector <int> > factors;
static vector <int> result_abundant;
static vector <int> result_evil;
static vector <int> result_perfect;
static vector <int> result_happy;
static vector <int> result_primeval;
static vector <int> result_lucky;

const int PRIME_RANGE = 1000000;
const int MAX_RANGE = 1000000;
int Prime[PRIME_RANGE], cut = 0;
bool isnotprime[PRIME_RANGE + 100];

void Abundant_Number (int begin, int end);// Done
/*  This is the number that the sum of the factors is
	larger than the number itself
*/

void Perfect_Number (int begin, int end); //Done
/*  This is the number that the sum of its factors
	equals to itself
*/

void Happy_Number (int begin, int end); //Done
/*	This is god damn complex
	LINK: https://en.wikipedia.org/wiki/Happy_number
*/

void Lucky_Number (int begin, int end);
/*	This is also god damn complex
	LINK: https://en.wikipedia.org/wiki/Lucky_number
*/

void Evil_Number (int begin, int end); //Done
/*	This is the number is those who have even number
	of 1s in binary form
*/

void Primeval_Number (int begin, int end); //Done
/*  This is also god damn complex
	LINK: https://en.wikipedia.org/wiki/Primeval_number
*/

void Print_set (vector<int>& result, char* cat);
void Generate_Numbers (int begin, int end);
void Liner_prime_list (int begin, int end); //
void Div_factors (int begin, int end);
void Div_Prime_factors (int begin, int end);

inline int digit (int x);
inline string tostring (int x);
inline int toint (string& x);
inline string tobinary(int x);

ostream& oslock(ostream& os);
ostream& osunlock(ostream& os);
/*	multithread lock for "cout"
	FROM  Dev <<
	Thanks Dev for this genius oslock
*/

int main()
{
	ios_base::sync_with_stdio(false);
	int begin, end; cin >> begin >> end;
	Generate_Numbers (begin, end);
	fclose (stdin); fclose (stdin);
	return 0;
}
ostream& oslock(ostream& os) {
	ostream *ostreamToLock = &os;
	if (ostreamToLock == &cerr) 
		ostreamToLock = &cout;
	mapLock.lock();
	unique_ptr<mutex>& up = streamLocks[ostreamToLock];
	if (up == nullptr) 
		up.reset(new mutex);
	mapLock.unlock(); 
	up->lock();
	return os;
}

ostream& osunlock(ostream& os) {
	ostream *ostreamToLock = &os;
	if (ostreamToLock == &cerr) 
		ostreamToLock = &cout;
	mapLock.lock();
	auto found = streamLocks.find(ostreamToLock);
	mapLock.unlock();
	if (found == streamLocks.end())
		throw "unlock inserted into stream that has never been locked.";
	unique_ptr<mutex>& up = found -> second; up -> unlock();
	return os;
}
void Generate_Numbers (int begin, int end) {
	Liner_prime_list (1, PRIME_RANGE);
	Div_factors (begin, end);

	flog << "Initalized success .." << endl; flog.flush();

	thread perfectnumber(Perfect_Number, begin, end);
	thread abundantnumber(Abundant_Number, begin, end);
	thread evilnumber(Evil_Number, begin, end);
	thread happynumber(Happy_Number, begin, end);
	thread primevalnumber(Primeval_Number, begin, end);

	flog << "All five threads created success ... " << endl;
	flog.flush();

	perfectnumber.join(); abundantnumber.join();
	evilnumber.join(); happynumber.join();
	primevalnumber.join();

	flog << "all threads joined .. waiting for final result" << endl;
	flog.close();
}
inline string tobinary(int x) {
	string newstring;
	while (x) 
		newstring += tostring(x % 2), x = x >> 1;
	int len = newstring.size(); 
	string final_result;
	stringstream stream;
	for (int i = 0 ; i < len ; i ++) {
		stream << newstring[len - i - 1];
		stream.flush();
	} stream >> final_result; stream.clear();
	return final_result;
}
inline string tostring (int x) {
	stringstream stream; 
	stream << x;
	string get; 
	stream >> get;
	stream.clear(); 
	return get;
}
inline int toint (string& x) {
	stringstream stream; 
	stream << x;
	int get; 
	stream >> get;
	stream.clear(); 
	return get;
}
inline string& tostring(char x) {
	stringstream stream; 
	stream << x;
	string get; 
	stream >> get;
	stream.clear(); 
	return get;
}
inline int digit (int x) {
	stringstream stream;
	stream << x; 
	string getx;
	stream >> getx; 
	stream.clear();
	return getx.size();
}
void Print_set (vector<int>& result, char* cat) {
	fout << oslock << cat << "_Numbers " << endl;
	for (int get : result)
		fout << get << " ";
	fout << '\n' << "------------------" << endl << osunlock;
}
void Liner_prime_list (int begin, int end)
{
	isnotprime[1] = 1; isnotprime[0] = 1;
	for (int i = begin; i < end ; i ++) {
		if (!isnotprime[i]) 
			Prime[cut ++] = i;
		for (int j = 0; j < cut && Prime[j] * i < end; j ++) {
			isnotprime[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break;
		}
	}
}
void Div_factors (int begin, int end) {
	for (int i = begin; i < end; i ++) {
		vector <int> temp;
		for (int j = 1; j < i; j ++)
			if (i % j == 0) 
				temp.push_back(j);
		factors.insert (make_pair (i, temp));
	}
}
void Abundant_Number (int begin, int end)
{
	for (int i = begin, sum = 0; i < end; i ++) {
		auto cur = factors [i];
		for (int factor : cur) 
			sum += factor;
		if (sum > i) 
			result_abundant.push_back (i);
	}
	Print_set (result_abundant, "Abundant");
}
void Evil_Number (int begin, int end) {
	for (int i = begin; i < end; i ++) {
		int get = i, cut = 0;
		while (get) 
			get -= (get & (-get)), cut ++;
		if (!(cut & 1)) 
			result_evil.push_back(i);
	}
	Print_set (result_evil, "Evil");
}
void Perfect_Number (int begin, int end) {
	for (int i = begin; i < end; i ++) {
		int sum = 0; 
		auto cur = factors[i];
		for (int factor : cur) 
			sum += factor;
		if (sum == i) 
			result_perfect.push_back(i);
	}
	Print_set (result_perfect, "Perfect");
}
void Happy_Number (int begin, int end) {
	map <int, int> hash; stack <int> st;
	stringstream stream; hash[1] = 1;
	hash[2] = -1; hash[3] = -1; hash[4] = -1;
	hash[5] = -1; hash[6] = -1; hash[7] = 1;

	for (int i = begin; i < end; i ++) {
		if (hash.find(i) -> second == 1) {
			result_happy.push_back (i);
			continue;
		}
		int cur = i, flag = -1;
		while (true) {
			if (hash[cur] == -1) {
				flag = -1; 
				break;
			}
			if (hash[cur] == 1) {
				flag = 1; 
				break;
			}
			st.push(cur);
			stream << cur; 
			string get; 
			stream >> get;
			stream.clear(); 
			int sum = 0; 
			for (char ch : get)
				sum += (ch - '0') * (ch - '0'); 
			cur = sum;
		}
		while (!st.empty()) 
			hash[st.top()] = flag, st.pop();
		if (flag == 1)
			result_happy.push_back(i);
	}
	Print_set (result_happy, "Happy");
}
void Primeval_Number (int begin, int end) {
	result_primeval.push_back(1);
	result_primeval.push_back(2);
	set <int> prime_get; 
	int cut = 1;
	for (int i = 3; i < end; i ++) {
		string get = tostring(i);
		int len = get.size(), tot = (1 << len);
		for (int j = 1; j < tot; j ++) {
			string index = tobinary(j); 
			stringstream stream;
			stream << setw(len) << setfill('0') << index;
			index = stream.str(); 
			stream.clear(); 
			string getnew;
			for (int k = 0 ; k < index.size(); k ++)
				if (index[k] == '1')
					getnew += get[k];
			sort (getnew.begin(), getnew.end());
			do {
				int getnewnum = toint(getnew);
				if (!isnotprime[getnewnum]) 
					prime_get.insert(getnewnum);
			} while (next_permutation(getnew.begin(), getnew.end()));
		}
		int cur = prime_get.size(); 
		prime_get.clear();
		if (cur > cut) 
			cut = cur, result_primeval.push_back(i);
	}
	Print_set (result_primeval, "Primeval");
} 
