#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	int count;
	vector <int> v;
	cin >> count;
	for(int i = 0; i < count; ++i)
	{ 	
		int x;		
		cin >> x;
		v.push_back(x);
	}
	sort(v.begin(), v.end());
	cout << v.back() << '\n';
	return 0;
}