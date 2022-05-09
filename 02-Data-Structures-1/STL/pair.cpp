#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>

using namespace std;

struct CmpSecond{
	bool operator( )(const pair<string, int> & x, const pair<string, int> &y  ) const {
		if( x.second < y.second ) return true;
		if( x.second > y.second ) return false;
		return x.first < y.first;
	}
};


int main (int argc, char const *argv[])
{
	std::pair<int, int> p1, p2;
	p1 = make_pair(1,2);
	p2 = make_pair(2,3);
	cout << p1.first << " " << p1.second << endl;
	int a, b;
	tie(a, b) = p2;
	cout << a << " " << b << endl;	
	
	cout << (p1 < p2) << endl; // False == 0, True == не 0
	
	return 0;
	set<pair<string, int>, CmpSecond> s;	
	s.insert(make_pair("Z", 17));
	s.insert(make_pair("C", 10));
	s.insert(make_pair("A", 13));
	s.insert(make_pair("B", 13));
	s.insert(make_pair("A", 1));
	//s.emplace("A", 1);
	
	//CmpSecond cmp;
	//cout << cmp(make_pair("A", 13), make_pair("Z", 17));
	
	//return 0;
	
	//cout << s.size();
	for(set<pair<string, int>  >::iterator it = s.begin() ; it != s.end(); ++it){ //s[i] is not defined
		cout << "(" << it->first << "," << (*it).second << ")" << " "; 
	}
	cout << endl;	
	
	
	for(auto & x : s){
		cout << "(" << x.first << "," << x.second << ") ";
		//x.second+=1;
	}
	cout << endl;
	
	for(auto & [first, second] : s){
		cout << "(" << first << "," << second << ") ";
		//x.second+=1;
	}
	cout << endl;
	
	vector<int> v = {1,2,3,4,5};
	for(auto & x : v){
		cout << x++ << " ";
	}
	cout << endl;
	for(auto & x : v){
		cout << x << " ";
	}
	cout << endl;
		
	vector<pair<int, int> > vv = {make_pair(1,1), make_pair(2,3)};
	for(auto & x : vv){
		cout << ++x.first << " ";
	}
	
	return 0;
}