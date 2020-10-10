#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class List{
	private:
	static int ListCounter;
	struct node{
		string val;
		node *left = nullptr;
		node *right = nullptr;
		int listId;
	};
	int listId;
	node* head = nullptr;
	node* tail = nullptr;
	int size = 0;
	
	public:
	List() {
		listId = ListCounter;
		ListCounter++;
	}
	int length() {					/*O(1)*/
		return size;
	}
	bool checkNode(node* n){
		try {
			return (n->listId == listId)? true : false;
		}
		catch(...) {
			return false;
			}
	}
	void printList() {					/*O(size)*/
		if(size == 0) {
			cout<<"(empty)"<<endl;
			return;
		}
		node* temp = head;
		while(temp->right != nullptr){
			cout<<temp->val<<" ";
			temp = temp->right;	
		}
		cout<<temp->val<<endl;
	}
	void printListReverse() {				/*O(size)*/
		if(size == 0) {
			cout<<"(empty)"<<endl;
			return;
		}
		node* temp = tail;
		while(temp->left != nullptr){
			cout<<temp->val<<" ";
			temp = temp->left;	
		}
		cout<<temp->val<<endl;
	}
	vector<string> returnValuesInVector() {			/*O(size)*/
		vector<string> vec;
		if(size == 0) return vec;
		node* temp = head;
		while(temp->right != nullptr){
			vec.push_back(temp->val);
			temp = temp->right;	
		}
		vec.push_back(temp->val);
		return vec;
	}
	void makeListEmpty(){					/*O(1)*/
		head = nullptr;
		tail = nullptr;
		size = 0;
		listId = ListCounter;
		ListCounter++;
	}
	bool isListEmpty() {					/*O(1)*/
		return size == 0? true : false;
	}
	void insert(void* addr, string val) {			/*O(1)*/
		node* n = (node*) addr;
		if(checkNode(n)) {
			node* temp = new node();
			temp->val = val;
			temp->listId = listId;
			size++;
			temp->right = n;
			temp->left = n->left;
			n->left = temp;
			if(temp->left == nullptr) head = temp;
			else temp->left->right = temp;
		}
		else{
			cout<<"error: addr doesn't belong to this list"<<endl;
			return;
		}
		return;
	}
	void del(void* addr){					/*O(1)*/
		node* n = (node*) addr;
		if(checkNode(n)) {
			n->listId = -1;
			size--;
			if(n->right == nullptr && n->left == nullptr) {
				head = nullptr;
				tail = nullptr;
			}
			else if(n->right == nullptr) {
				n->left->right = nullptr;
				tail = n->left;
			}
			else if(n->left == nullptr) {
				head = n->right;
				n->right->left = nullptr;
			}
			else {
				n->left->right = n->right;
				n->right->left = n->left;
			}
			n->left = nullptr;
			n->right = nullptr;
		}
		else{
			cout<<"error: addr doesn't belong to this list"<<endl;
			return;
		}
		return;
	}
	vector<void*> search(string val){			/*O(size)*/
		vector<void*> vec;
		if(size == 0) return vec;
		node* temp = head;
		while(temp->right != nullptr){
			if(temp->val == val) vec.push_back(temp);
			temp = temp->right;	
		}
		if(temp->val == val) vec.push_back(temp);
		return vec;	
	}
	void insertAsHead(string val){				/*O(1)*/
		if(head == nullptr) insertAsTail(val);
		else insert(head, val);
		return;
	}
	void insertAsTail(string val){				/*O(1)*/
		node* temp = new node();
		temp->val = val;
		temp->listId = listId;
		size++;
		temp->left = tail;
		tail = temp;
		if(temp->left == nullptr) head = temp;
		else temp->left->right = temp;
		return; 
	}
	void remakeList(vector<string> vals) {			/*O(vals.size())*/
		makeListEmpty();
		addToList(vals);
		return;
	}
	void addToList(vector<string> vals) {			/*O(vals.size())*/
		for(int i = 0; i<vals.size(); i++) insertAsTail(vals[i]);
		return;
	}
	void insert(void* addr, vector<string> vals) {/*O(vals.size())*/
		node* n = (node*) addr;
		if(checkNode(n)) {
			for(int i = 0; i<vals.size(); i++) insert(addr, vals[i]);
		}
		else{
			cout<<"error: addr doesn't belong to this list"<<endl;
			return;
		}
		return;
	}
	void* successor(void* addr, bool print) {		/*O(1)*/
		node* n = (node*) addr;
		if(checkNode(n)) {
			if (print) {
				if(n->right != nullptr) cout<<n->right->val<<endl;
				else cout<<"none"<<endl;
			}
			return n->right;
		}
		else{
			cout<<"error: addr doesn't belong to this list"<<endl;
			return nullptr;
		}
	}
	void* predecessor(void* addr, bool print) {		/*O(1)*/
		node* n = (node*) addr;
		if(checkNode(n)) {
			if (print) {
				if(n->left != nullptr) cout<<n->left->val<<endl;
				else cout<<"none"<<endl;
			}
			return n->left;
		}
		else{
			cout<<"error: addr doesn't belong to this list"<<endl;
			return nullptr;
		}
	}
};
int List::ListCounter;
void menu() {
	cout<<"01. new empty list :"<<string(31, ' ')<<"new\n";
	cout<<"02. new empty list with multiple items :"<<string(11, ' ')<<"new X Y Z ...\n";
	cout<<"03. make current list empty :"<<string(22, ' ')<<"empty\n";
	cout<<"04. check if current list is empty :"<<string(15, ' ')<<"q\n";
	cout<<"05. search current list for X (displays addr(s)):"<<string(2, ' ')<<"search X\n";
	cout<<"06. find successor of item with address addr :"<<string(5, ' ')<<"next addr\n";
	cout<<"07. find predecessor of item with address addr :"<<string(3, ' ')<<"prev addr\n";
	cout<<"08. del item with address addr :"<<string(19, ' ')<<"del addr\n";
	cout<<"09. insert item X before address addr :"<<string(12, ' ')<<"in addr X\n";
	cout<<"10. insert multiple items before address addr :"<<string(4, ' ')<<"in addr X Y Z ...\n";
	cout<<"11. insert item X as tail/ add item X to list :"<<string(4, ' ')<<"add X\n";
	cout<<"12. add multiple items to list :"<<string(19, ' ')<<"add X Y Z ...\n";
	cout<<"13. insert item X as head :"<<string(24, ' ')<<"inh X\n";
	cout<<"14. print list :"<<string(35, ' ')<<"print\n";
	cout<<"15. print list in reverse :"<<string(24, ' ')<<"rprint\n";
	cout<<"16. number of items on list :"<<string(22, ' ')<<"len\n";
	cout<<"warning: entering wrong 'addr' may lead to immediate termination.\n";
	cout<<"---------------------------------------------------------------------\n";
	cout<<"17. exit :"<<string(41, ' ')<<"bye\n";
	cout<<"18. relook menu :"<<string(34, ' ')<<"m\n";
	cout<<"---------------------------------------------------------------------"<<endl;
return;
}

