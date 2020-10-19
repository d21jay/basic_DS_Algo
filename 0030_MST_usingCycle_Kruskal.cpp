#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

/* finds MST of graph in O(ElogV).
Kruskal's algo works better on sparse graph.
no need of heap. setUnion at its core.
Prim's works better on dense graph;
*/
vector<bool> inMST;
vector<vector<int>> selected;
vector<vector<int>> sortedEdges;
vector<vector<int>> MSTN;

vector<vector<vector<int>>> edges;
int V;

//This is union set algo to maintain sets of MSTs for graph having multiple connected components.
//Also it helps in CYCLE detection.
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
//Union-set algo ends---

bool cc2(vector<int> &a, vector<int> &b) {
	return a[2] < b[2];
}

void kruskalMST() {
	if(V == 0) return;
	selected.clear();
	inMST = *(new vector<bool>(V, false));
	sortedEdges = *(new vector<vector<int>>);
	MSTN = *(new vector<vector<int>>(2));
	for(int i = 0; i < V; i++) {
		MSTN[0].push_back(i);
		MSTN[1].push_back(1);
		//MSTN[0] is set-parent. MSTN[1] is set size if it is root.
		for(int j = 0; j < edges[i].size(); j++) {
			sortedEdges.push_back({i, edges[i][j][0] - 1, edges[i][j][1]});
		}
	}
	sort(sortedEdges.begin(), sortedEdges.end(), cc2);
	int u, v;
	for(int i = 0; i < sortedEdges.size(); i++) {
		u = sortedEdges[i][0];
		v = sortedEdges[i][1];
		if(inMST[u] && inMST[v]) {
			//if edge forms cycle u and v must be in same set.
			if(sameSet(MSTN, u, v)) continue;
			else {
				selected.push_back({u, v});
				unionSet(MSTN, u, v);
			}		
		}
		else if(inMST[u]) {
			selected.push_back({u, v});
			inMST[v] = true;
			unionSet(MSTN, u, v);
		}
		else if(inMST[v]) {
			selected.push_back({u, v});
			inMST[u] = true;
			unionSet(MSTN, u, v);
		}
		else {
			selected.push_back({u, v});
			inMST[v] = true;
			inMST[u] = true;
			unionSet(MSTN, u, v);
		}
	}
	return;
}

int main() {
	string s;
	int temp, n, vs;
	while(true) {
		cout<<"enter n x1 x2 w1 x3 x4 w2..., where n is no of vertices and edges are x1<->x2 of weight w1, x3<->x4 of weight w2...\n";
		cout<<"(1-based index). edges are bi-directional.\n";
		vector<int> v;
		getline(cin, s);
		stringstream ss(s);
		while(ss>>temp) {
			v.push_back(temp);		
		}
		vs = v.size();
		if(vs > 0) {
			V = v[0];
			if(V > 0) {
				edges = *(new vector<vector<vector<int>>> (V));
				if(vs%3 == 0) vs--;
				if(vs%3 == 2) vs--;
				for(int i = 1; i < vs; i += 3) {
					if(v[i] > 0 && v[i] <= V && v[i+1] > 0 && v[i+1] <= V) {
						edges[v[i]-1].push_back({v[i+1],v[i+2]});
						if(v[i+1] != v[i])
						edges[v[i+1]-1].push_back({v[i],v[i+2]});
					}
				}
				cout<<"The graph edges: \n";
				for(int i = 0; i < V; i++){
					cout<<i + 1<<" :-> ";
					for(int j = 0; j < edges[i].size(); j++) cout<<'('<<edges[i][j][0]<<':'<<edges[i][j][1]<<')'<<' ';
					cout<<'\n';
				}
				kruskalMST();
				temp = -1;
				for(int i = 0; i < selected.size(); i++){
					selected[i].push_back(find(MSTN, selected[i][0]));
				}
				sort(selected.begin(), selected.end(), cc2);
				for(int i = 0; i < selected.size(); i++){
					if(selected[i][2] > temp) {
						cout<<"\nNow printing MST with id 0x"<<hex<<selected[i][2]<<dec<<" :\n";
						temp = selected[i][2];
					}
					cout<<selected[i][0] + 1<<" -> "<<selected[i][1] + 1<<'\n';
				}
				for(int i = 0; i < V; i++) {
					if(MSTN[1][i] == 1) cout<<"\nsingelton node: "<<i+1;
				}
				cout<<'\n';
			}
		}
		cout<<endl; 
	}

	return 0;
} 
//sample test case:
//15 1 2 4 2 3 8 3 4 7 4 5 9 5 6 10 6 7 2 7 8 1 8 1 8 2 8 11 8 9 7 3 9 2 9 7 6 3 6 4 4 6 14 10 11 23 11 14 21