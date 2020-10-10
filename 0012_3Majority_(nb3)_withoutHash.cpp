#include <iostream>

using namespace std;
/*
this algo finds element in a n-sized array/list that occurs more than n/3 times
in O(n) time and O(1) space.

array/list could even be read only.
only operation allowed is '=='.
"<=, =>, <, >" not defined or not allowed.
O(1) passing of array/list allowed.
*/

int main() {
	string s;
	char c1, c2;
	int count1, count2;
	while(true){
		cout<<"\nenter characters to find 3-majority (>n/3) : (or, exit with ctrl + c) :"<<endl;
		getline(cin,s);

		//The algo:
		count1 = 0;
		count2 = 0;
		for(int i = 0; i<s.size(); i++) {
			if(count1 == 0) {
				c1 = s[i];
				count1++;
			}
			else if(count2 == 0) {
				c2 = s[i];
				count2++;	
			}
			else if(s[i] == c1) count1++;
			else if(s[i] == c2) count2++;
			else {
				count1--;
				count2--;
			}
		}
		count1 = 0;
		count2 = 0;
		for(int i = 0; i<s.size(); i++) {
			if(s[i] == c1) count1++;
			else if(s[i] == c2) count2++;
		}
		if(count1 > s.size()/3) {
			cout<<"'"<<c1<<"' has 3-majority."<<endl;
			if (c1 == ' ') cout<<"<space> character."<<endl;
			else if (c1 == '\t') cout<<"<tab> character."<<endl;
		}
		if(count2 > s.size()/3) {
			cout<<"'"<<c2<<"' has 3-majority."<<endl;
			if (c2 == ' ') cout<<"<space> character."<<endl;
			else if (c2 == '\t') cout<<"<tab> character."<<endl;
		}
		if(count1 <= s.size()/3 && count2 <= s.size()/3)
			cout<<"no 3-majority character. (space and tabs included)"<<endl;
	}
	return 0;
}