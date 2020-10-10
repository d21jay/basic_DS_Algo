#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> edge;
vector<int> bfn;
bool isBipartite;

//O(n)
void BFS(int node0 = 1, bool print = false){
	if(node0 < 1 || node0 > bfn.size()) node0 = 1;
	isBipartite = true;
	node0--;
	queue<int> q;
	q.push(node0);
	bfn[node0] = 0;
	int cl = 0;
	if(print) cout<<"BFS Tree: \n";
	while(!q.empty()) {
		node0 = q.front();
		q.pop();
		for(int i = 0; i < edge[node0].size(); i++) {
			if(edge[node0][i] != node0 + 1) {
				if(bfn[edge[node0][i]-1] == -1) {
					bfn[edge[node0][i]-1] = bfn[node0] + 1;
					q.push(edge[node0][i]-1);
				}
				/*The Bipartite checker. */
				/*The odd length cycle checker. */
				else if(bfn[edge[node0][i]-1] == bfn[node0]) isBipartite = false;
			}
		}
		if(print) {
			if(!(bfn[node0] == cl)){
				cout<<'\n';
				cl++;
			}
			cout<<node0 + 1<<' ';
		}
	}
	if(print) cout<<"\n";
	return;
}

int main() {
	string s;
	int temp, n, vs;
	while(true) {
		cout<<"enter n x1 x2 x3 x4 ..., where n is no of vertices and edges are x1<->x2, x3<->x4 ... (1-based index). \n";
		cout<<"edges are bi-directional.\n";
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
				edge = *(new vector<vector<int>> (n));
				bfn = *(new vector<int> (n, -1));
				if(vs%2 == 0) vs--;
				for(int i = 1; i < vs; i += 2) {
					if(v[i] > 0 && v[i] <= n && v[i+1] > 0 && v[i+1] <= n)
						edge[v[i]-1].push_back(v[i+1]);
						if(v[i+1] != v[i])
						edge[v[i+1]-1].push_back(v[i]);
				}
				cout<<"The graph edges: \n";
				for(int i = 0; i < n; i++){
					cout<<i + 1<<" :-> ";
					for(int j = 0; j < edge[i].size(); j++) cout<<edge[i][j]<<' ';
					cout<<'\n';
				}
				cout<<'\n'; 	
				BFS();
				if(isBipartite) {
					cout<<"is Bipartite.\nSet A : ";
					for(int i = 0; i < n; i++) {
						if(bfn[i]%2 == 0) cout<<i + 1<<' ';
					}
					cout<<"\nSet B : ";
					for(int i = 0; i < n; i++) {
						if(bfn[i]%2 != 0) cout<<i + 1<<' ';
					}
				}
				else cout<<"not Bipartite.\n";
				cout<<'\n'; 
			}
		}
		cout<<endl; 
	}
	return 0;
}