#include <iostream>
#include <algorithm>

using namespace std;

int main (int argc, char const *argv[]){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	//freopen("t4", "r", stdin);
	int n, prev, cur, len=1, max_len=1;
	cin >> n >> prev;
	cout << max_len << "\n";	
	for(size_t i = 1; i < n; ++i){
		cin >> cur;
		if(cur >= prev) ++len;
		else len = 1;
		max_len = max(len, max_len);
		cout << max_len << "\n";
		prev = cur;
	}
	return 0;
}