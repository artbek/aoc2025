#include <iostream>

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


void part1()
{
	int counter = 0;

	int state = 50;

	char op;
	int num;

	while (std::cin >> op) {
		std::cin >> num;

		if (op == 'L') state -= num;
		else state += num;

		state %= 100;
		if (state < 0) state += 100;
		if (state == 0) counter++;
	}

	dump(counter);
}


void part2()
{
	int counter = 0;

	int state = 50;

	char op;
	int num;

	while (std::cin >> op) {
		std::cin >> num;

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

	dump(counter);
}


int main()
{
	//part1();
	part2();

	return 0;
}
