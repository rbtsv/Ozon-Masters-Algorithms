#include<iostream>

using namespace std;

void print_anything(void * any){
	//int* thing = (int*) any; 
	cout << "any:" << *((int*) any) << endl;
}

template <typename C> void p_anything(C *any){
	//int* thing = (int*) any; 
	cout << "any:" << *any << endl;
}


int main (int argc, char const *argv[]){
	int x, y, *px, *py;
	int &lx = x; // lx = *(px)
	const int &ly = y;		
	
	px = &x;
	py = &y;
	
	x = 7;
	y = -1;
	y = 12; cout << y << " " << *py << " " << ly << endl;
	py = &x;
	//ly = 13;
	y = 12; cout << y << " " << *py << " " << ly << endl;
	//return(0);
	
	//x = 10; cout << x << " " << px << " " << *px << " " << endl;	
	x = 10; cout << x << " " << *px << " " << lx << endl;
	//return(0);
	lx = 11; px = &y; cout << x << " " << *px << " " << lx << endl;
	//system("open link-pointer.jpeg");
	//system("open pointer-pointer.jpeg");
	//system("open int_star.jpeg");
	//system("open void_star.jpeg"); 
	
	//ly = 11;
	print_anything(&y);
	p_anything<int>(&y);
	
		
	return 0;
}