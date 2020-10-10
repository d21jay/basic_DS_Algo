#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

long long int ifib(long long int n) {
	long long int a = 0;
	long long int b = 1;
	if(n <= 0) return 0;
	if(n == 1) return 1;
	long long int t = -1;
	for(long long int i = 2; i <=n; i++) {
		t = a + b;
		a = b;
		b = t;
	}
	return t;
}

long long int rfib(long long int n) {
	if (n <= 0) return 0;
	if (n == 1) return 1;
	else return (rfib(n-1) + rfib(n-2));
}

int main() {
	clock_t T;
	cout<<"starting..."<<endl;
	cout<<"ifib check..."<<endl;
	for(int i = 0; i <= 15; i++) {
		cout<<ifib(i)<<endl;
	}
	cout<<"rfib check..."<<endl;
	for(int i = 0; i <= 10; i++) {
		cout<<rfib(i)<<endl;
	} 
	long long int n = 0;
	T = clock();
	while (clock() - T < CLOCKS_PER_SEC*60) {
		ifib(n);
		n++;
	}	
	cout<<"ifib seq n = "<<n<<"\n";
	long long int x = n;
	x = (n*(n + 1)/2);
	n = 0;
	T = clock();
	while (clock() - T < CLOCKS_PER_SEC*60) {
		rfib(n);
		n++;
	}
	cout<<"rfib seq n = "<<n<<"\n";
	long long int y = n + 1;
	cout<<"attempting ifib for (n*(n + 1)/2) : "<<x<<", proc time : ";
	T = clock();
	ifib(x);
	cout<<(clock() - T)/CLOCKS_PER_SEC<<" sec"<<endl;
	cout<<"attempting rfib for n + 1 : "<<y<<" , proc time : ";
	T = clock();
	rfib(y);
	cout<<(clock() - T)/CLOCKS_PER_SEC<<" sec"<<endl;
	cout<<"bye";
	sleep(20);
	return 0;	
}