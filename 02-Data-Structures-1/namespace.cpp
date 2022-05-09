#include<iostream>

namespace One{
	struct int_pair{
		int first;
		int second;
	};
}

namespace Two{
	struct int_pair{
		bool flag;
		int first;
		int second;
	};
}


using std::cout, std::endl;
using namespace Two;

int main (int argc, char const *argv[]){
	
	//One::int_pair pair;
	int_pair pair;
	pair.first = 1; pair.second = 2;
	
	cout << pair.first << " " << pair.second << endl;
	
	return 0;
	
	int x=7, vector=5;
	for(size_t i = 0; i < 5; ++i){
		int x=i;
		cout << i;
		//...
	}
	std::vector<int> v = {1, 2, 3};
	cout << endl << x << " " << vector << " " << v[0] << endl;	
}