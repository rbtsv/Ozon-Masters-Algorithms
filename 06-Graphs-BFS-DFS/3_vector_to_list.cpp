#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<list>


using namespace std;

#define MAX_COST 1000000001

struct vertex{
	// id 
	int cost;
	vertex(int c){cost = c;}
	vertex(){}
};

class Graph{
	int n; // Number of vertices ≤ 10^5
public: 
	long long TC; // total cost;
	vector<vertex> V;
	vector<list<int> > adj_list;
	void add_edge(pair<int, int> p){ 
		adj_list[p.first-1].push_back(p.second-1); 
		adj_list[p.second-1].push_back(p.first-1); 
	}
	Graph(int nn);
	void BFS();
	void printV();
	void printE();
	const list<int> & neighbours(int v){return adj_list[v];}
};

void Graph::BFS(){
	queue<int> q;
	vector<bool> touched(n, false);
	for(size_t i = 0; i < n; ++i){
		int min_cost;
		if(!touched[i]){
			min_cost = V[i].cost;
			q.push(i); touched[i] = true;
			while( !q.empty() ){
				min_cost = min(min_cost, V[q.front()].cost);
				for(auto u : neighbours(q.front())){
					if(!touched[u]){q.push(u); touched[u] = true;}
				}
				q.pop();
			}
			TC += min_cost;			
		}
	}
}

Graph::Graph(int nn){
	n = nn;
	TC = 0;
	vector<vertex> VV(n, vertex());
	V=VV;
	adj_list = vector<list<int> >(n, list<int>());
	
}

void Graph::printV(){
	for(size_t i = 0; i < n; ++i){
		cout << V[i].cost << " ";
	}
	cout << endl << endl;
}

struct DFS{
	Graph * G;
	int n; // Number of vertices == G->n
	int t; // Current time
	vector<int> d, f; // d — время открытия; f — время закрытия 
					// d[u] > 0 — вершина открыта.
	long long TC;
	int min_cur;
	
	DFS(Graph * GG){
		G = GG;
		n = G->V.size();
		t = 1; //!!! t == 0 -- вершина не открыта
		TC = 0;
		d = vector<int>(n, 0);
		f = vector<int>(n, 0);		
	}
	void search(); // Full DFS;
	void search(int v); // DFS starting from v;	
	void search_iter(); // DFS starting from v;	
};

void DFS::search(){
	for(size_t u = 0; u < n; ++u){
		if(d[u] == 0){ min_cur = MAX_COST; search(u); TC += min_cur; }
	}	
}

void DFS::search(int v){// v — input; u — local
	d[v] = t++;
	min_cur = min(min_cur, G->V[v].cost);
	for(auto u : G->neighbours(v)){
		if(d[u] == 0) search(u);
	}
	f[v] = t++;
}

void DFS::search_iter(){
	for(size_t v = 0; v < n; ++v){// v — input; u — local
		if(d[v] == 0){ min_cur = MAX_COST;
			vector<pair<int, list<int>::const_iterator> > st; // v, iu++
			auto iv =  G->neighbours(v).begin();
			st.emplace_back(v, iv);
			while(!st.empty()){
				auto [v, iu] = st.back();
				st.pop_back();
				if(d[v] == 0){ 
					d[v] = t++;
					min_cur = min(min_cur, G->V[v].cost);
				}				
				bool call = false;
				auto & neigh = G->neighbours(v);
				for(; iu != neigh.end() && !call; ++iu){
					if(d[*iu] == 0){
						call = true;
						auto iv = iu;			
						st.emplace_back(v, ++iv);
						st.emplace_back(*iu,  G->neighbours(*iu).begin());
					}
				}
				if(!call) f[v] = t++;
			}
		 TC += min_cur; 
		 }
	}	
}

int main (int argc, char const *argv[])
{
	//freopen("t2", "r", stdin); // open file with test data to reed and acces it through stdin
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0);
	
	int n, m; // n — V, E — 
	
	cin >> n; cin >> m;
	
	Graph G(n);
	
	for(size_t i = 0; i < n; ++i){
		int cost;
		cin >> cost;
		vertex v(cost);
		G.V[i] = v;
	}
	//G.printV();
	
	for(size_t i = 0; i < m; ++i){
		pair<int, int> p;
		cin >> p.first; cin >> p.second;
		G.add_edge(p);
	}
	//G.printE();	
	
	//G.BFS();
	//cout << G.TC << "\n";
	
	DFS dfs(&G);
	dfs.search_iter();
	cout << dfs.TC << "\n";
	
	
	return 0;
}