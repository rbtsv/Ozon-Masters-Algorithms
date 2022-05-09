#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>

#define DEBUG false

using namespace std;

#define MAXH 20

struct vertex{
	int id;
	int depth;
	vector<int> powancesters;
	int height;	
	int name(){return id+1;}
	
	vertex(int i){id = i; powancesters = vector<int>(MAXH, -1);}
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
	vector<int> Powers={1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};	
	public:
	vector<int> parent;	
	
	Tree(){// Сначала вызывается Graph
		V[0] = vertex(0); // В задаче №1!
		parent.resize(1);		
		V[0].powancesters[0] = 0;
		V[0].depth = 1;
	}
	
	void enlarge_graph(int s){
		for(size_t i = n; i < s; ++i){
			V.push_back(vertex(i));
		}
		n = s;
		adj_list.resize(n);
		parent.resize(n);		
	}
	
	void compute_powancesters(int iv);
	
	void add_edge(pair<int, int> p){ 		
		if(p.second > n) enlarge_graph(p.second);
		Graph::add_edge(p);
		//add edge u -> v
		int iu = p.first-1, iv = p.second-1;		
		parent[iv] = iu;
		vertex & v = V[iv], & u = V[iu];
		v.depth = u.depth + 1;
		compute_powancesters(iv);		
	}
	
	int lca(int iu, int iv){ // u глубже или на той же глубине, что и v		
		int answ = 0;
		for(int i = MAXH-1; i >= 0; --i){
			if(V[iu].powancesters[i] != V[iv].powancesters[i]){
				if(V[iu].powancesters[i] != -1)
					iu = parent[V[iu].powancesters[i]];
				if(V[iv].powancesters[i] != -1)
					iv = parent[V[iv].powancesters[i]];
			}else{
				if(V[iv].powancesters[i] != -1)
					answ = V[iv].powancesters[i];
			}
		}
		return answ;		
	}
			
};

void Tree :: compute_powancesters(int iv){
	int iu = parent[iv];
	vertex & v = V[iv], & u = V[iu];
	long long d = 0;
	for(int i = MAXH-1; i >= 0; --i){
		if( v.depth >= d + Powers[i]){
			d += Powers[i];
			if(u.depth >= d){
				v.powancesters[i] = u.powancesters[i];
			}else
				if(v.depth == d) v.powancesters[i] = iv;				
		}
	}
}

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


int main (int argc, char const *argv[])	{
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
	
	if(DEBUG) for(size_t i = 0; i < T.n; ++i){
		cout << i << ": ";
		print_vec(T.V[i].powancesters);
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