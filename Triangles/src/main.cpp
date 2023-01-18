#include "vector.hpp"
#include "triangle.hpp"
#include "octree.hpp"
#include "intersection.hpp"
#include <istream>
#include <iterator>
#include <utility>

#include <cstdlib>
#include <ctime>
#include <chrono>

int main() {

	size_t N;
	std::cin >> N;

	std::list<geometry::triangle_t> triangle_list;
	for(size_t num = 0; num < N; ++num) {
		geometry::triangle_t triangle;
		std::cin >> triangle;
		triangle.name = num;
		triangle_list.emplace_back(std::move(triangle));
	}
auto begin = std::chrono::high_resolution_clock::now();
	octree::octree_t<geometry::triangle_t> tree (std::move(triangle_list));
	tree.intersector();
auto end = std::chrono::high_resolution_clock::now();
std::cout << std::endl;
std::cout << "------- TIME ---------" << std::endl;
std::cout << std::chrono::duration_cast <std::chrono::milliseconds>(end - begin).count()<< " " << std::endl;
}