#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>

using namespace std;

//this fn finds a local minima in log(n).
//elem equal to both neigh is also local minima;
int lMinima(vector<int> &A){
	int n = A.size();
	if(n == 0) return 0;
	int l = 0;
	int r = n-1;
	int m = (l+r)/2;
	while(true) {
		if(m == 0) {
			if(A[0]>A[1]) {
				l = 1;
				m = (l+r)/2;
			}
			else return 0;
		}
		else if(m == n-1) {
			if(A[m]>A[m-1]) {
				r = m-1;
				m = (l+r)/2;	
			}
			else return m;
		}
		else {
			if(A[m]>A[m-1] || A[m]>A[m+1]) {
				if(A[m-1]>A[m+1]) l = m+1;
				else r = m -1;
				m = (l+r)/2;
			}
			else return m;
		}
	}
}

int main() {
	string s;
	int i;
	bool done = false;
	char e;
	while(!done) {
		vector<int> A;
		cout<<"enter int array (space seperated) : "<<endl;
		getline(cin,s);
		stringstream ss(s);
		while (ss >> i) {
			A.push_back(i);
		}
		cout<<"you entered : ";
		for (int j = 0; j<A.size(); j++) cout<<A[j]<<" ";
		cout<<endl;
		if(A.size()>0) {
			i = lMinima(A);
			cout<<"local minima "<<A[i]<<" found at index "<<i<<endl;
		}
		e = 'a';
		cout<<"exit (y/n): ";
		cin>>e;
		while(e !='y' && e != 'n') {
			cout<<"(y/n) : ";
			cin>>e;
		}
		if(e == 'y') done = true;
		cin.ignore(123, '\n');
	}
	sleep(1);
	return 0;
}