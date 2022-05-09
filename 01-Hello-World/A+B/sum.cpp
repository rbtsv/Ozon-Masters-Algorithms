#include <iostream>

using namespace std;

int main (int argc, char const *argv[])
{
	// std::ios::sync_with_stdio(false); std::cin.tie(0); /// NONONONO!
	int n, a, b;
	
	cin >> n;
	
	for(int i = 0; i < n; ++i){
		cin >> a;
		cin >> b;
		cout << a+b << endl; // endl != "\n"
		cout.flush();	// to make sure output doesn't stuck in some buffer
	}
	
	return 0;
}