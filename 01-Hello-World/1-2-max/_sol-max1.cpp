#include <iostream>
#include <algorithm>

using namespace std;

int main (){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	//freopen("t1", "r", stdin);
	//std::cout << "HW!" << std::endl;
	//cout << "HW!" << "\n";
	int n, max1;
	cin >> n >> max1;
	for(int i = 0; i < n; ++i){ // ++i == i += 1 == (i = i + 1)
		int c;
		cin >> c;
		max1 = std::max(c, max1);
	}
	cout << max1 << endl;
	
	return 0;
}

