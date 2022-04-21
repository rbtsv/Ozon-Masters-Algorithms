#include <iostream>
#include <sstream>
#include <string>

#include <algorithm>
#include <vector>


#define DEBUG true
#define INFTY 10050000000


using namespace std;

struct Node{
	long long val;
	int pos;	
	int	left_ind;
	int	right_ind;
	void print_node(){
		cout << "pos: " << pos << " val: " << val << "li: " << left_ind << "ri: " << right_ind; 
	}
};

struct SegTree{
	int n, N, m; // n — input size -> 2-power, N — total tree size, m — index of the first leaf
	vector<long long> inp;
	vector<Node> tree; // first index is 0
	
	Node left(Node v){ return tree[2*(v.pos+1)-1]; }
	Node right(Node v){ return tree[2*(v.pos+1)]; }
	Node parent(Node v){ if(is_root(v)){ return tree[0]; }
		 				 return tree[(v.pos+1)/2 - 1]; }
	
	bool is_root(Node v){ return (v.pos == 0); }
	
	
	long long RMQ(int l, int r){
		Node vl = tree[m+l], vr = tree[m+r];
		
		if(DEBUG) cout << "vl.pos: " << vl.pos+1 << " " << "vr.pos: " << vr.pos+1 << "\n";
		
		Node midl = vl, midr = vr;
		long long minl = vl.val, minr = vr.val;
		
		while(!is_root(midl) && parent(midl).right_ind <= r){
			midl = parent(midl);
			if(right(midl).left_ind >= l) minl = min(minl, right(midl).val); 
		}
		
		while(!is_root(midr) && parent(midr).left_ind >= l){
			midr = parent(midr);
			if(left(midr).right_ind <= r) minr = min(minr, left(midr).val); 
		}
		
		return min(minl, minr);
	}
	
	SegTree(const vector<long long> &Inp){//Asume that inp contain the initial array;
		inp = Inp;
		for(N=1; N < inp.size(); N <<= 1 );
		for(;inp.size() < N; inp.push_back(INFTY) );
		n = N;
		m = N-1;
		N += n-1;// N = 2^{h+1} - 1 = 2^h(==n) + 2^h -1 
		
		tree.resize(N);
		
		for(int i = 1; i <= n; ++i ){
			Node v;
			v.pos = N-i; v.left_ind = n-i; v.right_ind = n-i;
			v.val = inp[n-i];
			tree[N-i] = v;
		}
		
		for(int pos = m-1; pos >= 0; --pos ){
			Node v;
			v.pos = pos; v.left_ind = left(v).left_ind; 
			v.right_ind = right(v).right_ind;
			v.val = min(left(v).val, right(v).val);

			tree[pos] = v;			
		}
		
	}
	
};


void print_vec(vector<long long> v){
	//cout <<"print_vec: ";
	for(vector<long long>::iterator it=v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
	cout << "\n";
}

void print_subtree(SegTree * st, int ind, int d, stringstream * TrStream){
	*TrStream << "([level"<< d <<"]{$" << st->tree[ind].val << "_{" << st->tree[ind].pos+1 << "}$}";
	if( 2*(ind+1) < st->N ){
		print_subtree(st, 2*(ind+1)-1, d+1, TrStream);
		print_subtree(st, 2*(ind+1), d+1, TrStream);
	}
	*TrStream << ") ";
}


void print_tree(SegTree *st){
	
	stringstream TrStream;
	print_subtree(st, 0, 0, &TrStream);
	
	string tree_str = TrStream.str();
	
	//cout << tree_str;
	
	string cmd = "echo '" + tree_str + "' | ruby to_tree.rb";
	
	//cout << cmd;
	
	system(cmd.c_str());
		
}


int main ( )
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	if(DEBUG) freopen("./tests/01", "r", stdin);	
	
	
	long long n;	
	cin >> n;
	vector<long long> inp;
	
	for(size_t i = 0; i < n; ++i){
		long long x;
		cin >> x;
		inp.push_back(x);
	}
	
		
	SegTree st(inp);
	
	//print_vec(st.inp);
	
	if(DEBUG) print_tree(&st);
	
	
	
	int m; //the number of queries
	cin >> m;
	
	for(long long i = 0; i < m; ++i){
		int l, r;
		cin >> l >> r;
		if(DEBUG) cout << "l: " << l << " r: " << r << "\n";
		cout << st.RMQ(l-1, r-1);
		cout << "\n";
		if(DEBUG) cout << "\n";
	}
	
	return 0;
}