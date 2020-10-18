#include <iostream>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

/* finds shortest distance from start node to all nodes in graph 
	in O(ElogV).
it finds spt(shoertest part tree) from start node s.

spt != (any)MST of graph for any s in general.

but if we transform graph G in G' s.t. edge wt = edge wt + distance of edge from s
then spt(G) == (1 of) MST(G');
this is Dijkstra's algo equivalence with Prim's algo. (Both use Cut property)
Also this is Bellman-Fords' algo equivalence to Kruskal's algo. (Both use Cycle property)

for Dijkstra's algo ALL edges must be non-negative. (or atleast no cycle should have any neg edge).
(only shortcoming of Dijkstra's algo not Prim's).
For negative edges use Bellman-Ford.
*/
vector<bool> inSpt;
vector<int> dist;
vector<int> spHeap;
vector<int> heapPos; 

vector<vector<vector<int>>> edges;
int V;
int count;

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
			k = dist[spHeap[2*j + 1]] < dist[spHeap[2*j +2]] ? 2*j + 1 : 2*j + 2;
			else k = 2*j + 1;
			if(dist[spHeap[k]] < dist[spHeap[j]]) {
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
		if(dist[spHeap[index]] < dist[spHeap[(index-1)/2]]){
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
	if(count == V) return;
	int node = extractMin();
	//if whole tree is not connected :
	if(dist[node] == INT_MAX) return;
	//count will be no of connected comp then.
	int distance = dist[node];
	inSpt[node] = true;
	count++;
	for(int i = 0; i < edges[node].size(); i++) {
		if(!inSpt[edges[node][i][0] - 1]) {
			if(dist[edges[node][i][0] - 1] > distance + edges[node][i][1]) {
				dist[edges[node][i][0] - 1] = distance + edges[node][i][1];
				fix_heap(heapPos[edges[node][i][0] - 1]);
			}	
		}
	}
	greedy();
	return;
}

void dijkstra(int start) {
	if(V == 0) return;
	count = 0;
	start = start - 1;
	inSpt = *(new vector<bool>(V, false));
	dist = *(new vector<int>(V, INT_MAX));
	spHeap = *(new vector<int>(V));
	heapPos = *(new vector<int>(V));
	for(int i = 0; i < V; i++) {
		spHeap[i] = i;
		heapPos[i] = i;
	}
	dist[start] = 0;
	fix_heap(start);
	greedy();
	return;
}

int main() {
	string s;
	int temp, n, vs;
	while(true) {
		cout<<"enter n s x1 x2 w1 x3 x4 w2..., where n is no of vertices and edges are x1<->x2 of weight w1, x3<->x4 of weight w2... and s is the start node.\n";
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
				int s = 1;
				if(vs > 1) s = v[1];
				if(s < 1) s = 1;
				if(s > V) s = V;
				edges = *(new vector<vector<vector<int>>> (V));
				if(vs%3 == 1) vs--;
				if(vs%3 == 0) vs--;
				for(int i = 2; i < vs; i += 3) {
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
				dijkstra(s);
				cout<<"The distances from node "<<s<<" : \n";
				for(int i = 0; i < V; i++){
					cout<<i+1<<" : ";
					if(dist[i] == INT_MAX) cout<<"inf\n";
					else cout<<dist[i]<<'\n';
				}
				cout<<'\n'; 
			}
		}
		cout<<endl; 
	}

	return 0;
} 