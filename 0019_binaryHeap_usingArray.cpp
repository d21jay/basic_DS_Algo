#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <random>

using namespace std;

/*
for a heap in array.
 i.e. 0 based :
if parent node is j :
	left child = [2j + 1];
	right child = [2j + 2];
if child node is j :
	parent = |_(j-1)/2_|;
*/

//O(n). comes with calculting value of c * n * <Sum_{1 : log(n)}> (i/(2^i)).

void heapify(vector<int> &A) {
	for(int i = A.size()/2 - 1; i >= 0; i--) {
		int j = i;
		bool done = false;
		int temp = A[j];
		while(!done) {
			done = true;
			if(2*j + 1 < A.size()) {
				int k;
				if(2*j + 2 < A.size())
					k = A[2*j + 1] < A[2*j +2] ? 2*j + 1 : 2*j + 2;
				else k = 2*j + 1;
				if(A[k] < A[j]) {
					done = false;
					A[j] = A[k];
					A[k] = temp;
					j = k;			
				}
			}
		}
	}
	return;
}

//O(1)
int min(vector<int> &A) {
	if(A.size() > 0) return A[0];
	else return INT_MAX;
}

//O(log(n))
int extract_min(vector<int> &A) {
	int ans = INT_MAX;
	if(A.size() > 0) {
		ans = A[0];
		A[0] = A[A.size() - 1];
		A.pop_back();
		int j = 0;
		bool done = false;
		int temp = A[j];
		while(!done) {
			done = true;
			if(2*j + 1 < A.size()) {
				int k;
				if(2*j + 2 < A.size())
					k = A[2*j + 1] < A[2*j +2] ? 2*j + 1 : 2*j + 2;
				else k = 2*j + 1;
				if(A[k] < A[j]) {
					done = false;
					A[j] = A[k];
					A[k] = temp;
					j = k;
				}
			}
		}
	}
	return ans;
}

//O(log(n))
void insert(vector<int> &A, int num) {
	A.push_back(num);
	bool done = false;
	int k;
	k = A.size() - 1;
	while(!done && k > 0 ) {
		if(A[k] < A[(k-1)/2]){
			A[k] = A[(k-1)/2];
			A[(k-1)/2] = num;
			k = (k-1)/2;	 
		}
		else done = true;
	}
	return;
}

void decIndexBy(vector<int> &A, int j, int diff);

//O(log(n))
void incIndexBy(vector<int> &A, int j, int diff) {
	if(diff<0) {
		decIndexBy(A, j, (-1)*diff);
		return;
	}
	if(j < 0 || j >= A.size()) return;
	A[j] = A[j] + diff;
	bool done = false;
	int temp = A[j];
	while(!done) {
		done = true;
		if(2*j + 1 < A.size()) {
			int k;
			if(2*j + 2 < A.size())
				k = A[2*j + 1] < A[2*j +2] ? 2*j + 1 : 2*j + 2;
			else k = 2*j + 1;
			if(A[k] < A[j]) {
				done = false;
				A[j] = A[k];
				A[k] = temp;
				j = k;			
			}
		}
	}
	return;
}

//O(log(n))
void decIndexBy(vector<int> &A, int j, int diff) {
	if(diff<0) {
		incIndexBy(A, j, (-1)*diff);
		return;
	}
	if(j < 0 || j >= A.size()) return;
	A[j] = A[j] - diff;
	bool done = false;
	int temp = A[j];
	while(!done && j > 0 ) {
		if(A[j] < A[(j-1)/2]){
			A[j] = A[(j-1)/2];
			A[(j-1)/2] = temp;
			j = (j-1)/2;	 
		}
		else done = true;
	}
	return;
}

vector<int> mergeHeap(vector<int> &A, vector<int> &B) {
	vector<int> C;
	for(int i = 0; i < A.size(); i++) C.push_back(A[i]);
	for(int i = 0; i < B.size(); i++) C.push_back(B[i]);
	heapify(C);
	return C;
}

void printByLevel(vector<int> &A) {
	int i = 2;
	for(int j = 0; j < A.size(); j++){
		if(j == i-1) {
			cout<<'\n';
			i *= 2;
		}
		cout<<A[j]<<' ';
	}
	cout<<'\n';
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(1, 999);
	string s;
	int n, num, ind;
	while(true) {
		vector<int> A;
		n = 7 + (dist(gen))%25;
		cout<<"Actual array : ";
		for(int i = 0; i < n; i++) {
			num = dist(gen);
			A.push_back(num);
			cout<<num<<' ';
		}
		cout<<'\n';
		heapify(A);
		printByLevel(A);
		cout<<"\nmin : "<<min(A)<<endl;
		extract_min(A);
		cout<<"\nafter extracting min from heap :\n";
		printByLevel(A);
		num = dist(gen);
		insert(A, num);
		cout<<"\nafter inserting "<<num<<" to heap :\n";
		printByLevel(A);
		num = dist(gen);
		ind = (dist(gen))%n;
		incIndexBy(A, ind, num);
		cout<<"\nafter increasing index "<<ind<<" by "<<num<<" :\n";
		printByLevel(A);
		num = dist(gen);
		ind = (dist(gen))%n;
		decIndexBy(A, ind, num);
		cout<<"\nafter decreasing index "<<ind<<" by "<<num<<" :\n";
		printByLevel(A);
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}