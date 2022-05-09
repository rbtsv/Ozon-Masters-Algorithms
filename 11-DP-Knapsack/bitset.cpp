#include <iostream>       
#include <bitset>         
using namespace std;


int main (int argc, char const *argv[])
{
	const int bs_max_size = 10;
	bitset<bs_max_size> bs;
	
	int bs_size = 3;
	int BS=1;
	BS = BS << bs_size;
	
	cout << "2^{bs_size} = " << BS << endl;
	cout << bs << endl;
	
	for(long long i = 0; i < BS-1; ++i){
		int j = 0; // bs[j] == 0 , bs[k < j] == 1
		for(; j <= bs_size && bs[j] == 1; ++j){bs[j] = 0;}
		if(j < bs_size) bs[j] = 1;
		
		cout << i+1 << ": ";
		
		for(size_t j = 1; j <= bs_size; ++j){
			cout << bs[bs_size-j];			
		}cout << endl;
		//cout << bs << endl;
		
	}
	
	return 0;
}