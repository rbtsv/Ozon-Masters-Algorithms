#include <iostream>
#include <algorithm>

std::pair<int, int> max_two(int n, std::pair<int, int> m12){
	int c;
	if(n == 0) return m12;		
	std::cin >> c;
	std::pair<int, int> p = (c > m12.first) ? std::make_pair(c, m12.first)
											: std::make_pair(m12.first, std::max(c, m12.second));
	return max_two(n-1, p);
}

int main (int argc, char const *argv[])
{
	std::ios::sync_with_stdio(false); std::cin.tie(0);
	int n, a, b;
	
	std::cin >> n >> a >> b;
	std::pair<int, int> m12 = std::make_pair(std::max(a, b), std::min(a, b));
			
	m12 = max_two(n-2, m12);
		
	std::cout << ((long long) m12.first) * ((long long) m12.second) << "\n";
	
	return 0;
}
