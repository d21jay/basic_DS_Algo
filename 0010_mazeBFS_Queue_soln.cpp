#include <iostream>
#include <random>
#include <queue>
#include <iomanip>

using namespace std;

bool** maze;
int** bfn;
int n;
queue<int*> q;

// bfs/queue algo to travel to n*n maze in O(n*n);
void bfs() {
	int curr[2];
	int num, i, j;
	while(!q.empty()) {
		curr[0] = q.front()[0];
		curr[1] = q.front()[1];
		q.pop();
		num = bfn[curr[0]][curr[1]];
		j = curr[1];
		for(i = curr[0] - 1; i <= curr[0] + 1; i += 2) {
			if(i >= 0 && i < n) {
				if(bfn[i][j] < 0 && maze[i][j]) {
					int* temp = new int[2]();
					temp[0] = i;
					temp[1] = j;
					q.push(temp);
					bfn[i][j] = num + 1;
				}
			}	
		}
		i = curr[0];
		for(j = curr[1] - 1; j <= curr[1] + 1; j += 2) {
			if(j >= 0 && j < n) {
				if(bfn[i][j] < 0 && maze[i][j]) {
					int* temp = new int[2]();
					temp[0] = i;
					temp[1] = j;
					q.push(temp);
					bfn[i][j] = num + 1;
				}
			}	
		}
	}
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(5,10);
	string s;
	int r;
	while(true) {
		n = dist(gen);
		maze = new bool* [n];
		bfn = new int* [n];	
		for(int i = 0; i < n; i++) {
			maze[i] = new bool[n];
			bfn[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				r = dist(gen);
				maze[i][j] = (r <= 8);
				bfn[i][j] = -1;
			}
		}
		maze[0][0] = true;
		bfn[0][0] = 0;
		int temp[2] = {0, 0};
		q.push(temp);
		bfs();
		for (int i = 0; i < n; i++) {
			cout<<' ';
			for (int j = 0; j < n; j++) {
				cout<<(maze[i][j]? '+' : ' ')<<' '<<' '<<' ';
			}
			cout<<' '<<' ';
			for (int j = 0; j < n; j++) {
				cout<<setw(2);
				if(bfn[i][j] >= 0) cout<<bfn[i][j];
				else {
					if(maze[i][j]) cout<<'+';
					else cout<<' ';
				}
				cout<<' '<<' ';
			}
			cout<<'\n'<<'\n';
		}
		cout<<"press enter for new maze. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}
