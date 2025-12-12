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


std::vector<int> boxes;

struct region {
	int w;
	int h;
	std::vector<int> counts;
};

std::vector<region> regions;


int solve()
{
	int total_valid = 0;
	int total_invalid = 0;

	for (auto r : regions) {
		int required_area = 0;
		int required_slots = 0;

		for (int i = 0; i < 6; i++) {
			required_area += r.counts[i] * boxes[i];
			required_slots += r.counts[i];
		}

		// available area too small
		int available_area = r.w * r.h;
		if (available_area < required_area) {
			total_invalid++;
			continue;
		}

		// available area aplenty
		int full_box_slots = (r.w  / 3) * (r.h  / 3);
		if (full_box_slots >= required_slots) {
			total_valid++;
		}
	}

	dump(total_valid);
	dump(total_invalid);

	return total_valid;
}


int main(int argc, char** argv)
{
	std::string s;
	int box;
	for (int i = 0; i < 6; i++) {
		box = 0;
		std::cin >> s; // ignore
		std::cin >> s; for (auto c : s) if (c == '#') box++;
		std::cin >> s; for (auto c : s) if (c == '#') box++;
		std::cin >> s; for (auto c : s) if (c == '#') box++;
		boxes.push_back(box);
	}

	while (true) {
		char x;
		region r;

		std::cin >> r.w >> x;
		std::cin >> r.h >> x;

		for (int i = 0; i < 6; i++) {
			int n;
			std::cin >> n;
			r.counts.push_back(n);
		}

		if (std::cin.fail()) {
			break;
		} else {
			regions.push_back(r);
		}
	}

	dump(regions.size());

	std::cout << "PART 1: " << solve() << std::endl;

	return 0;
}
