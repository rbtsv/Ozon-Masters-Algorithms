#include<iostream>
#include<stack>
#include<vector>
#include<deque>

using namespace std;

int main (int argc, char const *argv[])
{
	stack<int, deque<int> > st;
	vector<int> vst;
	deque<int> d;
	
	for(size_t i = 0; i < 10; ++i){
		vst.push_back(i);
		d.push_back(i);
		st.push(i);
	}
	
/*	for(size_t i = 0; i < 10; ++i){
		cout << st[i] << endl;
//		d.push_back(i);
//		st.push(i);
	}*/
	
	
	//return 0;
	
	cout << "Deque:\n";
	
	d.pop_back();
	d.pop_front();
	/**/
	for(auto & x : d){
		cout << x << " ";
		x *= 2;
	}
	cout << endl;
	for(deque<int>::iterator it = d.begin(); it != d.end(); ++it){		
			cout << *it << "\n";
			//*it *= 2;
	}
	
	cout << "Empty Deque:\n";
	//int t = d.size();
	for(size_t i = 0; i < d.size(); ++i){
		cout << d.back() << "\n";
		d.pop_back();
		//cout << static_cast<int>(d.back()) << " ";		
	}
	cout << "Eof Deque\n";
	
	
	
	st.pop();
	vst.pop_back();
	//vst.pop_front();
	vst.erase(vst.begin()); // vst.erase(vst.begin()+k); O(vst.size()-k)
	cout << st.top() << endl;
	cout << vst.back() << endl;
	cout << "Vector stack:\n";
	for(size_t i = 0; i < vst.size(); ++i){
		cout << vst[i] << "\n";
	}
	cout << "Empty vector:\n";
	//for(vector<int>::iterator it = vst.end()-1; it != vst.begin(); --it){				
	
	//bad example!
	for(vector<int>::iterator it = vst.begin(); it != vst.end();){				
		cout << *it << "\n";
		vst.erase(it++);
	}
	
	cout << "vst.size: " << vst.size() << endl;
	
	for(vector<int>::reverse_iterator it = vst.rbegin(); it != vst.rend(); ++it){				
		cout << *it << "\n";		
		//vst.erase(it++);
	}
	
	cout << "vst.size: " << vst.size();
	
	return 0;
}

