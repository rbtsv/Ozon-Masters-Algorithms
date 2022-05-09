#include <iostream>
#include <algorithm>

using namespace std;

int main (){
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	//freopen("tm2", "r", stdin);
	//std::cout << "HW!" << std::endl;
	//cout << "HW!" << "\n";
	int n, a, b;
	long long max1, max2;
	cin >> n >> a >> b;
	max1 = max(a,b);
	max2 = min(a,b);
	for(int i = 0; i < n-2; ++i){ // ++i == i += 1 == (i = i + 1)
		int c;
		cin >> c;
		if( c > max1){
			max2 = max1;
			max1 = c;
		}else max2 = std::max(max2, (long long) c);
	}
	
	cout <<  max1 * max2 << endl;
	//cout << (long long) max1 *  (long long) max2 << endl;
	
	return 0;
}

