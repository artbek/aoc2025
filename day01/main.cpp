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

const int MOD = 100;


std::vector<std::pair<char,int>> input;


int part1()
{
	int counter = 0;

	int state = 50;

	for (auto [op, num] : input ) {
		if (op == 'L') state -= num;
		else state += num;

		state %= 100;
		if (state < 0) state += 100;
		if (state == 0) counter++;
	}

	return counter;
}


int part2()
{
	int counter = 0;

	int state = 50;

	for (auto [op, num] : input ) {
		int prev_state = state;

		if (op == 'L') state -= num;
		else state += num;

		if (prev_state < 0  && state > 0) counter++;
		if (prev_state > 0  && state < 0) counter++;

		bool modified = false;

		if (state > MOD) {
			counter += (state / MOD);
			modified = true;
		} else if (state < -MOD) {
			counter += (state / -MOD);
			modified = true;
		}

		state %= 100;
		if (state < 0) state += 100;

		if (! modified && state == 0) counter++;
	}

	return counter;
}


int main()
{
	char op;
	int num;

	while (std::cin >> op) {
		std::cin >> num;
		input.emplace_back(op, num);
	}

	std::cout << "PART 1: " << part1() << "\n";
	std::cout << "PART 2: " << part2() << "\n";

	return 0;
}
