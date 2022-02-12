#include<iostream>
#include<vector>

using namespace std;

int main (int argc, char const *argv[])
{
	int n, x, m;
	vector <int> a;
	vector <vector<int> > ar;
	cin >> n;
	for( int i = 0; i < n; ++i){ 
		cin >> x;
		a.push_back(x);
	}

	
	ar.resize(n+1);
	
	for( int i = 0; i < n; ++i){ 
		ar[i].resize(n+1);
		for( int j = 0; j < n; ++j){
			if(a[i] >= a[j] ){ ar[i][j] = 1; } //Заполнение массива ar
			else{ ar[i][j] = 0; }			
		} 
	}	
	for( int i = 0; i < n; ++i){ 
		int flag;
		flag = 0;
		for( int j = 0; j < n; ++j){
			//		cout << ar[i][j];
			if( ar[i][j] == 0 ){ flag++; }
		}
//		cout << endl;
		if(flag == 0){ m = a[i]; }
	}

	cout << m << endl;
	
	return 0;
}