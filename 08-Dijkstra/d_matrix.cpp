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
//	long long TC; // total cost;
	vector<vertex> V;
	vector<vector<bool> > E; //T — есть ребро, F — нет ребра
	vector<vector<unsigned int> > W; 
	
	//void add_edge(pair<int, int> p){ E[p.first-1][p.second-1] = 1; E[p.second-1][p.first-1] = 1; }
	Graph(int nn);
	//void printV();
	void printE();
	void printW();
	vector<int> neighbours(int v);
	void read_weight_matrix(){
		for(size_t i = 0; i < n; ++i){
			for(size_t j = 0; j < n; ++j){
				cin >>  W[i][j];
				(W[i][j] + 1 != 0) ?  E[i][j] = true : E[i][j] = false;
			}
		}
	}
};


vector<int> Graph::neighbours(int v){
	vector<int> neigh;
	for(size_t j = 0; j < n; ++j){
		if(E[v][j] ){neigh.push_back(j);}
	}
	return neigh;
}





Graph::Graph(int nn){
	n = nn;
	//TC = 0;
	vector<vertex> VV(n, vertex());
	V=VV;
	
	vector<vector<bool> > EE(n, vector<bool>(n, false) );
	E=EE;
	
	vector<vector<unsigned int> > WW(n, vector<unsigned int>(n, -1) );
	W = WW;
	
}

/*void Graph::printV(){
	for(size_t i = 0; i < n; ++i){
		cout << V[i].cost << " ";
	}
	cout << endl << endl;
}*/

void Graph::printE(){
	for(size_t i = 0; i < n; ++i){
		for(size_t j = 0; j < n; ++j){
			cout << E[i][j];
			cout << " ";
		}
		cout << "\n";
	}
}

void Graph::printW(){
	for(size_t i = 0; i < n; ++i){
		for(size_t j = 0; j < n; ++j){
			cout << W[i][j];
			cout << " ";
		}
		cout << "\n";
	}
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
		vector<unsigned int> d(n, M1);
		dist = d;		
	}	
	
	void operator ()();
	
	void Relax(int u, int v){
		if( dist[v] > dist[u] + G->W[u][v] ){ 
			dist[v] = dist[u] + G->W[u][v]; 
			//pred[v] = u;
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
			pair<int, int> vd = q.extract_min();
			
			int v = vd.first;
			dist[v] = vd.second;			
			vector<int> neigh = G->neighbours(v);
			
			//cout << "v: " << v  << ", d[v] = " << dist[v] << endl;
			
			if(dist[v] != M1){
				for(vector<int>::iterator pu=neigh.begin(); pu != neigh.end(); ++pu){
			  		Relax(v, *pu); 						
				}
			}			
			
		}
			
	}

int main (int argc, char const *argv[]){
	std::ios::sync_with_stdio(false); std::cin.tie(0);	
	//	freopen( "m0", "r", stdin);
		
	int n, s, t;// m; // n — V, E — 
	unsigned int M1 = -1;
	
	cin >> n; cin >> s; cin >> t;
	
	//cout << "s: " << s << " t:" << t << endl; 
	
	Graph G(n);
	
	
	G.read_weight_matrix();
		/*G.printW();
		cout << endl;
		G.printE();*/
	
	Dijkstra dijkstra(&G, s);
	
	dijkstra();
	
	//dijkstra.print_dist();
	
	if( dijkstra.dist[t-1] != M1 ){ cout << dijkstra.dist[t-1] << "\n"; }
	else{ cout << "-1\n"; }	
	return 0;
}