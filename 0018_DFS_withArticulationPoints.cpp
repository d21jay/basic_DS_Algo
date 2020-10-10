#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> edge;
vector<int> DFN;
vector<int> high_pt;
vector<int> parent;
vector<bool> articulation_pt;
int n;
bool ap;
//n+1 will be infinity.
int dfn;
int root, root_childs;

void DFS(int node){
	DFN[node] = dfn++;
	for(int i = 0; i < edge[node].size(); i++) {
		int w = edge[node][i] - 1;
		if(w != node) {
			if(DFN[w] == -1){
				if(node == root) root_childs++;
				parent[w] = node;
				DFS(w);
				high_pt[node] = high_pt[node] > high_pt[w] ? high_pt[w] : high_pt[node];
				if(high_pt[w] >= DFN[node]) {
					//root with only one child should not be ap.
					if(node != root || root_childs > 1) {
						articulation_pt[node] = true;
						ap = true;
					}
				}
			}
			else if(parent[node] != w) {
				high_pt[node] = high_pt[node] > DFN[w] ? DFN[w] : high_pt[node];
			}
		}
	}
	return;
}

//O(n)
void DFStraversal() {
	dfn = 0;
	for(int i = 0; i<n; i++){
		root = i;
		root_childs = 0;
		if(DFN[i] == -1) DFS(i);
	}
	return;
}

int main() {
	string s;
	int temp, vs;
	while(true) {
		n = 0;
		ap = false;
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
				DFN = *(new vector<int> (n, -1));
				high_pt = *(new vector<int> (n, n+1));
				parent = *(new vector<int> (n, -1));
				articulation_pt = *(new vector<bool> (n, false));
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
				DFStraversal();
				if(!ap) cout<<"no articulation points.";
				else {
					cout<<"articulation points: ";
					for(int i = 0; i < n; i++)
						if(articulation_pt[i]) cout<<i + 1<<' ';
				}
				cout<<'\n'; 
			}
		}
		cout<<endl; 
	}
	return 0;
}