#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string.h>
#include <math.h>

using namespace std;

unordered_map<char, int> exp_inPriority({{'+',1}, {'-',1}, {'*', 2}, {'/',2}, {'%',3},{'^',4},{'(',0}, {'[',0}, {'{',0}});
unordered_map<char, int> exp_outPriority({{'+',1}, {'-',1}, {'*', 2}, {'/',2}, {'%',3},{'^',5},{'(',6}, {'[',6}, {'{',6}});
unordered_set<char> valid_exp({'+', '-', '*', '/', '^', '%'});
unordered_set<char> valid_digits({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'});
unordered_set<char> evaluator({ ')', ']', '}'});
unordered_set<char> braces({ '(', '[', '{'});
unordered_map<char, char> bpair({{')', '('}, {']', '['}, {'}', '{'}, {'#', '#'}});
double d;

bool m_stod(string s) {
	if(s == "." || s == "-" || s == "+" || s.size() == 0) return false;
	int mul = s[0] == '-'? -1 : 1;
	bool dec = false;
	d = 0;
	int l = 0;
	long long int dm = 10;
	int curr;
	if(s[0] == '-' || s[0] == '+') l = 1;
	for(int i = l; i < s.size(); i++) {
		if(s[i] == '.'){
			if(dec) return false;
			else dec = true;
		}
		else {
			curr = s[i] - '0';
			if (curr > 9 || curr < 0) return false;
			if(dec) {	
				d = d + (double) curr/dm;
				dm *= 10;
			}
			else d = d*10 + curr;
		}
	}
	d *= mul;
	return true;
}

double calc(double d1, double d2, char o){
	switch(o) {
	case('+'):
		return d1 + d2;
		break;
	case('-'):
		return d1 - d2;
		break;
	case('*'):
		return d1 * d2;
		break;
	case('/'):
		return d1 / d2;
		break;
	case('^'):
		return pow (d1 , d2);
		break;
	case('%'):
		if((int) d2 == 0) return 0.0/0.0;
		return (int)d1 % (int)d2;
		break;
	default :
		return 0.0/0.0;
	} 
}

void eval(stack<char> &op, stack<double> &val) {
	double d1;
	double d2;
	char c, c2;
	c = op.top();
	op.pop();
	int c_p = bpair.find(c)->second;
	while(c_p != op.top()){
		c2 = op.top();
		op.pop();
		d1 = val.top();
		val.pop();
		d2 = val.top();
		val.pop();
		d1 = calc(d2, d1, c2);
		val.push(d1);
	}
	op.pop();
	return;	
}

void magic(stack<char> &op, stack<double> &val, char c) {
	double d1;
	double d2;
	char c2;
	int c_p = exp_outPriority.find(c)->second;
	while(op.size()>1 && c_p <= exp_inPriority.find(op.top())->second){
		c2 = op.top();
		op.pop();
		d1 = val.top();
		val.pop();
		d2 = val.top();
		val.pop();
		d1 = calc(d2, d1, c2);
		val.push(d1);
	}
	op.push(c);
	return;
}

int main() {
	string s1, s2;
	char c, p;
	bool valid;
	cout<<"enter expression. Press ctrl + c to exit"<<endl;
	while(true) {
		stack<char> op;
		stack<double> val;
		stack<char> brack;
		p = '#';
		getline(cin, s1);
		op.push('#');
		bool illegal = false;
		for(int i = 0; i < s1.size(); i++) {
			c = s1[i];
			if(c == ' ' || c == '\t') continue;
			if(braces.find(c) != braces.end()) {
				if(p == 'd') {
					valid = m_stod(s2);
					if(valid) {
						op.push('*');
					}
					else{
						illegal = true;
						break;
					}
				}
				else if(p == 'c'){
					op.push('*');
				}
				else if(p !='#' && p != 'e') {
					illegal = true;
					break;
				}
				op.push(c);
  				brack.push(c);
				p = '#';
			}
			else if(evaluator.find(c) != evaluator.end()) {
				if(p == 'e' || p == '#') {
					illegal = true;
					break;
				}
				if(brack.top() == bpair.find(c)->second) {
					if(p == 'd'){
						valid = m_stod(s2);
						if(valid) {
							val.push(d);
						}
						else{
							illegal = true;
							break;
						}
					}
					brack.pop();
					op.push(c);
					p = 'c';
					eval(op,val);
				}
				else {
					illegal = true;
					break;
				}
				
			}
			else if(p == '#'){
				s2 = "";
				if(valid_digits.find(c) != valid_digits.end() || c == '+' || c == '-') {
					s2 += c;
					p = 'd';
				}
				else {
					illegal = true;
					break;
				}
			}
			else if(c == '%'){
				if(p != 'd' && p != 'c') {
					illegal = true;
					break;
				}
				else {
					if(p == 'd'){
						valid = m_stod(s2);
						if(valid) {
							while(i + 1 < s1.size() && (s1[i+1] == ' ' || s1[i+1] == '\t' )) i++;
							if(i == s1.size() - 1 || evaluator.find(s1[i+1]) != evaluator.end()
										|| valid_exp.find(s1[i+1]) != valid_exp.end()) {
								d = d/100;
								s2 = to_string(d);
							}
							else {
								val.push(d);
								p = 'e';
								magic(op, val, c);
							}
						}
						else{
							illegal = true;
							break;
						}
					}
					else {
						while(i + 1 < s1.size() && (s1[i+1] == ' ' || s1[i+1] == '\t' )) i++;
						if(i == s1.size() - 1 || evaluator.find(s1[i+1]) != evaluator.end()
									|| valid_exp.find(s1[i+1]) != valid_exp.end()) {
							val.top() /= 100;
						}
						else {
							p = 'e';
							magic(op, val, c);
						}
					}
				}
				
			}
			else if(valid_exp.find(c) != valid_exp.end()) {
				if(p != 'd' && p != 'c') {
					illegal = true;
					break;
				}
				else {
					if(p == 'd'){
						valid = m_stod(s2);
						if(valid) {
							val.push(d);
						}
						else{
							illegal = true;
							break;
						}
					}
					p = 'e';
					magic(op, val, c);
				}
				
			}	
			else if (p == 'e') {
				s2 = "";
				if(valid_digits.find(c) != valid_digits.end()) {
					s2 += c;
					p = 'd';
				}
				else {
					illegal = true;
					break;
				}
			}
			else if (p == 'c') {
				s2 = "";
				if(valid_digits.find(c) != valid_digits.end()) {
					op.push('*');
					s2 += c;
					p = 'd';
				}
				else {
					illegal = true;
					break;
				}
			}
			else {
				if(valid_digits.find(c) != valid_digits.end()) {
					s2 += c;
				}
				else {
					illegal = true;
					break;
				}
			}
		}
		if(brack.empty() && !illegal){
			if(p == 'd'){
				valid = m_stod(s2);
				if(valid) {
					val.push(d);
				}
				else cout<<"invalid expression."<<endl; 
			}
			if(p != 'd' && p != 'c') cout<<"invalid expression."<<endl;
			else{
				op.push('#');
				eval(op, val);
				if(val.empty()) cout<<"invalid expression."<<endl;
				else cout<<val.top()<<endl;
			}	
		}
		else cout<<"invalid expression."<<endl; 
	}
}