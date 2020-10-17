#include <iostream>
#include <random>
#include <climits>

using namespace std;

//O(n) sort technically over n^const1 range or less integers ∀ n > const2 and const3 otherwise..
//const1 = 5, const2 = 100, and const3 = (c + const1)*const2 in this case.

void radixSort100(int arr[], int sorted[], int n) {
	//int range is -2*10^9 to 2*10^9.
	//base 100-digits = 5
	int baseArr[2][5][n];
	int j, k;
	for(int i = 0; i < n; i++) {
		j = 0;
		k = arr[i];
		while(k != 0){
			//no need to worry about negs. coz neg should be opp-sorted at digits level.
			baseArr[0][j][i] = k%100;;
			k /= 100;
			j++;
		}
		for(k = j; k < 5; k++) baseArr[0][k][i] = 0;
	}
	int count[199] = {0};
	//for stable sort;
	int index[199] = {0};
	for(int l = 0; l < 5; l++) {
		for(int i = 0; i < n; i++) {
			count[baseArr[l%2][l][i]+99]++;
		}
		index[0] = count[0] - 1;
		for(int i = 1; i < 199; i++) {
			index[i] = index[i-1] + count[i];
		}
		for(int i = n-1; i >= 0; i--) {
			for(k = 0; k < 5; k++) {
				baseArr[(l+1)%2][k][index[baseArr[l%2][l][i]+99]] = baseArr[l%2][k][i];
			}
			index[baseArr[l%2][l][i]+99]--;
		}
		for(int i = 0; i < 199; i++) {
			index[i] = 0;
			count[i] = 0;
		}
	}
	//combine;
	for(int i = 0; i < n; i++) {
		sorted[i] = 0;
		int dvalue = 1;
		for(k = 0; k < 5; k++) {
			sorted[i] += dvalue*baseArr[1][k][i];
			dvalue *= 100;
		}
	}
	return;
}

int main() {
	default_random_engine gen;
	uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
	uniform_int_distribution<int> ndist(1, 500);
	int n;
	string s;
	while(true) {
		n = ndist(gen);
		int arr[n], sorted[n];
		
		cout<<"\noriginal array:\n";
		for(int i = 0; i < n; i++) {
			arr[i] = dist(gen);
			cout<<arr[i]<<' ';
			
		}
		cout<<'\n';
		radixSort100(arr, sorted, n);
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