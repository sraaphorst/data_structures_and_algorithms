/**
 * merging_tables.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * This is supposed to be a simulation of merging database tables.
 * I found the instructions very unclear, but as it simply entailed a basic implementation of disjoint sets,
 * it appears that I am solving the problem that I don't quite understand.
 */

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>


struct DisjointSetsElement {
	size_t size, rank;
	size_t parent;
	
	explicit DisjointSetsElement(size_t size = 0, size_t parent = 0, size_t rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	size_t size;
	size_t max_table_size;
	std::vector <DisjointSetsElement> sets;

	explicit DisjointSets(size_t size): size(size), max_table_size(0), sets(size) {
		for (size_t i = 0; i < size; i++)
			sets[i].parent = i;
	}

	size_t getParent(size_t table) {
		if (sets[table].parent != table)
			sets[table].parent = getParent(sets[table].parent);
		return sets[table].parent;
	}

	void merge(size_t destination, size_t source) {
		size_t realDestination = getParent(destination);
		size_t realSource = getParent(source);
		if (realDestination != realSource) {
			if (sets[realDestination].rank > sets[realSource].rank) {
                sets[realSource].parent = realDestination;
                sets[realDestination].size += sets[realSource].size;
            } else {
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
				if (sets[realDestination].rank == sets[realSource].rank)
					++sets[realSource].rank;
			}
		}
        max_table_size = std::max(max_table_size, std::max(sets[realDestination].size, sets[realSource].size));
	}
};

int main() {
	size_t n, m;
	std::cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		std::cin >> table.size;
		tables.max_table_size = std::max(tables.max_table_size, table.size);
	}

	for (size_t i = 0; i < m; i++) {
		size_t destination, source;
		std::cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        std::cout << tables.max_table_size << std::endl;
	}

	return 0;
}
