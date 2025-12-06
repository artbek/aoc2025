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

struct operation {
	char op_sign;
	int op_index;
};

std::vector<std::string> lines;
std::vector<std::vector<int>> numbers;
std::vector<operation> ops;


auto get_col_numbers(int col_id, int version)
{
	std::vector<int> nums;

	if (version == 1) {

		for (auto n : numbers) nums.push_back(n[col_id]);

	} else {

		int line_len = lines[0].size();
		int start_offset = ops[col_id].op_index;

		for (int i = start_offset; i < line_len; i++) {
			std::string num_str;
			for (auto ln : lines) {
				if (ln[i] != ' ') num_str += ln[i];
			}

			if (num_str.size() == 0) break;

			nums.push_back(std::stoi(num_str));
		}

	}

	return nums;
}


ll get_col_total(int col_id, int version)
{
	ll col_total = 0;
	char op = ops[col_id].op_sign;

	if (op == '+') col_total = 0;
	else col_total = 1;

	auto col_numbers = get_col_numbers(col_id, version);

	if (op == '+') {
		for (auto n : col_numbers) col_total += n;
	} else {
		for (auto n : col_numbers) col_total *= n;
	}

	return col_total;
}


ll find_total_sum(int version)
{
	ll sum = 0;

	int cols_count = ops.size();

	for (int c = 0; c < cols_count; c++) {
		sum += get_col_total(c, version);
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
		std::string ops_line = lines[line_count - 1];

		int line_len = lines[0].size();
		for (int i = 0; i < line_len; i++) {
			if (ops_line[i] != ' ') ops.push_back({ops_line[i], i});
		}
	}

	std::cout << "PART 1: " << find_total_sum(1) << "\n";
	std::cout << "PART 2: " << find_total_sum(2) << "\n";

	return 0;
}
