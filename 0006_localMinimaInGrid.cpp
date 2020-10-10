#include <iostream>
#include <sstream>

using namespace std;

int** mat;
int hl, hr, vl, vr;
int si, sj;

//this fn finds local minima in grid in O(n).
void localMinima() {
	int hm = (hl + hr)/2;
	int vm = (vl + vr)/2;
	for(int i = 0; i < (hr - hl); i++){
		if(mat[vm][hl+i]<mat[si][sj]) {
			si = vm; sj = hl+i;
		}
		if(mat[vl+i][hm]<mat[si][sj]) {
			si = vl+i; sj = hm;
		}
	}
	bool isMinima = true;
	if(isMinima && sj != hl && mat[si][sj-1] < mat[si][sj]){
		isMinima = false;
		sj = sj-1;
	}
	if(isMinima && sj != hr && mat[si][sj+1] < mat[si][sj]){
		isMinima = false;
		sj = sj+1;
	}
	if(isMinima && si != vl && mat[si-1][sj] < mat[si][sj]){
		isMinima = false;
		si = si-1;
	}
	if(isMinima && si != vr && mat[si+1][sj] < mat[si][sj]){
		isMinima = false;
		si = si+1;
	}
	if(!isMinima){	
		if(si>vm) vl = vm + 1;
		else vr = vm - 1;
		if(sj>hm) hl = hm + 1;
		else hr = hm - 1;
		localMinima();
	}
	return;
}

int main() {
	int n,n2,temp,c;
	string s;
	cout<<"enter n for n * n matrix : ";	
	cin>>n;
	while(cin.fail() || n<1){
		cin.clear();
		getchar();
		cout<<"pos int n only : ";
		cin>>n; 	
	}
	getchar();
	n2 = n*n; 
	cout<<"enter "<<n2<<" space seperated int elem of matrix: "<<"\n";
	cout<<"(if less elem are entered remaining would be 0. extra elem would be ignored.)"<<endl;
	getline(cin,s);
	stringstream ss(s);
	mat = new int*[n];
	for(int i = 0; i<n; i++){
		mat[i] = new int[n];
		for(int j = 0; j<n; j++) mat[i][j] = 0;
	}
	c = 0;
	while(ss>>temp && c<n2){
		mat[c/n][c%n] = temp;
		c++;
	}
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout<<mat[i][j]<<'\t';
		}
		cout<<endl;
	}
	if(n>0) {
		hl = 0; hr = n-1; vl = 0; vr = n-1;
		si = 0, sj = 0;
		localMinima();
		cout<<"local minima '"<<mat[si][sj]<<"' found at index "<<si<<", "<<sj<<"\n (0 based indices)"<<endl;
	} 
	cout<<"press enter to exit"<<endl;
	getchar();
	return 0;
}