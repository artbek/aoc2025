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

ll paths_counter = 0;


void find_path(std::string key)
{
	for (auto & el : devices[key]) {
		if (el == "out") {
			paths_counter++;
			break;
		} else {
			find_path(el);
		}
	}

	return;
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

	//for (auto [k,v] : devices) {
	//	dump(k);
	//	dumpv(v);
	//}

	find_path("you");
	std::cout << "PART 1: " << paths_counter << "\n";
	//std::cout << "PART 2: " << solve2() << "\n";

	return 0;
}
