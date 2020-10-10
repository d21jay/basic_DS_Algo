#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool** mat;

//O(n) fn to find sink if mat is already given.
int sink(int n) {
	int sink = 0;
	if(n <= 1) return 0;
	int k = 0;
	for(int i = 1; i < n; i++) {
		if(mat[k][i]) k = i;
	}
	sink = k + 1;
	for(int i = 0; i < n; i++) {
		if(i != k){
			if(mat[k][i] || !(mat[i][k])) {
				sink = 0;
				break;
			} 
		}
	} 
	return sink;
}

int main() {
	string s;
	int temp, n, vs;
	while(true) {
		cout<<"enter n x1 x2 x3 x4 ..., where n is no of vertices and edges are x1->x2, x3->x4 ... (1-based index). \n";
		cout<<"edges are directional.\n";
		vector<int> v;
		getline(cin, s);
		stringstream ss(s);
		while(ss>>temp) {
			v.push_back(temp);		
		}
		vs = v.size();
		if(vs > 0) {
			n = v[0];
			if(n > 0) {
				mat = new bool*[n];
				for(int i = 0; i < n; i++) {
					//initialize everything to false
					mat[i] = new bool[n]();
				}
				if(vs%2 == 0) vs--;
				for(int i = 1; i < vs; i += 2) {
					if(v[i] > 0 && v[i] <= n && v[i+1] > 0 && v[i+1] <= n)
						mat[v[i]-1][v[i+1]-1] = true;
				}
				cout<<"The graph: \n";
				for(int i = 0; i < n; i++){
					for(int j = 0; j < n; j++) cout<<(mat[i][j]? 1 : 0)<<' ';
					cout<<'\n';
				}
				temp = sink(n);
				if(temp) cout<<"The sink is: "<<temp<<endl;
				else cout<<"no sink"<<endl; 
			}
		}
		cout<<endl; 
	}
	return 0;
}