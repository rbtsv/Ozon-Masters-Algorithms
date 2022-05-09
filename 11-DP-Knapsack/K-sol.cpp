#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <unistd.h>
#include <cassert>

#define DEBUG false
#define BS_MAX_SIZE 30

using namespace std;

void print_breaker();

struct CWI{
	int cost, weight, ind;
	CWI(){cost = 0; weight = 0; ind = 0;}
	CWI(int c, int w, int i){cost = c; weight = w; ind = i;}
	void print(){ cout << "cost: " << cost << "weight: " << weight << endl; }
};
	


bool dense_desc_order(const CWI &cwi1, const CWI &cwi2 ){
	double d1 = cwi1.cost/(double)cwi1.weight;
	double d2 = cwi2.cost/(double)cwi2.weight;
	//return d1 > d2;
	if(d1 != d2) return d1 > d2;
	return &cwi1 > &cwi2;
}

bool input_order(const CWI &cwi1, const CWI &cwi2 ){	
	return cwi1.ind < cwi2.ind;
}

bool weight_order(const CWI &cwi1, const CWI &cwi2 ){	
	if(cwi1.weight != cwi2.weight) return cwi1.weight < cwi2.weight;
	return &cwi1 < &cwi2;
}

bool desc_cost_order(const CWI &cwi1, const CWI &cwi2 ){	
	if(cwi1.cost != cwi2.cost) return cwi1.weight > cwi2.weight;
	return &cwi1 > &cwi2;
}

void cwi_print(const vector<CWI> &cwi){
	for(vector<CWI>::const_iterator it= cwi.begin(); it != cwi.end(); ++it ){	
		cout << "(" << it->cost << ", " << it->weight <<  ")";
		if((it+1)!=cwi.end()){cout << ",";}else{cout << "\n";}
	}
}


class Solutions{
	int n, W;
	vector<CWI> data, const_data;
	
	struct Sol{
		int cost, weight, n;
		vector<CWI>  cwi, data;
		vector<bool> vbin;
		string name;
		
		void operator += (CWI item){ // sol += cwi_item
			cost += item.cost;
			weight += item.weight;			
			cwi.push_back(item);
			vbin[item.ind] = true;
		}
		
		
		
		bool operator < (const Sol &sec) const{
			if(cost != sec.cost) return cost < sec.cost;
			return &(*this) < &sec;
		}
		
		bool operator > (Sol sec){ return (sec < *this); } 
		
		Sol(){name =""; cost = 0; weight = 0; };
		
		Sol(vector<CWI> d){
			name ="";
			n = d.size();
			data=d;
			cost = 0; weight = 0;			
			vector<bool> tvbin(n,false);
			vbin = tvbin;
		}
		
		Sol(vector<CWI> d, string s){ *this=Sol(d); name = s; }
		
		Sol(vector<CWI> d, vector<CWI> vec){
			*this = Sol(d);
			cwi = vec;
			for(vector<CWI>::iterator it=cwi.begin(); it != cwi.end(); ++it){
				 vbin[(it->ind)-1] = true; 
			}
			for(vector<CWI>::iterator it=cwi.begin(); it != cwi.end(); ++it){ 
				cost+= it->cost; weight+= it->weight; 
			}
			
		}
		Sol(vector<CWI> d, vector<bool> vec){
			*this = Sol(d);
			vbin = vec;
			for(int i = 0; i < n; ++i){ if(vec[i]){ cwi.push_back(data[i]);} }
			for(vector<CWI>::iterator it=cwi.begin(); it != cwi.end(); ++it){
				 cost+= it->cost; weight+= it->weight; 
			}
		}
		
		Sol(vector<CWI> d, vector<bool> vec, string str){
			 *this = Sol(d, vec); name = str;
		 }
		
		void print_data();
		void print_submition_format();
	};
	

	
	
	

public:	
	Solutions(int nn, int WW, vector<CWI> d);
	Sol best;
	
