#include<iostream>
#include<string>

using namespace std;

struct list_item{
	string key;
	int val;
	list_item *next;
	list_item *prev;
	list_item(){};
	list_item(string k, int v){key = k; val = v; next = 0; prev = 0;};
};

class List{
	list_item *left;
	list_item *right;
	public:
		List();
		List(list_item * li);
		~List();
		list_item* next(list_item li);
		list_item* prev(list_item li);
		list_item* lbegin(){return left;}
		list_item* rbegin(){return right;}
		void insert_after(list_item *l, list_item *x);
		void delete_at(list_item *li);
};

List::List(){}
List::List(list_item * li_p){left = li_p; right = li_p;}

List::~List(){
	for(list_item * l = rbegin(); l != 0; ){
		list_item * _next = l->next;
		delete l;
		l = _next;
	}
}

void List::delete_at(list_item *l){
	if(left == l) left = l->next; 
	if(l->prev) (l->prev)->next = l->next;
	if(l->next) (l->next)->prev = l->prev;
	delete l; 
	return;
}

void List::insert_after(list_item *l, list_item *x){ // insert x after l
	x->next = l->next; l->next = x; x->prev = l;
	if(right == l) right = x;
	return;
}


int main (int argc, char const *argv[]){
	//	list_item li("k", 1), l2("k2", 2), l3("k3", 3), * lp;
	list_item * l1, * l2, * l3, * lp;
	l1 = new list_item("k1", 1);
	l2 = new list_item("k2", 2);
	l3 = new list_item("k3", 3);
	
	
	List * myp_list = new List(l1);
	lp = myp_list->lbegin();
	myp_list->insert_after(lp, l2);
	myp_list->insert_after(lp->next, l3);
	for(list_item * l = myp_list->lbegin(); l != 0; l = l->next){
		cout << l->key << " " << l->val << endl;
	}
	
	delete myp_list;
	
	return 0;
	l1 = new list_item("k1", 1);
	l2 = new list_item("k2", 2);
	l3 = new list_item("k3", 3);
	//cout << li.key << " " << li.val << endl;
	List my_list(l1);
	lp = my_list.lbegin();
	my_list.insert_after(lp, l2);
	my_list.insert_after(lp->next, l3);
	for(list_item * l = my_list.lbegin(); l != 0; l = l->next){
		cout << l->key << " " << l->val << endl;
	}
	my_list.delete_at(l2);
	//return 0;
	cout << "===\n";
	for(list_item * l = my_list.rbegin(); l != 0; l = l->prev){
		cout << l->key << " " << l->val << endl;
	}	
	cout << "===\n";
	for(list_item * l = my_list.lbegin(); l != 0; l = l->next){
		cout << l->key << " " << l->val << endl;
	}
	//cout << (my_list.lbegin())->key << " " << my_list.rbegin()->val << endl;
	
	
	return 0;
}

