#include <iostream>
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

using ll = long long;


std::vector<std::pair<ll,ll>> input;
std::vector<ll> invalid_ids;


bool has_repeating_parts(ll n)
{
	bool found_rep = false;

	auto s = std::to_string(n);
	int s_size = s.size();

	if (s_size % 2 == 0) {
		int mid_point = s_size/2;
		std::string l = s.substr(0, mid_point);
		std::string r = s.substr(mid_point, mid_point);

		if (l == r) found_rep = true;
	}

	return found_rep;
}


bool has_repeating_parts_multi(ll n)
{
	bool found_rep = false;

	auto s = std::to_string(n);
	int s_size = s.size();
	int max_part_size = s_size/2;

	for (int part_size = 1; part_size <= max_part_size; part_size++) {
		std::string prev = "";
		found_rep = true;

		for (int offset = 0; offset < s_size; offset += part_size) {
			std::string cur = s.substr(offset, part_size);
			if (prev != "" && cur != prev) {
				found_rep = false;
				break;
			}

			prev = cur;
		}

		if (found_rep) break;
	}

	return found_rep;
}


void solve_part_number(int part_number)
{
	invalid_ids.clear();

	for (auto [first, last] : input) {
		for (ll i = first; i <= last; i++) {
			if (part_number == 1) {
				if (has_repeating_parts(i)) invalid_ids.push_back(i);
			} else {
				if (has_repeating_parts_multi(i)) invalid_ids.push_back(i);
			}
		}
	}

	ll sum = 0;
	for (auto el : invalid_ids) sum += el;

	std::cout << "PART " << part_number << ": " << sum << "\n";
}


int main()
{
	ll first;
	ll last;
	char c;

	while (std::cin >> first) {
		std::cin >> c >> last >> c;
		input.emplace_back(first, last);
	}

	solve_part_number(1);
	solve_part_number(2);

	return 0;
}
