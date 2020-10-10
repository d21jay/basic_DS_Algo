#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>

using namespace std;

/*
if(S[i-1]>0): 	S[i] = S[i-1] + A[i];
else: 		S[i] = A[i]
*/

//this fn find first maxSum Sub-array & the maxSum in O(n) time and O(1) space.
//empty subarray allowed and would be first if maxSum is 0.
int maxSum(vector<int> &A){
	int maxS = 0;
	int l = 0;
	int r = -1;
	int temp = -1;
	for(int i = 1; i < A.size(); i++){
		if(A[i-1]> 0) A[i] += A[i-1];
	}
	for(int i = 0; i < A.size(); i++) {
		if (A[i]<0) temp = i;
		if (A[i]>maxS){
			maxS = A[i];
			l = temp + 1;
			r = i;
		} 
	}
	cout<<"first maxSum Sub-array : ";
	if(r == -1) cout<<"empty";
	else {
		cout<<A[l]<<" ";
		for (int i = l+1 ; i <= r; i++) {
			cout<<A[i] - A[i-1]<<" ";
		}	
	}
	cout<<endl;
	return maxS;
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
			i = maxSum(A);
			cout<<"max Sum = "<<i<<endl;
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