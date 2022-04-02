#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>

#define DEBUG false

using namespace std;

#define MAX_COST 1000000001

struct vertex{
	int id;
	vertex(int i){id = i;}
	vertex(){}
};

class Graph{	

public: 
	int n; // Number of vertices ≤ 10^5
	vector<vertex> V;

	vector<vector<int> > adj_list;
	virtual void add_edge(pair<int, int> p){ 
		adj_list[p.first-1].push_back(p.second-1); adj_list[p.second-1].push_back(p.first-1); 
	}
	Graph(int nn);
	Graph();
	void BFS();
	void printV();
	//void printE();
	vector<int> neighbours(int v){ return adj_list[v]; };
};


class Tree : public Graph{ // Tree — производный клас от Graph
	public:
	vector<int> parent;
	vector<vector<int> > lexname; // lexname[iv] Путь к вершине v (iv — индекс вершины v).
	
	Tree(){// Сначала вызывается Graph
		V[0].id = 0; // В задаче №1!
		parent.resize(1);
		lexname.resize(1);
		lexname[0].push_back(0);
	}
	
	void enlarge_graph(int s){
		for(size_t i = n; i < s; ++i){
			V.push_back(vertex(i));
		}
		n = s;
		adj_list.resize(n);
		parent.resize(n);
		lexname.resize(n);
	}
	
	void add_edge(pair<int, int> p){ 		
		if(p.second > n) enlarge_graph(p.second);
		Graph::add_edge(p);
		//add edge u -> v
		int iu = p.first-1, iv = p.second-1;
		
		parent[iv] = iu;
		lexname[iv] = lexname[iu];
		lexname[iv].push_back(iv);
	}
	
	int lca(int iu, int iv){		
		int min_size = min(lexname[iu].size(), lexname[iv].size());
		int l = 0, r = min_size - 1;
		if(lexname[iu][r] == lexname[iv][r]) return lexname[iu][r];
		
		int i = (l+r)/2;
		while( r - l > 1){
			if(lexname[iu][i] == lexname[iv][i]){ l = i; i = (l+r)/2 + (l+r)%2;}
			else{ r = i; i = (l+r)/2;}
		}
		return(lexname[iu][l]);
	}
};

Graph::Graph(){
	n = 1;
	vector<vertex> VV(n, vertex());
	V=VV;
	vector<vector<int> > al(n);
	adj_list = al;
}

Graph::Graph(int nn){
	n = nn;
	vector<vertex> VV(n, vertex());
	V=VV;
	vector<vector<int> > al(n);
	adj_list = al;
}

void Graph::printV(){
	for(size_t i = 0; i < n; ++i){
		cout << V[i].id << " ";
	}
	cout << endl << endl;
}

void print_vec(vector<int> v){
	//cout <<"print_vec: ";
	for(vector<int>::iterator it=v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	cout << "\n";
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
	//min_cur = min(min_cur, G->V[v].cost);
	for(auto u : G->neighbours(v)){
		if(d[u] == 0) search(u);
	}
	f[v] = t++;
}

int main (int argc, char const *argv[])
{	
	std::ios::sync_with_stdio(false); std::cin.tie(0);	
	if(DEBUG) freopen("./testsA/01", "r", stdin);	
	
	Tree T;
	int k; 
	cin >> k; // Число запросов.
	
	for(size_t i = 0; i < k; ++i){
		string q; // запрос
		int iu, iv;
		cin >> q >> iu >> iv;
		if(DEBUG) cout << q << " " << iu << " " << iv << "\n"; 
		if(q=="ADD"){ T.add_edge(make_pair(iu, iv));  			}
		if(q=="GET"){ cout << T.lca(iu-1, iv-1)+1 << "\n"; }
	}
	
	/*cout << "pr_vec:";
	print_vec(T.adj_list[0]);
	
	//int iv
	//T.add_edge(make_pair(iu, iv));
	
	/*DFS dfs(&T);
	dfs.search();
	cout << "d:";
	print_vec(dfs.d);
	cout << "f:";
	print_vec(dfs.f);*/
	
	
	return 0;
}