#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>

using namespace std;

#define MAX_COST 1000000001

struct vertex{
	//int cost;
	//vertex(int c){cost = c;}
	vertex(){}
};

class Graph{
	int n; // Number of vertices ≤ 10^5
public: 
	vector<vertex> V;
	Graph(int nn);
	//void printV();
	void printE();
	void printW();
	vector<vector<pair<int, unsigned int> > > neighbours;	
};



Graph::Graph(int nn){
	n = nn;
	//TC = 0;
	vector<vertex> VV(n, vertex());
	V=VV;	
	neighbours = vector<vector<pair<int, unsigned int> > >(n, vector<pair<int, unsigned int> >());
}


template<class T, class PriorInt=int> class MaxMinPrQueue{

struct CompareSecond{// return x < y
	bool operator()(const std::pair<T, PriorInt> &x, const std::pair<T, PriorInt> &y){
		if( x.second < y.second ) return true;
		if( x.second > y.second ) return false;
		return x < y;
	}
};
	set< pair<T, PriorInt>, CompareSecond> queue;
	map<T, typename set<pair<T, PriorInt> >::iterator  > find;
	
	
	public:
		MaxMinPrQueue(){ };
		void insert(pair<T, PriorInt> kv);// main insert
		void insert(T key, PriorInt val){ insert(make_pair(key, val));};
		void insert(T key){ insert(make_pair(key, 0)); }; 

		pair<T, PriorInt> extract_min();
		pair<T, PriorInt> extract_max();
		
		void set_priority(pair<T, PriorInt> kv);
		void set_priority(T k, PriorInt v){ set_priority(make_pair(k,v)); };
		
		bool empty() { return queue.empty(); }
		
		class ExceptionAddTheSameKey{};

};

template<class T, class PriorInt>	void MaxMinPrQueue<T, PriorInt>::insert(pair<T, PriorInt> kv){
		if(find.find(kv.first) == find.end() ){				 
				find[kv.first] = queue.insert(kv).first;				
		}else{ throw ExceptionAddTheSameKey(); }
	}
	
template<class T, class PriorInt>	pair<T, PriorInt> MaxMinPrQueue<T, PriorInt>::extract_min(){
		typename set<pair<T,PriorInt> >::iterator it = queue.begin();
		find.erase(it->first);
		pair<T,PriorInt> x = *it;
		queue.erase(it);
		return x;
		}
template<class T, class PriorInt>	pair<T, PriorInt> MaxMinPrQueue<T, PriorInt>::extract_max(){
		typename set<pair<T,PriorInt> >::iterator it = queue.end(); 
		it--;
		find.erase(it->first);
		pair<T,PriorInt> x = *it;
		queue.erase(it);
		return x;
	}		
	
template<class T, class PriorInt>	void MaxMinPrQueue<T, PriorInt>::set_priority(pair<T, PriorInt> kv){	
		queue.erase(find[kv.first]);
		find.erase(kv.first);
		insert(kv);
	}
	
struct Dijkstra{
	Graph *G;
	int n;
	int s;
	unsigned int M1;
	
	vector<unsigned int> dist;
	vector<int> pred;
	MaxMinPrQueue<int, unsigned int> q;
	
	Dijkstra(Graph *GG, int ss){
		M1=-1;
		G = GG;
		n = G->V.size();
		s = ss-1;
		dist = vector<unsigned int>(n, M1);
		dist[s] = 0;
		pred = vector<int>(n, -1);
	}	
	
	void operator ()();
	
	void Relax(int u, int v, int w){
		if( dist[v] > dist[u] + w ){ 
			dist[v] = dist[u] + w; 
			pred[v] = u;
			q.set_priority(v, dist[v]);
		}
	}
	
	void print_dist(){
		cout << "dist: " << endl;
		for(size_t i = 0; i < n; ++i){
			
			cout << "i: " << i << ", d[i]: ";
			 (dist[i] == M1) ? cout << -1 : cout << dist[i];
			 cout << endl;
		}
	}
	
};

	void Dijkstra::operator ()(){
		
		q.insert( make_pair(s, 0) );
		for(size_t i = 0; i < n; ++i){
			if(i != s){ q.insert( make_pair(i, M1) ); }
		}
		
		while( !q.empty() ){
			auto [u, d] = q.extract_min();								
			if(dist[u] != M1){
				for(auto [v, w] : G->neighbours[u]){
			  		Relax(u, v, w); 						
				}
			}else break;						
		}
			
	}

int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);	
	freopen( "a0", "r", stdin);
		
	int n, m, s, t;// m; // n — V, E — m;
	unsigned int M1 = -1;
	
	cin >> n >> m; cin >> s; cin >> t;
	
	//cout << "s: " << s << " t:" << t << endl; 
	
	Graph G(n);
	
	for(size_t i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		--u; --v;
		G.neighbours[u].emplace_back(v, w);
		G.neighbours[v].emplace_back(u, w);
	}

	
	Dijkstra dijkstra(&G, s);
	
	dijkstra();
	
	dijkstra.print_dist();
	
	if( dijkstra.dist[t-1] != M1 ){ cout << dijkstra.dist[t-1] << "\n"; 
		vector<int> s_t_path{t-1};
		int v = t-1;
		while( v != s-1){		
			s_t_path.push_back(dijkstra.pred[v]);
			v = dijkstra.pred[v];
		}		
		while(s_t_path.size() > 0){ 
			cout << s_t_path.back() + 1 << " ";
			s_t_path.pop_back();
		}
	}
	else{ cout << "-1\n"; }	
		
	return 0;
}