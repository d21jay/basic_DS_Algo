#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> A, iLog2, iPow2;
vector<vector<int>> mat;

/*
this fn constructs Range-Minima Data Structure in
 O(nlog(n)) space and O(nlog(n)) preprocessing time.
*/
void rangeMinimaDS() {
	for(int i = 1; i < A.size(); i = i * 2) iPow2[i] = i;
	int count = 0;
	iLog2[0] = -1; iPow2[0] = -1;
	for(int i = 2; i < A.size(); i++) {
		if(iPow2[i] != 0) count++;
		else iPow2[i] = iPow2[i-1];
		iLog2[i] = count;
	}
	for(int i = 0 ; i < A.size() - 1; i++) {
		vector<int> temp;
		mat.push_back(temp);
		if(A[i] < A[i+1]) mat[i].push_back(A[i]);
		else mat[i].push_back(A[i+1]);
	}
	int twok = 2; 
	for(int i = 1; i <= count; i++) {
		for(int j = 0; j < A.size() - twok; j++) {
			if(mat[j][i-1] < mat[j + twok/2][i-1]) mat[j].push_back(mat[j][i-1]);
			else mat[j].push_back(mat[j + twok/2][i-1]);
		}
		twok *= 2;
	}
	return;	 
}

/*
this fn does Range-Minima Query in O(1) time 
using Range-Minima DS
*/
int RMQ(int i, int j) {
	if(i == j) return A[i];
	int k = j - i;
	if(iPow2[k] == k) return mat[i][iLog2[k]];
	else {
		 return (mat[i][iLog2[k]] < mat[j-iPow2[k]][iLog2[k]])? mat[i][iLog2[k]] : mat[j-iPow2[k]][iLog2[k]];
	}	
}

int main() {
	string s;
	int i, j, t;
	bool done = false;
	char e;
	cout<<"enter int array (space seperated) : "<<endl;
	getline(cin,s);
	stringstream ss(s);
	while (ss >> i) {
		A.push_back(i);
		iLog2.push_back(0);
		iPow2.push_back(0);
	}
	cout<<"you entered : ";
	for (int k = 0; k<A.size(); k++) cout<<A[k]<<" ";
	cout<<endl;
	if(A.size()>0) {
		rangeMinimaDS();

		while(!done) {
			cout<<"enter index i : ";
			cin>>i;
			if(cin.fail()) cin.clear();
			cin.ignore(123, '\n');
			cout<<"enter index j : ";
			cin>>j;
			if(cin.fail()) cin.clear();
			cin.ignore(123, '\n');
			if(i < 0) i= 0;
			if(i >= A.size()) i = A.size() - 1;
			if(j < i) {
				t = j;
				j = i; 
 				i = t > 0? t : 0;
			}
			if(j >= A.size()) j = A.size() - 1;
			
			cout<<"minima from index "<<i<<" to "<<j<<" is "<<RMQ(i, j)<<endl;
			
			e = 'a';
			cout<<"query again (y/n): ";
			cin>>e;
			while(e != 'y' && e != 'n') {
				cout<<"(y/n) : ";
				cin>>e;
			}
			if(e == 'n') done = true;
			cin.ignore(123, '\n');
		}
	}

	return 0;
}