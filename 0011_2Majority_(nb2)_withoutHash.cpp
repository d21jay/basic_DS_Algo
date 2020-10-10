#include <iostream>

using namespace std;
/*
this algo finds element in a n-sized array/list that occurs more than n/2 times
in O(n) time and O(1) space.

array/list could even be read only.
only operation allowed is '=='.
"<=, =>, <, >" not defined or not allowed.
O(1) passing of array/list allowed.
*/

int main() {
	string s;
	char c;
	int count;
	while(true){
		cout<<"\nenter characters to find 2-majority (>n/2) : (or, exit with ctrl + c) :"<<endl;
		getline(cin,s);

		//The algo:
		count = 0;
		for(int i = 0; i<s.size(); i++) {
			if(count == 0) {
				c = s[i];
				count++;
			}
			else if(s[i] == c) count++;
			else count--;
		}
		count = 0;
		for(int i = 0; i<s.size(); i++) {
			if(s[i] == c) count++;
		}
		if(count > s.size()/2) {
			cout<<"'"<<c<<"' has 2-majority."<<endl;
			if (c == ' ') cout<<"<space> character."<<endl;
			else if (c == '\t') cout<<"<tab> character."<<endl;
		}
		else cout<<"no 2-majority character. (space and tabs included)"<<endl;
	}
	return 0;
}