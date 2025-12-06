#include <iostream>
#include <sstream>
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

std::vector<std::string> lines;
std::vector<std::vector<int>> numbers;
std::vector<char> ops;


auto get_col_numbers(int col_id)
{
	std::vector<int> nums;

	for (auto n : numbers) {
		nums.push_back(n[col_id]);
	}

	return nums;
}


ll get_col_total(int col_id)
{
	ll col_total = 0;
	char op = ops[col_id];

	if (op == '+') col_total = 0;
	else col_total = 1;

	auto col_numbers = get_col_numbers(col_id);

	if (op == '+') {
		for (auto n : col_numbers) col_total += n;
	} else {
		for (auto n : col_numbers) col_total *= n;
	}

	return col_total;
}


ll find_total_sum()
{
	ll sum = 0;

	int cols_count = ops.size();

	for (int c = 0; c < cols_count; c++) {
		sum += get_col_total(c);
	}

	return sum;
}


int main()
{
	std::string ln;
	while (std::getline(std::cin, ln)) {
		lines.push_back(ln);
	}

	int line_count = lines.size();

	// Extract the numbers:
	for (int l = 0; l < line_count - 1; l++) {
		std::istringstream input;
		input.str(lines[l]);

		std::vector<int> temp_nums;

		int i;
		while (input >> i) temp_nums.push_back(i);
		numbers.push_back(temp_nums);
	}

	// Extract the operations:
	{
		std::istringstream input;
		input.str(lines[line_count - 1]);

		char op;
		while (input >> op) ops.push_back(op);
	}

	std::cout << "PART 1: " << find_total_sum() << "\n";
	//std::cout << "PART 2: " << find_total_sum2() << "\n";

	return 0;
}
