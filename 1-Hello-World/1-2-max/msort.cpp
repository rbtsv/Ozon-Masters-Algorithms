#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char const *argv[])
{
	freopen("t1", "r", stdin);
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
	cout << v.back() << endl;
	return 0;
}
