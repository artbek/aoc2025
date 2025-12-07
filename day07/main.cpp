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


using ll = long long;

std::vector<std::string> lines;


std::pair<ll,ll> solve()
{
	int lines_count = lines.size();
	int line_length = lines[0].size();

	ll splits_total = 0;
	ll paths_total = 0;
	std::vector<ll> dp(line_length);

	for (int i = 1; i < lines_count; i++) {
		std::vector<ll> prev_dp = dp;
		for (auto & el : dp) el = 0;

		for (int c = 0; c < line_length; c++) {
			char cur_c = lines[i][c];
			char prev_c = lines[i-1][c];

			if (cur_c == '.') {
				if (prev_c == 'S') {
					dp[c] = 1; break;
				} else if (prev_dp[c] > 0) {
					dp[c] += prev_dp[c];
				}
			} else if (cur_c == '^') {
				if (prev_dp[c] > 0) {
					dp[c-1] += prev_dp[c];
					dp[c+1] += prev_dp[c];
					splits_total++;
				}
			}
		}
	}

	for (auto el : dp) paths_total += el;

	return {splits_total, paths_total};
}


int main()
{
	std::string ln;
	while (std::cin >> ln) {
		lines.push_back(ln);
	}

	std::cout << "PART 1: " << solve().first << "\n";
	std::cout << "PART 2: " << solve().second << "\n";

	return 0;
}
