#include <iostream>
#include <unistd.h>

using namespace std;

//this fn computes x^n in log(n) time.
int xpowern(int x, int n, int m) {
	if (x == 0) return 0;
	if (n == 0) return 1;
	else if (n == 1) return x;
	else {
		long long int y;
		y = xpowern(x, n/2, m);
		y = (y*y) % m;
		if (n%2 == 1) y = (y*x) % m;
		return (int) y;
	}	
}

int main() {
	int x, n, m;
	bool done = false;
	char e;
 	while(!done){
		cout<<"enter x : ";
		cin>>x;
		while(cin.fail()) {
			cin.clear();
			cout<<"enter integer x only : ";
			cin.ignore(123, '\n');
			cin>>x;
		}
		cout<<endl<<"enter n : ";
		cin>>n;
		while(cin.fail() || n<0) {
			cin.clear();
			cout<<"enter non-neg int range n only : ";
			cin.ignore(123, '\n');
			cin>>n;
		}
		cout<<endl;
		m = 1000000007;
		cout<<x<<"^"<<n<<" mod "<<m<<" : "<<xpowern(x, n, m)<<endl;
		e = 'a';
		cout<<"exit (y/n): ";
		cin>>e;
		cout<<endl;
		while(e != 'y' && e != 'n'){
			cout<<"enter (y/n) only: exit : ";
			cin>>e;
			cout<<endl;
		}
		if(e == 'y') done = true;
	}
	sleep(1);
	return 0;
}
