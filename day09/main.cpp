#include <algorithm>
#include <iostream>
#include <vector>

#define dump(x) \
		std::cout << #x << "=" << x << std::endl;

#define dumpv(x) \
		std::cout << #x << ": "; \
		for (auto el : x) std::cout << el << " "; \
		std::cout << std::endl;

#define dumpm(x) \
		std::cout << #x << ": "; \
		for (auto [k,v] : x) std::cout << "[" << k << "]: " << v << ", "; \
		std::cout << std::endl;

#define dumpp(x) \
		std::cout << #x << ": "; \
		std::cout << "(" << x.first << ", " << x.second << ")"; \
		std::cout << std::endl;


using ll = long long;


std::vector<std::pair<int,int>> tiles;


ll solve()
{
	std::vector<ll> areas;

	int tiles_count = tiles.size();

	for (int i = 0; i < tiles_count; i++) {
		for (int j = i + 1; j < tiles_count; j++) {
			auto t1 = tiles[i];
			auto t2 = tiles[j];
			ll w = std::abs(t1.first - t2.first) + 1;
			ll h = std::abs(t1.second - t2.second) + 1;
			areas.push_back(w * h);
		}
	}

	auto max_area = std::max_element(areas.begin(), areas.end());

	return (*max_area);
}


int main(int argc, char** argv)
{
	int r, c;
	char comma;

	while (std::cin >> c) {
		std::cin >> comma >> r;
		tiles.push_back({r,c});
	}

	std::cout << "PART 1: " << solve() << "\n";

	return 0;
}
