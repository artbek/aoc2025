#include <algorithm>
#include <iostream>
#include <map>
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

struct junction_box {
	int circuit_id;
	int x;
	int y;
	int z;
	bool operator < (const junction_box rhs) const {
        return circuit_id < rhs.circuit_id;
    }
};

using dist = std::pair<ll, std::pair<int, int>>;

std::vector<junction_box> boxes;
std::vector<dist> distances;
int max_connected_pairs = 1000;

void print_boxes()
{
	std::cout << "\n";
	for (auto [c, x,y,z] : boxes) {
		std::cout << "" << c << " (" << x << "," << y << "," << z << ")\n";
	}
}


void calc_distances()
{
	int boxes_count = boxes.size();
	for (int i = 0; i < boxes_count; i++) {
		for (int j = i+1; j < boxes_count; j++) {
			ll dx = boxes[i].x - boxes[j].x;
			ll dy = boxes[i].y - boxes[j].y;
			ll dz = boxes[i].z - boxes[j].z;
			ll d = (dx*dx + dy*dy + dz*dz);
			distances.push_back({d, {i,j}});
		}
	}

	std::sort(distances.begin(), distances.end());
}


ll solve(int part)
{
	ll answer = -1;

	calc_distances();

	int next_circuit_id = 1;
	int connected_pairs = 0;

	for (auto [d,box] : distances) {
		junction_box & b1 = boxes[box.first];
		junction_box & b2 = boxes[box.second];

		if (b1.circuit_id == 0 && b2.circuit_id == 0) { // create new circuit
			b1.circuit_id = next_circuit_id;
			b2.circuit_id = next_circuit_id;
			next_circuit_id++;

		} else if (b1.circuit_id > 0 && b2.circuit_id == 0) {
			b2.circuit_id = b1.circuit_id;

		} else if (b1.circuit_id == 0 && b2.circuit_id > 0) {
			b1.circuit_id = b2.circuit_id;

		} else if (b1.circuit_id != b2.circuit_id) { // connect both circuits
			int new_circuit_id = b1.circuit_id;
			int old_circuit_id = b2.circuit_id;
			for (auto & b : boxes) {
				if (b.circuit_id == old_circuit_id) {
					b.circuit_id = new_circuit_id;
				}
			}
		}

		connected_pairs++;

		std::map<int,int> circuits;
		for (auto b : boxes) circuits[b.circuit_id]++;

		if (part == 1) {
			if (connected_pairs >= max_connected_pairs) break;
		} else {
			if (circuits.size() == 1) {
				answer = ll(b1.x) * ll(b2.x);
				break;
			}
		}
	}

	if (part == 1) {
		std::map<int,int> circuits;
		for (auto b : boxes) circuits[b.circuit_id]++;
		circuits.erase(0);

		std::vector<int> values;
		for (auto [k,v] : circuits) values.push_back(v);
		std::sort(values.rbegin(), values.rend());

		answer = 1;

		int counter = 0;
		for (auto val : values) {
			answer *= val;
			if (++counter >= 3) break;
		}
	}

	return answer;
}


int main(int argc, char** argv)
{
	int x, y, z;
	char comma;

	while (std::cin >> x) {
		std::cin >> comma >> y >> comma >> z;
		boxes.push_back({0, x, y, z});
	}

	if (argc > 1) {
		std::string opt(argv[1]);
		if (opt == "--test-input") max_connected_pairs = 10;
	}

	std::cout << "PART 1: " << solve(1) << "\n";
	std::cout << "PART 2: " << solve(2) << "\n";

	return 0;
}
