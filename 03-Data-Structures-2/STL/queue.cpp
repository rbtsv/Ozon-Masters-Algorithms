#include<iostream>
#include<set>
#include<map>
#include<string>
using namespace std;

class MaxPrQueue{
	set<pair<int, string> > queue; // int -> priority, string -> key
	map<string, set<pair<int, string> >::iterator > find;
public:
	MaxPrQueue(){};
	void insert(pair<int, string> kv);
	void insert(string k, int v){ insert(make_pair(v ,k)); };
	pair<int, string> extract_max();
	void set_priority(pair<int, string> kv);
	void set_priority(string k, int v){ set_priority(make_pair(v, k)); };
	class ExceptionAddTheSameKey{};
};

void MaxPrQueue::insert(pair<int, string> kv){
	if(find.find(kv.second) == find.end())
		find[kv.second] = queue.insert(kv).first;
	else{throw ExceptionAddTheSameKey();}
}

pair<int, string> MaxPrQueue::extract_max(){
	set<pair<int, string> >::iterator it = queue.end();
	--it;
	find.erase(it->second);
	pair<int, string> x = *it;
	queue.erase(it);	
	return x;
}

void MaxPrQueue::set_priority(pair<int, string> vk){
	queue.erase(find[vk.second]);
	find.erase(vk.second);
	insert(vk);
}




int main (int argc, char const *argv[])
{
	MaxPrQueue q;
	q.insert("Z", 17);
	q.insert("C", 10);
	q.insert("A", 13);
	q.insert("B", 13);
	auto [v, k] = q.extract_max();
	cout << k << " " << v << endl;
	auto [v1, k1] = q.extract_max();
	cout << k1 << " " << v1 << endl;
	q.set_priority("A", 1);
	auto [v2, k2] = q.extract_max();
	cout << k2 << " " << v2 << endl;	
	return 0;
}