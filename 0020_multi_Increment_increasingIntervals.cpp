#include <iostream>
#include <vector>
#include <random>

using namespace std;

void constructBinTree(vector<int> &values, vector<int> &binTree) {
	int n = values.size();
	int n2 = 1;
	while(n2 < n) n2 *= 2;
	for (int i = 0; i < n2-1; i++) {
		binTree.push_back(0);
	}
	for(int i = 0; i< n; i++) {
		binTree.push_back(values[i]);
	}
	return;
}

void multiIncrement(vector<int> &binTree, int n2, int i, int j, int diff) {
	int temp; 
	if(i > j){
		temp = i;
		i = j;
		j = temp;
	}
	if(i < 0) i = 0;
	if(j > (binTree.size() - n2)) j = binTree.size() - n2 - 1; 
	i = n2 - 1 + i;
	j = n2 - 1 + j;
	binTree[i] += diff;
	if(j > i) {
		binTree[j] += diff;
		while((i - 1)/2 != (j -1)/2) {
			if(i % 2 == 1) binTree[i + 1] += diff;
			if(j % 2 == 0) binTree[j - 1] += diff;
			i = (i - 1)/2;
			j = (j - 1)/2;
		}
	}
	return;
}

int report(vector<int> &binTree, int n2, int i) {
	int val = 0;
	i = n2 - 1 + i;
	if(i < n2 - 1 || i >= binTree.size()) return 0;
	while(i > 0) {
		val = val + binTree[i];
		i = (i - 1) / 2;
	}

	val += binTree[0];
	//redundant step as binTree[0] will always be 0;
	//this is due to nature of multiIncrement func.

	return val;
}

void compress(vector<int> &binTree, int n2, int i, int j) {
	int temp; 
	if(i > j){
		temp = i;
		i = j;
		j = temp;
	}
	if(i < 0) i = 0;
	i = n2 - 1 + i;
	j = n2 - 1 + j;
	if(j >= binTree.size()) j = binTree.size() - 1;
	for(int k = 0; k < n2 -1 ; k++) {
		if(2*k + 1 < binTree.size()) binTree[2*k + 1] += binTree[k];
		if(2*k + 2 < binTree.size()) binTree[2*k + 2] += binTree[k];
		binTree[k] = 0; 
	}
}

vector<int> multiReportWithCompression(vector<int> &binTree, int n2, int i, int j){
	compress(binTree, n2, i, j);
	vector<int> ans = *(new vector<int>);
	for(int k = i; k <= j; k++) {
		ans.push_back(binTree[k]);
	}
	return ans;
}

vector<int> multiReport(vector<int> &binTree, int n2, int i, int j) {
	int temp; 
	if(i > j){
		temp = i;
		i = j;
		j = temp;
	}
	if(i < 0) i = 0;
	if(j > (binTree.size() - n2)) j = binTree.size() - n2 - 1;
	int ilogn = 0;
	int k = 1;
	while(k < n2) {
		k *= 2;
		ilogn++;	
	}
	if((j - i + 1)*(ilogn + 1) >= 2*binTree.size()) {
		return multiReportWithCompression(binTree, n2, i, j);		
	}
	vector<int> ans = *(new vector<int>);
	for(int k = i; k <= j; k++) ans.push_back(report(binTree,n2,k));
	return ans; 
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
	int n, num, ind, k, j;
	while(true) {
		vector<int> A;
		vector<int> binTree;
		n = 8 + (dist(gen))%25;
		cout<<"Actual array : ";
		for(int i = 0; i < n; i++) {
			num = dist(gen);
			A.push_back(num);
			cout<<num<<' ';
		}
		cout<<'\n';
		constructBinTree(A, binTree);
		int n2 = binTree.size() - A.size() + 1;
		for(int i = 0; i < 5;  i++){
			j = dist(gen)%n;
			k = j + dist(gen)%(n-j);
			num = dist(gen);
			multiIncrement(binTree, n2, j, k, num);
			cout<<"\nafter increasing "<<num<<" from index "<<j<<" to index "<<k<<'\n';
			printByLevel(binTree);
			j = dist(gen)%n;
			cout<<"reporting value at index "<<j<<" : "<<report(binTree,n2,j)<<endl;
		}
		compress(binTree, n2, 0, n-1);
		cout<<"\nafter compression of tree :\n";
		printByLevel(binTree);
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}