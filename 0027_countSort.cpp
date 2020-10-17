#include <iostream>
#include <random>

using namespace std;

//O(n + const1) sort for integers having const1 range.  where const1 = 100 this case.
void count100(int arr[], int sorted[], int n) {
		int count[100] = {0};
		//for stable sort;
		int index[100] = {0};
		for(int i = 0; i < n; i++) {
			count[arr[i]%100]++;
		}
		index[0] = count[0] - 1;
		for(int i = 1; i < 100; i++) {
			index[i] = index[i-1] + count[i];
		}
		for(int i = n-1; i >= 0; i--) {
			sorted[index[arr[i]%100]] = arr[i];
			index[arr[i]%100]--;
		}
		return;
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(0, 99);
	int n;
	string s;
	while(true) {
		n = dist(gen) + 1;
		int arr[n], sorted[n];
		
		cout<<"\noriginal array:\n";
		for(int i = 0; i < n; i++) {
			arr[i] = dist(gen);
			cout<<arr[i]<<' ';
			
		}
		cout<<'\n';
		count100(arr, sorted, n);
		cout<<"\nsorted array:\n";
		for(int i = 0; i < n; i++) {
			cout<<sorted[i]<<' ';
		}
		cout<<'\n';
		cout<<"\npress enter to sim again. press ctrl+c to exit.\n";
		getline(cin, s);
	}
	return 0;
}

//(∀ n >= √x : x<0)