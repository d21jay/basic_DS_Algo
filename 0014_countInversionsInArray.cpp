#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
bool ascending (T a, T b) {
	return a <= b;
}

template <typename T>
int MergeAndCount(vector<T> &A, int l, int r, int m, bool (*cc)(T, T)) {
	T C[r - l  + 1];
	int a, b, c, count;
	a = l;
	b = m + 1;
	c = 0;
	count = 0;
	while(a <= m && b <= r) {
		if((*cc)(A[a], A[b])) {
			C[c] = A[a];
			a++;
		}
		else {
			C[c] = A[b];
			b++;
			count += (m - a + 1);
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
	return count;
}

/*counts num of inversions (A[i] > A[j] for i < j) in O(nlog(n)) time.*/
template <typename T>
int countInversions(vector<T> &A, int l, int r, bool (*cc)(T, T) = ascending<T>) {
	if((r - l) < 1) return 0;
	int m = (l + r)/2;
	int a = countInversions<T>(A, l, m);
	int b = countInversions<T>(A, m + 1, r);
	int c = MergeAndCount<T>(A, l, r, m, cc);
	return a + b + c;
}

int main() {
	string s;
	while(true) {
		
		vector<int> A;
		int num;
		cout<<"\n(you can exit with ctrl + c)"<<endl;
		cout<<"enter int array (space seperated) : "<<endl;
		getline(cin,s);
		stringstream ss(s);
		while (ss >> num) {
			A.push_back(num);
		}
		num = 0;
		num = countInversions(A, 0, A.size() - 1);
		cout<<"num of inversions (A[i] > A[j] for i < j)  = "<<num<<endl;
	}
	return 0;
}