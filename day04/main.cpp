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


std::vector<std::string> input;
std::vector<std::pair<int,int>> rolls_to_remove;


int count_valid_rolls()
{
	int valid_rolls = 0;

	int c_count = input.back().size();
	int r_count = input.size();

	std::pair<int,int> offsets[] = {
		{-1,-1}, {-1, 0}, {-1,+1},
		{ 0,-1},          { 0,+1},
		{+1,-1}, {+1, 0}, {+1,+1},
	};

	for (int r = 0; r < r_count; r++) {
		for (int c = 0; c < c_count; c++) {
			if (input[r][c] != '@') continue;

			int counter = 0;
			for (auto [dr,dc] : offsets) {
				if (r+dr < 0 || c+dc < 0) continue;
				if (r+dr >= r_count || c+dc >= c_count) continue;
				if (input[r+dr][c+dc] == '@') counter++;
			}

			if (counter < 4) {
				valid_rolls++;
				rolls_to_remove.emplace_back(r,c);
			}
		}
	}

	return valid_rolls;
}


int remove_valid_rolls()
{
	int sum = 0;

	do {
		rolls_to_remove.clear();
		sum += count_valid_rolls();
		for (auto [r,c] : rolls_to_remove) {
			input[r][c] = '.';
		}
	} while (rolls_to_remove.size() > 0);

	return sum;
}


int main()
{
	std::string temp_row;
	while (std::cin >> temp_row) {
		input.push_back(temp_row);
	}

	std::cout << "PART 1: " << count_valid_rolls() << "\n";
	std::cout << "PART 2: " << remove_valid_rolls() << "\n";

	return 0;
}
