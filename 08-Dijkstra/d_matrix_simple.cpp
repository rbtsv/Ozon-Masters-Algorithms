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
	vector<vector<unsigned int> > W; // int x = _0_11001 бит знака y = _1_11001 => y = -x;  _0_11...1+ 1
									// unsigned int INFTY = -1; 11111;   
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


	
struct Dijkstra{
	Graph *G;
	int n;
	int s;
	unsigned int M1;
	
	vector<unsigned int> dist;	
	vector<bool> completed;
	
	Dijkstra(Graph *GG, int ss){
		M1=-1;
		G = GG;
		n = G->V.size();
		s = ss-1;
		dist = vector<unsigned int>(n, M1);
		dist[s] = 0;
		completed = vector<bool>(n, false);
	}	
	
	void operator ()();
	
	void Relax(int u, int v){
		if(dist[v] > dist[u] + G->W[u][v]) 
		   dist[v] = dist[u] + G->W[u][v]; 
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
		while( true ){
			int u = 0; for(; completed[u] && u < n; ++u);
			if( u == n) break;
			
			for(int v = u; v < n; ++v)
				if(dist[v] < dist[u] && !completed[v]) u = v;
			if(dist[u] == M1) break;
			
			completed[u] = true;
			for(auto v : G->neighbours(u))
			  		Relax(u, v); 										
			//cout << "Tst:" << u << endl;
		}			
	}

int main (int argc, char const *argv[])	
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);	
	//freopen( "m0", "r", stdin);
		
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