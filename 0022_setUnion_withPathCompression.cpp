#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

int find(vector<vector<int>> &A, int i) {
	if(A[0][i] == i) return i;
	else {
		int j = find(A, A[0][i]);
		
		//The Hero step.
		//The path compressor.
		A[0][i] = j;
		
		return j;
	}
}

bool sameSet(vector<vector<int>> &A, int i, int j) {
	return (find(A, i) == find(A, j));
}

void unionSet(vector<vector<int>> &A, int i, int j) {
	int k = find(A, i);
	int l = find(A, j);
	if (l == k) return;

	if(A[1][k] > A[1][l]) {
		A[1][k] += A[1][l];
		A[1][l] = 0;
		A[0][l] = k;	
	}
	else{
		A[1][l] += A[1][k];
		A[1][k] = 0;
		A[0][k] = l;
	}
	return;
}

void printSet(vector<vector<int>> &A) {
	cout<<"\nelement_# : ";
	for(int i = 0; i< A[0].size(); i++) {
		cout<<setw(2)<<i<<' ';
	}
	cout<<"\nparent_id : ";
	for(int i = 0; i< A[0].size(); i++) {
		cout<<setw(2)<<A[0][i]<<' ';
	}
	cout<<"\n#_members : ";
	for(int i = 0; i< A[0].size(); i++) {
		cout<<setw(2)<<A[1][i]<<' ';
	}
	cout<<endl;
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(0, 30);
	string s;
	int n, k, j;
	while(true) {
		n = 5 + dist(gen);
		vector<vector<int>> A(2, vector<int>(n, 1));
		for(int i = 0; i<n; i++){
			A[0][i] = i;
		}
		//A[0] is parent. A[1] is size.

		cout<<">>> The original sets :";
		printSet(A);

		for(int i = 0; i < 2; i++){
			for(int l = 0; l < 5; l++) {
				j = dist(gen) % n;
				k = dist(gen) % n;
				unionSet(A, j, k);
				cout<<"\nunion of elements "<<j<<" and "<<k<<" :";
				printSet(A);
			}
			j = dist(gen) % n;
			k = dist(gen) % n;
			cout<<"\nelement "<<j<<" & element "<<k<<" belongs to same set? : "<<(sameSet(A,j,k)? "true" : "false")<<endl;
			cout<<"situation after this step :";
			printSet(A);
			j = dist(gen) % n;
			cout<<"\nroot of element "<<j<<" is : "<<find(A, j)<<endl;
			cout<<"situation after this step :";
			printSet(A);
		}
		
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}