	Sol sol_naive();
	Sol sol_bf();
	
	Sol sol_bf_bitset();
	
	Sol sol_dpW();
	Sol sol_dpW_mem();
	Sol sol_dpW_opt();
	
	
};

void Solutions::Sol::print_submition_format(){
	/*obj opt
	x_0 x_1 x_2 ... x_n-1
	*/	
	cout << cost << " 1\n";
	for(size_t i = 0; i < n; ++i){
		cout << vbin[i] << " ";
	}
	cout << endl;
}



void Solutions::Sol::print_data(){
	cout << name << "\n";
	for(size_t i = 0; i < 50; ++i){cout << "-";}
	cout << endl;
	
	cout << "C: " << cost << " " << "W: " << weight << endl;
	cwi_print(cwi);
	
	print_breaker();
}

void print_breaker(){
	cout << endl;
	for(int i = 0; i < 50; ++i) cout << "=";
	cout <<endl << endl;
}


Solutions::Solutions(int nn, int WW, vector<CWI> d){
	n=nn; W=WW; data=d; const_data = d;
		
	
	sort(data.begin(), data.end(), weight_order );	
	while( data.back().weight > W ) data.pop_back();
	
			
		
}



Solutions::Sol Solutions::sol_naive(){
	sort(data.begin(), data.end(), desc_cost_order);
	Sol Snaive(data, "Naive approximate solution");
	
	//CWI = triple of cost C_i weight W_i and index I
	for(vector<CWI>::iterator it = data.begin(); it != data.end(); ++it){
		if( Snaive.weight + it->weight <= W ){
			Snaive += *it;
		}
	}
	return Snaive;
}

vector<vector<bool> > gen_bool(int n){ // 2^n + 2^{n-1} + 2^{n-2} + ... = 2^{n+1}-1
	vector< vector<bool> > v;
	vector<bool> t; t.push_back(true); 
	vector<bool> f; f.push_back(false);	
	if ( n == 1 ) { 
		v.push_back(f); v.push_back(t);
		return v;
	}else{
		v = gen_bool(n-1); //size == 2^{n-1}
		vector< vector<bool> > rv;
		for(vector< vector<bool> >::iterator it=v.begin(); it != v.end(); ++it ){
			it->push_back(false);
			rv.push_back(*it);
			it->pop_back();
			it->push_back(true);
			rv.push_back(*it);
		}
		return rv;
	}
	
}


Solutions::Sol Solutions::sol_bf(){
	vector <vector<bool> > bf = gen_bool(n);
	vector<bool> cur_sol;
	
	Sol slv(const_data);
	
	for(vector <vector<bool> >::iterator iv=bf.begin(); iv != bf.end(); ++iv){
		Sol cur_sol(const_data, *iv, "Brute-force solution");
		if( cur_sol.weight <= W && cur_sol > slv){ slv = cur_sol;}	
	}
		
	return slv;
}


Solutions::Sol Solutions::sol_bf_bitset(){
	bitset<BS_MAX_SIZE> bs;
	
	int best_sol_weight = 0, best_sol_cost = 0;
	unsigned long long best_sol_ind = 0;
	
	int bs_size = n;
	long long BS=1;
	BS = BS << bs_size;
	
	int w=0, c=0;
	for(unsigned long long i = 0; i < BS-1; ++i){
		int j = 0; // bs[j] == 0 , bs[k < j] == 1
		for(; j <= bs_size && bs[j] == 1; ++j){
			bs[j] = 0; 
			w -= const_data[j].weight;
			c -= const_data[j].cost;
		}
		if(j < bs_size){ 
			bs[j] = 1;
			w += const_data[j].weight;
			c += const_data[j].cost;			
		}
		
		if( (w <= W) && (c > best_sol_cost)){
			best_sol_weight = w;
			best_sol_cost = c;			
			best_sol_ind = i+1;
		}
		
	}
	
	bitset<BS_MAX_SIZE> best_sol = bitset<BS_MAX_SIZE>(best_sol_ind);
	vector<bool> vbin = vector<bool>(n,0);
	for(size_t i = 0; i < n; ++i){
		vbin[i] = best_sol[i];
	}
	
	Sol bf_opt_sol(const_data, vbin, "Brute-force iterative solution");
	assert(best_sol_cost == bf_opt_sol.cost);
	return bf_opt_sol;
}


