#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

/* finds MST of graph in O(ElogV).
no issue for any weights as
MST is free from any neg weight issues.
*/
vector<bool> inMST;
vector<int> span;
vector<int> parent;
vector<vector<int>> MSTN;
vector<int> spHeap;
vector<int> heapPos; 

vector<vector<vector<int>>> edges;
int V;
int count;
int mstn;

bool cc(vector<int> &a, vector<int> &b) {
	return a[1] < b[1];
}

int minOHeap() {
	return spHeap[0];
}

int extractMin() {
	int ans = spHeap[0];
	spHeap[0] = spHeap[spHeap.size() - 1];
	spHeap.pop_back();
	heapPos[ans] = -1;
	int j = 0;
	bool done = false;
	int temp = spHeap[j];
	while(!done) {
		done = true;
		if(2*j + 1 < spHeap.size()) {
			int k;
			if(2*j + 2 < spHeap.size())
			k = span[spHeap[2*j + 1]] < span[spHeap[2*j +2]] ? 2*j + 1 : 2*j + 2;
			else k = 2*j + 1;
			if(span[spHeap[k]] < span[spHeap[j]]) {
				done = false;
				heapPos[spHeap[j]] = k;
				heapPos[spHeap[k]] = j;
				spHeap[j] = spHeap[k];
				spHeap[k] = temp;
				j = k;
			}
		}
	}
	return ans;
}

void fix_heap(int index) {
	bool done = false;
	int temp = spHeap[index];
	while(!done && index > 0 ) {
		if(span[spHeap[index]] < span[spHeap[(index-1)/2]]){
			heapPos[spHeap[index]] = (index-1)/2;
			heapPos[spHeap[(index-1)/2]] = index;
			spHeap[index] = spHeap[(index-1)/2];
			spHeap[(index-1)/2] = temp;
			index = (index-1)/2; 
		}
		else done = true;
	}
	return;
}

void greedy() {
	if(spHeap.size() == 0) return;
	int node = minOHeap();
	//if whole tree is not connected :
	if(parent[node] == -1) return;
	extractMin();
	inMST[node] = true;
	MSTN[node][1] = mstn;
	for(int i = 0; i < edges[node].size(); i++) {
		if(!inMST[edges[node][i][0] - 1]) {
			if(span[edges[node][i][0] - 1] > edges[node][i][1]) {
				span[edges[node][i][0] - 1] = edges[node][i][1];
				parent[edges[node][i][0] - 1] = node + 1;
				fix_heap(heapPos[edges[node][i][0] - 1]);
			}	
		}
	}
	greedy();
	return;
}

void primMST() {
	if(V == 0) return;
	mstn = 1;
	inMST = *(new vector<bool>(V, false));
	span = *(new vector<int>(V, INT_MAX));
	MSTN = *(new vector<vector<int>>(V));
	spHeap = *(new vector<int>(V));
	heapPos = *(new vector<int>(V));
	parent = *(new vector<int>(V, -1));
	for(int i = 0; i < V; i++) {
		spHeap[i] = i;
		heapPos[i] = i;
		MSTN[i].push_back(i);
		MSTN[i].push_back(0);
	}
	for(int i = 0; i < V; i++) {
		if(parent[i] == -1) {
			span[i] = 0;
			parent[i] = 0;
			fix_heap(i);
			MSTN[i][1] = mstn;
			greedy();
			mstn++;
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
				cout<<'\n';
				primMST();
				sort(MSTN.begin(), MSTN.end(), cc);
				temp = 0;
				for(int i = 0; i < V; i++){
					if(MSTN[i][1] > temp) {
						cout<<"\nNow printing MST number "<<MSTN[i][1]<<" :\n";
						temp++;
					}
					if(parent[MSTN[i][0]] == 0) cout<<'x';
					else cout<<parent[MSTN[i][0]];
					cout<<" -> "<<MSTN[i][0] + 1<<'\n';
				}
				cout<<'\n';
			}
		}
		cout<<endl; 
	}

	return 0;
} 