#include <iostream>
#include <vector>
#include <random>
#include <algorithm> 

using namespace std;

/*
O(n) worst time algo for finding  i-th smallest element.
O(n) space would be required.

though simple soln by partition also has O(n) avg time,
its worst time is O(n^2). So, this soln may perform better.
However, partition can be done in O(1) space.

also this algo finds a 3/10-th median of the array in O(n).
if we chose another odd no x > 5. it would find (x + 1)/(4*x)-th
median instead. 
x = 3 would not work for finding i-th smallest elem due to 
constraint {1 - (x + 1)/(4*x) + 1/x} < 1 for O(n) soln.  
*/

//not passing A by ref. don't want to rearrange actual vector.
//though immaterial for this problem. also, won't hurt order of space req.
int select(vector<int> A, int j) {
	int n = A.size();
	if(n == 1) return A[0]; 
	vector<int> M;
	for(int i = 0; i < n; i += 5) {
		if(i + 4 < n) sort(A.begin() + i, A.begin() + i + 5);
		else sort(A.begin() + i, A.end());
		if(i + 2 < n) M.push_back(A[i + 2]); 
		else(M.push_back(A[n-1]));
	}
	int k = select(M, (M.size()+1)/2);

	vector<int> A2, A3;
	//inplace partition is recomended. But not necessary as in quick sort.
	//closer analysis will show that space req is still O(n).
	for(int i = 0; i < n; i++){	
		if(A[i] < k) A2.push_back(A[i]);
		else if(A[i] > k) A3.push_back(A[i]);
	}
	if(A2.size() >= j) return select(A2, j);
	else if((n - A3.size()) < j) return select(A3, j + A3.size() - n);
	else return k;
	//handles repeating case as well.
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(1, 999);
	string s;
	int n, num;
	while(true) {
		vector<int> A;
		n = 8 + (dist(gen))%25;
		cout<<"Actual array : ";
		for(int i = 0; i < n; i++) {
			num = dist(gen);
			A.push_back(num);
			cout<<num<<' ';
		}
		cout<<'\n';
		for(int i = 0; i < 10; i++) {
			num = 1 + dist(gen) % n;
			cout<<"smallest element of rank "<<num<<" is : "<<select(A,num)<<endl;
		}
		cout<<"check results with : ";
		sort(A.begin(), A.end());
		for(int i = 0; i < n; i++) {
			cout<<A[i]<<' ';
		}
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl + c to exit."<<endl;
		getline(cin, s);
	}
	return 0;
}