#include <bitset>
#include <cassert>
#include <iostream>
#include <set>
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


struct machine {
	int light_diagram;
	std::vector<int> buttons;
};

std::vector<machine> machines;


int convert_to_light_diagram(std::string s) {
	int output = 0;

	int s_len = s.size();
	for (int i = 1; i < (s_len-1); i++) {
		if (s[i] == '#') {
			int bit_num = i - 1;
			output |= 1 << (bit_num);
		}
	}

	return output;
}


int convert_to_button(std::string s) {
	int output = 0;

	int s_len = s.size();
	for (int i = 1; i < (s_len-1); i++) {
		if (s[i] != ',') {
			int bit_num = s[i] - 48;
			output |= 1 << (bit_num);
		}
	}

	return output;
}


std::string to_bits(int i)
{
	std::bitset<16> bits = i;

	return bits.to_string();
}


void print_machine(machine m)
{
	dump(to_bits(m.light_diagram));
	for (int b : m.buttons) dump(to_bits(b));
}


int solve_machine(machine m)
{
	int solution = -1;
	std::set<int> queue;
	queue.insert(0);

	int counter = 0;
	while (counter < 10) {
		counter++;
		std::set<int> new_queue {};
		bool found_solution = false;

		for (auto b1 : queue) {
			for (auto b2 : m.buttons) {
				int l = b1^b2;

				if (l == m.light_diagram) {
					solution = counter;
					found_solution = true;
					break;
				}

				new_queue.insert(l);
			}

			if (found_solution) break;
		}

		if (found_solution) break;
		queue = new_queue;
	}

	return solution;
}


int solve()
{
	std::vector<int> counters;

	for (auto m : machines) {
		int counter = solve_machine(m);
		assert(counter > 0);
		counters.push_back(counter);
	}

	int sum = 0;
	for (auto el : counters) sum += el;

	return sum;
}


int main(int argc, char** argv)
{
	machine m;
	std::string s;

	while (std::cin >> s) {
		if (s[0] == '[') {
			m.light_diagram = convert_to_light_diagram(s);
		} else if (s[0] == '(') {
			m.buttons.push_back(convert_to_button(s));
		} else if (s[0] == '{') {
			machines.push_back(m);
			m.light_diagram = 0;
			m.buttons.clear();
		}
	}

	std::cout << "PART 1: " << solve() << "\n";
	//std::cout << "PART 2: " << solve2() << "\n";

	return 0;
}