int main() {
	void* addr;
	int val;
	string s, s2;
	bool done = false;
	menu();
	List l;
	while(!done){
		getline(cin,s);
		stringstream ss(s);
		ss>>s;
		if(s == "bye") done = true;
		else if(s == "new"){
			vector<string> vals;
			while(ss>>s2) vals.push_back(s2);
			l.remakeList(vals);
		}
		else if(s == "empty") l.makeListEmpty();
		else if(s == "q"){
			if(l.isListEmpty()) cout<<"empty list"<<endl;
			else cout<<"list not empty"<<endl;
		}
		else if(s == "search"){
			ss>>s2;
			vector<void*> addrss = l.search(s2);
			if (addrss.size() == 0) cout<<"not found"<<endl;
			else cout<<"found at location(s) : "<<endl;
			for(int i = 0; i < addrss.size(); i++) cout<<addrss[i]<<endl;
		}
		else if(s == "next"){
			ss>>addr;
			addr = l.successor(addr, true);
			if (addr != nullptr) cout<<"found at : "<<addr<<endl;
		}
		else if(s == "prev"){
			ss>>addr;
			addr = l.predecessor(addr, true);
			if (addr != nullptr) cout<<"found at : "<<addr<<endl;
		}
		else if(s == "del"){
			ss>>addr;
			l.del(addr);
		}
		else if(s == "in"){
			vector<string> vals;
			ss>>addr;
			while(ss>>s2) vals.push_back(s2);
			l.insert(addr, vals);
		}
		else if(s == "add"){
			vector<string> vals;
			while(ss>>s2) vals.push_back(s2);
			l.addToList(vals);
		}
		else if(s == "inh") {
			if(ss>>s2) l.insertAsHead(s2);
		}
		else if(s == "print") l.printList();
		else if(s == "rprint") l.printListReverse();
		else if(s == "len") cout<<l.length()<<endl;
		else if(s == "m") menu();
		else cout<<"invalid input, try again"<<endl;
	}
	return 0;	
}