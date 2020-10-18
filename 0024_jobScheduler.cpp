#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

bool cc(vector<int> &a, vector<int> &b){
	if(a[1] < b[1]) return true;
	else if(b[1] < a[1]) return false;
	else if(a[0] <= b[0]) return true;
	else return false;
}

/*
O(nlog(n)) greedy algo; 
*/

//this is just O(n) fn. O(nlog(n)) is due to sort.
void jobSchedule(vector<vector<int>> &A, vector<vector<int>> &B, int *sch) {
	int t = -1;
	for(int i = 0; i < A.size(); i++) {
		if(A[i][3] == 1) {
			if(A[i][0] > t) {
				B.push_back(A[i]);
				A[i][3] = 0;
				t = A[i][1];
				(*sch)++;
			}
		}
	}
	return;
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(1, 9999);
	string s;
	int n, num;
	while(true) {
		n = 3 + (dist(gen))%11;
		vector<vector<int>> A(n, vector<int>(4,1));
		//index 0 is start time.
		//index 1 is finish time.
		//index 2 is job id.
		//index 3 is isUnscheduled.
		for(int i = 0; i < n; i++) {
			num = dist(gen) % (2*n);
			A[i][0] = num;
			num = num + dist(gen) % (2*n-num);
			A[i][1] = num;
			A[i][2] = i;
		}
		cout<<"values :";
		cout<<"\n-------------";
		for(int i = 0; i < n; i++) cout<<"---";
		cout<<"\njob id     : ";
		for(int i = 0; i < A.size(); i++) {
			cout<<setw(2)<<A[i][2]<<' ';
		}
		cout<<"\n-------------";
		for(int i = 0; i < n; i++) cout<<"---";
		cout<<"\nstart time : ";
		for(int i = 0; i < A.size(); i++) {
			cout<<setw(2)<<A[i][0]<<' ';
		}
		cout<<"\nend time   : ";
		for(int i = 0; i < A.size(); i++) {
			cout<<setw(2)<<A[i][1]<<' ';
		}
		cout<<"\n\n";
		
		//The O(nlog(n)) step.
		sort(A.begin(), A.end(), cc);
		
		vector<vector<int>> B;
		int t;
		int sch = 0;
		cout<<"TimeScale : ";
		for(int i = 0; i < 2*n; i++){
			if(i < 10) cout<<'0';
			cout<<'0'<<i<<' ';
		}
		cout<<"\n------------";
		for(int i = 0; i < 2*n; i++) cout<<"----";
		cout <<"\n";
		cout<<"Schedules : ";
		while(sch != n) {
			B.clear();
			jobSchedule(A, B, &sch);
			t = 0;
			for(int i = 0; i < B.size(); i++) {
				while(t < B[i][0]){
					cout<<"    ";
					t++;
				}
				if(B[i][2] < 10) cout<<' ';
				cout<<B[i][2];
				while(t < B[i][1] - 1) {
					cout<<"---+";
					t++;
				}
				if(t == B[i][1] - 1) {
					cout<<"---x";
					t++;
				}
				cout<<"  ";
				t++;
			}
			cout<<'\n';
			if(sch < n) cout<<"          : ";
		}
		cout<<"------------";
		for(int i = 0; i < 2*n; i++) cout<<"----";

		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}