Solutions::Sol Solutions::sol_dpW(){
	vector<Sol> Wsol(W+1, Sol(data, "Dynamic programming on W"));	
	for(vector<CWI>::iterator it=data.begin(); it != data.end(); ++it){
		int c=it->cost, w=it->weight;
		for(int iw = W; (iw - w) >= 0 ; --iw){
			if(Wsol[iw-w].cost + c > Wsol[iw].cost){
				Wsol[iw] = Wsol[iw-w]; // copy!
				Wsol[iw] += *it;
			}
		}
	}
	
	return Wsol[W];
}



Solutions::Sol Solutions::sol_dpW_opt(){
	vector<vector<bool> > Wbsol(W+1, vector<bool>(n, false) );
	vector<int > DC(W+1, 0); // DC[w] = max cost of knapsack of weight == w (!!!)
	vector<bool> Wexists(W+1, false);	
	Wexists[0] = true;
	
	int max_avail_W = 0;
	
	for(vector<CWI>::iterator it=data.begin(); it != data.end(); ++it){		
		int c=it->cost, w=it->weight;
		max_avail_W = min(max_avail_W + w, W);
		for(int iw = max_avail_W; (iw - w) >= 0 ; --iw){
			if(Wexists[iw-w] && DC[iw-w] + c > DC[iw]){
					DC[iw] = DC[iw-w] + c; 
					Wbsol[iw] = Wbsol[iw-w]; // copy!
					Wbsol[iw][it->ind] = 1;
					Wexists[iw] = true;
			}						
		}
	}
	
	
	int w_best = 0;
	for(int w = W; w > 0; --w){
		if(Wexists[w] && DC[w] > DC[w_best]){			
			w_best = w;
		}
	}
	Sol sol(const_data, Wbsol[w_best], "Dynamic sol W opt");
	return sol;
}
	




int main (int argc, char const *argv[])
{
	/*
		ks_30_0		ks_lecture_dp_1	ks_19_0		ks_50_0		ks_lecture_dp_2
		ks_100_0	ks_200_0	ks_40_0		ks_50_1	ks_45_0		ks_60_0
		ks_100_2	ks_4_0 ks_500_0
	*/	
		
	string test = "ks_30_0";
	string path="./K-tests/";
	if(DEBUG) freopen((path+test).c_str(), "r", stdin); //ks_30_0
		
	
	
	int n; cin >> n;
	int W; cin >> W;
	int Cmax = 0;
	


	
	//cout << n << " " << K << endl;
	cout<< "W = " << W << "\t n=" << n << endl; //O(nW)

	vector<CWI> data;
	for(size_t i = 0; i < n; ++i){
		int cc, ww;
		cin >> cc; cin >> ww;
		Cmax = max(Cmax, cc);
		data.push_back(CWI(cc, ww, i));
	}

	cout<< "Cmax: "<< Cmax << endl;	
	
	cout << "Input:";
	cwi_print(data);
	
	print_breaker();
	
	Solutions run_sol(n, W, data);

		run_sol.sol_naive().print_data(); //approx

		
	if(n <= 30){ // exact 
		//run_sol.sol_bf_bitset().print_data(); 
		//run_sol.sol_bf().print_data();
	}
	
	//run_sol.sol_dpW().print_data();	// exact 
	run_sol.sol_dpW_opt().print_data();
	
	
	
	return 0;
  
}

