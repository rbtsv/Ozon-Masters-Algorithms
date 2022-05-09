#include<iostream>
#include<algorithm>
#include<vector>

#define DEBUG true

#define Next 1
#define Prev 0

using namespace std;

template<class C> void pr_2d_xy_vec(const vector<C> &field){ 
	int N = field.size() -1;
	for(int j = N; j >= 0; --j){
		for(size_t i = 0; i <= N; ++i){
						cout << field[i][j] <<  " ";
		}
		cout << endl;
	}
	
}
	
struct Sol{
	int N, M;
	long Rsq;	
	const vector<pair<int,int> > & moves;	
	
	/* Sol(int NN, int RR, int MM, long RRsq, const vector<pair<int,int> > * mmoves){
		N = NN; R= RR; M = MM; Rsq = RRsq; pmoves = mmoves;
	}*/
	
	Sol(int NN,  int MM, long RRsq, const vector<pair<int,int> > & mmoves) :
			N{NN},  M{MM}, Rsq{RRsq}, moves(mmoves) {}
	
	bool operator ()(){ return comp_pos(0,0); }
	
	bool comp_pos(int x, int y){
		cout << "Wrong Function!" << endl;
		return Prev; // remove
	}
	
};

struct RecursiveSol : public Sol{
	
	using Sol::Sol;
	
	bool operator ()(){ return comp_pos(0,0); }
	
	bool comp_pos(int x, int y){
		//cout << "Here\n";
		if(x*x +y*y >= Rsq) return Prev;
		for(auto [xx, yy] : moves)
			if(x + xx <= N && y + yy <= N && comp_pos(x+xx, y+yy) == Prev) 
				return Next;			
		
		return Prev;
	}
};


struct DPsol{
	int N, M;
	long Rsq;	
	const vector<pair<int,int> > & moves;
	vector<vector<bool> > & field; // Result: Next or Prev
	vector<vector<bool> > & computed; // Result was computed (or not)
	
	/* Sol(int NN, int RR, int MM, long RRsq, const vector<pair<int,int> > * mmoves){
		N = NN; R= RR; M = MM; Rsq = RRsq; pmoves = mmoves;
	}*/
	
	DPsol(int NN,  int MM, long RRsq, const vector<pair<int,int> > & mmoves, 
		vector<vector<bool> > & ffield, vector<vector<bool> > & ccomputed) :
			N{NN},  M{MM}, Rsq{RRsq}, moves(mmoves), field(ffield), computed(ccomputed)  {}
	
	bool operator ()(){ return comp_pos(0,0); }
	
	bool comp_pos(int x, int y){
		if(computed[x][y]) return field[x][y];
		if(x*x +y*y >= Rsq) field[x][y] = Prev;
		else{
			field[x][y] = Prev;
			for(auto [xx, yy] : moves)
				if(x + xx <= N && y + yy <= N && comp_pos(x+xx, y+yy) == Prev) 
					field[x][y] = Next;					
					//break;
		}
		computed[x][y] = true;
		return field[x][y];
	}
	
};


int main (int argc, char const *argv[]){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	if(DEBUG) freopen("./tests/1", "r", stdin);
		
	int N, R, M;
	cin >> N >> R >> M;
	long Rsq = R*R;
	
	// 0 == Prev, 1 == Next 
	
	vector<pair<int, int> > moves;
	for(size_t i = 0; i < M; ++i){
		int x, y;		
		cin >> x >> y;
		//if(DEBUG) cout << x << ", " << y << endl;
		moves.emplace_back(x, y);
	}
	

	RecursiveSol rec_sol(N, M, Rsq, moves);
			
	if(DEBUG) cout << ((rec_sol() == Prev) ?  "2\n" : "1\n");	
	

	if(DEBUG){
		vector<vector<bool> > field = vector<vector<bool> >(N+1, vector<bool>(N+1, 0)); 
		vector<vector<bool> > computed = vector<vector<bool> >(N+1, vector<bool>(N+1, 0));
		DPsol dp_sol(N, M, Rsq, moves, field, computed);
		cout << ((dp_sol() == Prev) ?  "2\n" : "1\n");		
	
		cout << "Dp sol field:\n";
		pr_2d_xy_vec(dp_sol.field);
		cout << "\n";
		cout << "Dp sol computed:\n";
		pr_2d_xy_vec(dp_sol.computed);
 	}
	
	vector<vector<bool> > field = vector<vector<bool> >(N+1, vector<bool>(N+1, 0)); 
	
	for(int diag = 2*N; diag >= 0; --diag){
		for(int y = min(diag, N), x = diag - y; y >= 0 && x <= N  ; --y){
			field[x][y] = Prev; 
			if(x*x + y*y >= Rsq) continue; 
			for(auto [xx, yy] : moves)
				if( x + xx <= N && y + yy <= N && field[x+xx][y+yy] == Prev ){ 
					field[x][y] = Next;					
					break;
				}				
		}		
	}
	
	if(DEBUG){
		cout << "\n";
		cout << "Iter sol field:\n";
		pr_2d_xy_vec(field);
		cout << endl;
	}
	
	cout << ((field[0][0]  == Prev) ?  "2\n" : "1\n") << endl;
			
	
	return 0;
}