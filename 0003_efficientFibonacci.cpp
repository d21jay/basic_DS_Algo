#include <iostream>
#include <unistd.h>

using namespace std;

/*
f(n) is nth fibonacci number
                                 n-1
|f(n)  | = |1 1| |f(n-1)| = |1 1|   |1|
|f(n-1)|   |1 0| |f(n-2)|   |1 0|   |0|
*/

struct mulmat {
	long long int a = 1;
	long long int b = 1;
	long long int c = 1;
	long long int d = 0;
};

mulmat mulPowx(mulmat mul, int x, int m) {
	if(x == 1) return mul;
	long long int a, b, c, d, temp;
	mul = mulPowx(mul, x/2, m);
	a = ((mul.a * mul.a)%m + (mul.b * mul.c)%m)%m;
	b = ((mul.a * mul.b)%m + (mul.b * mul.d)%m)%m;
	c = ((mul.c * mul.a)%m + (mul.d * mul.c)%m)%m;
	d = ((mul.c * mul.b)%m + (mul.d * mul.d)%m)%m;
	if(x%2 == 1){
	temp = a;
	a = (a + b)%m;
	b = temp;
	temp = c;
	c = (c + d)%m;
	d = temp; 
	}
	mul.a = a;
	mul.b = b;
	mul.c = c;
	mul.d = d;
	return mul;
}

//This fn calculates nth fibonacci number in log(n).
int fib(int n, int m) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	mulmat mul;
	mul =  mulPowx(mul,n-1,m);
	return (int) mul.a;
}

int main() {
	bool done = false;
	int n, m;
	char e;
	m = 1000000007;
	while(!done){
		cout<<"enter n : ";
		cin>>n;
		while(cin.fail() || n<0) {
			cin.clear();
			cout<<"enter non-neg int range n only : ";
			cin.ignore(123, '\n');
			cin>>n; 
		}
		cout<<"nth fibonacci number mod "<<m<<" : "<<fib(n,m)<<endl<<"exit (y/n): ";
		e = 'a';
		cin>>e;
		while(e != 'y' && e != 'n') {
			cout<<"(y/n): ";
			cin>>e;
		}
		if(e == 'y') done = true;
	}
	sleep(1);
	return 0;
}