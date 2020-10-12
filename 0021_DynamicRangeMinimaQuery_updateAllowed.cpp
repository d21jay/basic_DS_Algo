#include <iostream>
#include <vector>
#include <random>

using namespace std;

void constructRMQTree(vector<int> &values, vector<int> &binTree) {
	int n = values.size();
	int n2 = 1;
	while(n2 < n) n2 *= 2;
	for (int i = 0; i < n2-1; i++) {
		binTree.push_back(0);
	}
	for(int i = 0; i< n; i++) {
		binTree.push_back(values[i]);
	}
	for(int i = n2 - 2; i >= 0; i--) {
		if(2*i + 1 < binTree.size()){
			binTree[i] = binTree[2*i + 1];
			if(2*i + 2 < binTree.size() && binTree[i] > binTree[2*i + 2])
				binTree[i] = binTree[2*i + 2]; 
		}
	}
	return;
}

int RMQ(vector<int> &binTree, int n2, int i, int j) {
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
	int ans = binTree[i];
	if(j > i) {
		ans = ans <= binTree[j] ? ans : binTree[j];
		while((i - 1)/2 != (j -1)/2) {
			if(i % 2 == 1) ans = ans <= binTree[i+1] ? ans : binTree[i+1];
			if(j % 2 == 0) ans = ans <= binTree[j-1] ? ans : binTree[j-1];
			i = (i - 1)/2;
			j = (j - 1)/2;
		}
	}
	return ans;
}

void update(vector<int> &binTree, int n2, int j, int val) {
	if(j < 0 || j > (binTree.size() - n2)) return; 
	j = n2 - 1 + j;
	binTree[j] = val;
	while(j > 0) {
		j = (j-1)/2;
		binTree[j] = binTree[2*j + 1];
		if(2*j + 2 < binTree.size() && binTree[j] > binTree[2*j + 2])
			binTree[j] = binTree[2*j + 2];
		
	}
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
		constructRMQTree(A, binTree);
		cout<<"RMQ Tree :\n";
		printByLevel(binTree);
		int n2 = binTree.size() - A.size() + 1;
		for(int i = 0; i < 5;  i++){
			j = dist(gen)%n;
			k = j + dist(gen)%(n-j);
			cout<<"\nRMQ from index "<<j<<" to index "<<k<<" is "<<RMQ(binTree, n2, j, k)<<'\n';

			ind = dist(gen)%n;
			j = dist(gen)%n;
			k = j + dist(gen)%(n-j);
			num = dist(gen);
			update(binTree, n2, ind, num);
			cout<<"\nRMQ Tree after updating index "<<ind<<" to value "<<num<<" :\n";
			printByLevel(binTree);
			cout<<"\nRMQ from index "<<j<<" to index "<<k<<" is "<<RMQ(binTree, n2, j, k)<<'\n';
		}
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}