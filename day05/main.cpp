#include <iostream>
#include <algorithm>
#include <vector>

#define dump(x) \
		std::cout << #x << "=" << x << "\n";

#define dumpv(x) \
		std::cout << #x << ": "; \
		for (auto el : x) std::cout << el << " "; \
		std::cout << "\n";

#define dumpm(x) \
		std::cout << #x << ": "; \
		for (auto [k,v] : x) std::cout << "[" << k << "]: " << v << ", "; \
		std::cout << "\n";

#define dumpp(x) \
		std::cout << #x << ": "; \
		std::cout << "(" << x.first << ", " << x.second << ")"; \
		std::cout << std::endl;


using ll = long long;
using range = std::pair<ll,ll>;

std::vector<range> ranges;
std::vector<ll> vals;


int find_fresh()
{
	int total = 0;

	for (auto v : vals) {
		for (auto [left,right] : ranges) {
			if (v >= left && v <= right) {
				total++;
				break;
			}
		}
	}

	return total;
}


void trim_range(range & trimmed, range remove)
{
	auto [l1,r1] = trimmed;
	auto [l2,r2] = remove;

	if (r1 < l2 || r2 < l1) {
		// no overlap
	} else {
		trimmed = {r2+1, r1};
	}
}


ll find_fresh2()
{
	ll total_add = 0;

	int ranges_count = ranges.size();

	for (int i = 0; i < ranges_count; i++) {
		range trimmed = ranges[i];
		for (int ii = 0; ii < i; ii++) {
			trim_range(trimmed, ranges[ii]);
			if (trimmed.first > trimmed.second) break;
		}
		if (trimmed.first <= trimmed.second) {
			total_add += trimmed.second - trimmed.first + 1;
		}
	}

	return total_add;
}


int main()
{
	ll left, right;
	char c;
	while (std::cin >> left) {
		if (! left) break;
		std::cin >> c >> right;
		ranges.emplace_back(left, right);
	}

	ll val;
	while (std::cin >> val) {
		vals.push_back(val);
	}

	std::sort(ranges.begin(), ranges.end());

	std::cout << "PART 1: " << find_fresh() << "\n";
	std::cout << "PART 2: " << find_fresh2() << "\n";

	return 0;
}
