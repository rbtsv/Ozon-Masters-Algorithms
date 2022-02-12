#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char const *argv[]){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	freopen("tsort", "r", stdin);
	int t;
	cin >> t;
	
	for(size_t i = 0; i < t; ++i){
		int n;
		cin >> n;
		vector <int> v(n,0);
		//v.resize(n);
		for(size_t i = 0; i < n; ++i){
//			int c;
//			cin >> c;			
//			v.push_back(c); // (1, 1) -> (2, 2) -> (3, 4) -> (4,4) -> (5, 8) log_2(n) 
			cin >> v[i];
		}
		sort(v.begin(), v.end());	
		for(size_t i = 0; i < n; ++i){
			cout << v[i] << " ";
		}
		cout << "\n";		
	}
	
	
	return 0;
}
