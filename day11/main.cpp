#include <iostream>
#include <map>
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

std::map<std::string, std::vector<std::string>> devices;


std::map<std::string, ll> ways;

ll find_path(std::string src, std::string dst)
{
	if (ways[src]) {
		return ways[src];
	}

	ll total_paths = 0;

	for (auto & el : devices[src]) {
		if (el == dst) {
			total_paths += 1;
		} else {
			total_paths += find_path(el, dst);
		}
	}

	ways[src] = total_paths;

	return total_paths;
}


int main(int argc, char** argv)
{
	std::string s;

	std::string key;
	while (std::cin >> s) {
		if (s.back() == ':') {
			s.pop_back();
			key = s;
			continue;
		}
		devices[key].push_back(s);
	}

	auto answer = find_path("you", "out");
	std::cout << "PART 1: " << answer << std::endl;

	ways.clear();
	ll p1 = find_path("dac", "out");
	ways.clear();
	ll p2 = find_path("fft", "dac");
	//ways.clear();
	//ll p3 = find_path("fft", "svr");

	auto answer2 = p1 * p2;// * p3;
	std::cout << "PART 2: " << answer2 << std::endl;

	return 0;
}
