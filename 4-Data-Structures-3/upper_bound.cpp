#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>

using namespace std;


int main (int argc, char const *argv[])
{
	set<int> s = {1,3,5,7,9};
	/*for(auto x : s){
		cout << x << " ";
	}
	return 0;*/
	
	auto x = s.upper_bound(6);
		cout << *x << endl;
		--x;
		cout << *x << endl;
		return 0;
	
	/*auto x = s.lower_bound(6);
	cout << *x << endl;
	
	++x;
	cout << *x << endl;
	
	auto x = s.upper_bound(6);
		cout << *x << endl;*/
	
	
	
	auto y = s.find(5);
	
	--y;
	cout << *y << endl;
	
		
}