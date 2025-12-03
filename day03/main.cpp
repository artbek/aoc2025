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


std::vector<std::string> banks;


ll solve_for_digits(int total_digits)
{
	std::vector<ll> joltages;

	for (auto bank : banks) {
		int bank_size = bank.size();

		ll joltage = 0;
		int bat_pos = -1;

		for (int digits = total_digits-1 ; digits >= 0; digits--) {
			ll bat_val = 0;
			for (int i = bat_pos + 1; i < bank_size - digits; i++) {
				ll cur_val = (bank[i] - 48);
				if (cur_val > bat_val) {
					bat_val = cur_val;
					bat_pos = i;
				}
			}

			for (int m = 0; m < digits; m++) bat_val *= 10;

			joltage += bat_val;
		}

		joltages.push_back(joltage);
	}

	ll sum = 0;
	for (auto j : joltages) sum += j;

	return sum;
}


int main()
{
	std::string temp_bank;
	while (std::cin >> temp_bank) {
		banks.push_back(temp_bank);
	}

	std::cout << "PART 1: " << solve_for_digits(2) << "\n";
	std::cout << "PART 2: " << solve_for_digits(12) << "\n";

	return 0;
}
