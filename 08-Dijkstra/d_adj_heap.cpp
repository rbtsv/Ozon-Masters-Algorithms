#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

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



	
struct Dijkstra{
	Graph *G;
	int n;
	int s;
	unsigned int M1;
	
	vector<unsigned int> dist;
	vector<int> pred;
	vector<pair<unsigned int, int> > heap;
	
	Dijkstra(Graph *GG, int ss){
		M1=-1;
		G = GG;
		n = G->V.size();
		s = ss;
		dist = vector<unsigned int>(n, M1);
		pred = vector<int>(n, -1);
		dist[s] = 0;
		heap.emplace_back(0, s); // heap.push_back(make_pair(0, s));
	}	
	
	void operator ()();
	
	void Relax(int u, int v, int w){
		if( dist[v] > dist[u] + w ){ 
			dist[v] = dist[u] + w; 
			pred[v] = u;
			heap.emplace_back(dist[v], v);
			push_heap(heap.begin(), heap.end(), std::greater<>{}); // std::greater<>{} (<) -> (>)
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
		//cout << "here";
		while(  !heap.empty() ){ // O(|E|)
			pop_heap(heap.begin(), heap.end(), std::greater<>{});		
			auto [d, u] = heap.back(); heap.pop_back(); // O(|E|)
			
			//cout << "Tst: " << u << " " << d << endl;
						
			assert(dist[u] <= d);
			if(dist[u] == d){ // только при закрытии вершины, т.е. O(|V|) запусков
				for(auto [v, w] : G->neighbours[u])
			  		Relax(u, v, w); 										
			}						
		}			
	}

int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);	
	//freopen( "a0", "r", stdin);
		
	int n, m, s, t;// m; // n — V, E — m;
	unsigned int M1 = -1;
	
	cin >> n >> m; 
	cin >> s >> t; --s; --t;
	
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
	
	//dijkstra.print_dist();
	
	if( dijkstra.dist[t] != M1 ){ cout << dijkstra.dist[t] << "\n"; 
		vector<int> s_t_path{t};
		int v = t;
		while( v != s){		
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