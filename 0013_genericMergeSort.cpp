#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
bool ascending (T a, T b) {
	return a <= b;
}

template <typename T>
void Merge(vector<T> &A, int l, int r, int m, bool (*cc)(T, T)) {
	T C[r - l  + 1];
	int a, b, c;
	a = l;
	b = m + 1;
	c = 0;
	while(a <= m && b <= r) {
		if((*cc)(A[a], A[b])) {
			C[c] = A[a];
			a++;
		}
		else {
			C[c] = A[b];
			b++;
		}
		c++;
	}
	while(a <= m) {
		C[c] = A[a];
		a++; c++;
	}
	while(b <= r) {
		C[c] = A[b];
		b++; c++;
	}
	for(int i = 0; i < (r - l + 1); i++) {
		A[l + i] = C[i];
	}
	return;
}

//O(nlog(n))
template <typename T>
void MergeSort(vector<T> &A, int l, int r, bool (*cc)(T, T) = ascending<T>) {
	if((r - l) < 1) return;
	int m = (l + r)/2;
	MergeSort<T>(A, l, m);
	MergeSort<T>(A, m + 1, r);
	Merge<T>(A, l, r, m, cc);
	return;
}

int main() {
	string s;
	while(true) {
		
		//using merge sort on int
		
		vector<int> A;
		int num;
		cout<<"(you can exit with ctrl + c)"<<endl;
		cout<<"enter int array (space seperated) : "<<endl;
		getline(cin,s);
		stringstream ss(s);
		while (ss >> num) {
			A.push_back(num);
		}
		MergeSort<int>(A, 0, A.size()-1);
		for (int i = 0; i < A.size(); i++){
			cout<<A[i]<<' ';
		}
		cout<<endl;
		

		//using merge sort on chars
		
		vector<char> B;
		char c;
		cout<<"enter character array (no space. spaces & tabs would be counted) : "<<endl;
		getline(cin,s);
		ss.clear();
		ss.str(s);
		while (ss >> c) {
			B.push_back(c);
		}
		MergeSort<char>(B, 0, B.size()-1);
		for (int i = 0; i < B.size(); i++){
			cout<<"'"<<B[i]<<"'";
		}
		cout<<endl;


		//fun with strings

		vector<string> C;
		string s2;
		cout<<"enter string array (space seperated) : "<<endl;
		getline(cin,s);
		ss.clear();
		ss.str(s);
		while (ss >> s2) {
			C.push_back(s2);
		}
		MergeSort<string>(C, 0, C.size()-1);
		for (int i = 0; i < C.size(); i++){
			cout<<C[i]<<' ';
		}
		cout<<endl;
	}
	return 0;
}