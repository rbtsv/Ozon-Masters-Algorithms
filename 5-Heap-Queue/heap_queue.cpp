#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

template<class C> void print_vector(vector<C> v){
	for(auto x : v){
		cout << x << " ";
	}
	cout << endl;
}

template<class C, class D> void print_vector_of_pairs(vector<pair<C, D> > v){
	for(auto x : v){
		cout << "(" << x. first <<", " << x.second << ") ";
	}
	cout << endl;
}

template <class Key, class Val> class Heap{	
	vector<pair<Val, Key> > heap;
	map<Key, int> get_node; 
	int left_ind(int i){ // 1 -l-> 2 = 2*1, 1-r-> 3 = 2*1 + 1
		return 2*(i+1)-1;} // i-l-> 2i i-r-> 2i+1
	int right_ind(int i){
		return 2*(i+1);}
	int parent_ind(int i){
		if(i == 0) return i;
		return (i+1)/2-1;
	}
	void heap_swap(int i, int j){
		assert(max(i, j) < heap.size());
		get_node[heap[i].second] = j;
		get_node[heap[j].second] = i;
		std::swap(heap[i], heap[j]);
		/*auto val_i = heap[i];
		heap[i] = heap[j]; 
		heap[j] = val_i;*/
	}	
	void solve_collisions_up(int i){
		if(i == 0) return;
		if(heap[parent_ind(i)] < heap[i]){ 
			heap_swap(i, parent_ind(i));
			solve_collisions_up(parent_ind(i));
		}
	}
	void solve_collisions_down(int i){
		int max_i = i;
		if(left_ind(i)< heap.size() && heap[i] < heap[left_ind(i)])
			max_i = left_ind(i);
		if(right_ind(i) < heap.size() && heap[max_i] < heap[right_ind(i)])
			max_i = right_ind(i);
		if(max_i != i){ 
			heap_swap(i, max_i);
			solve_collisions_down(max_i);
		}
	}
	void solve_collisions(int i){		
		solve_collisions_up(i);
		solve_collisions_down(i);
	}
public:
	Heap(){}
	/*void print_heap(){
		print_vector_of_pairs<int, string>(heap);
	}*/
	void add(pair<Val, Key> p){
		heap.push_back(p);
		get_node[p.second] = heap.size()-1;
		solve_collisions_up(heap.size()-1);	
	}
	void update(pair<Val, Key> p){
		assert(get_node.find(p.second) != get_node.end());
		heap[get_node[p.second]] = p;
		solve_collisions(get_node[p.second]);	
	}
	void add_or_update(pair<Val, Key> p){
		if(get_node.find(p.second) == get_node.end())
			add(p);
		else update(p);			
	}
	bool has_key(Key k){
		return get_node.find(k) != get_node.end();
	}
	pair<Val, Key> find(Key k){
		assert(has_key(k));
		return heap[get_node[k]];
	}
	pair<Val, Key> extract_max(){
		heap_swap(0, heap.size()-1);
		pair<Val, Key> max_node = heap.back();
		heap.pop_back();		
		get_node.erase(max_node.second);
		solve_collisions_down(0);
		return max_node;
	}
	int size(){
		return heap.size();
	}		
};


int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	freopen("t", "r", stdin);
	int n, m;
	cin >> n >> m;
	//set<string> was;
	Heap<string, pair<int, int> > h;
	for(size_t i = 0; i < m; ++i){
		string name; int points;
		cin >> name >> points;
		if(h.has_key(name)){
			auto node = h.find(name);
			if(node.first.first < points)
				h.update(make_pair(make_pair(points, -i), name));
		}else{
			h.add(make_pair(make_pair(points, -i), name));
		}
			
		//h.add_or_update(make_pair(make_pair(points, -i), name));
		/*if(was.find(name) == was.end()){
			h.add(make_pair(points, name));
			was.insert(name);
		}*/
	}
	//h.print_heap();
	while(h.size() > 0){
		auto p = h.extract_max();
		cout << p.second << "\n";
	}
	return 0;
}