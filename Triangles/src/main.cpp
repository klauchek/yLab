#include "vector.hpp"
#include "triangle.hpp"
#include "octree.hpp"
#include "intersection.hpp"
#include <istream>
#include <iterator>
#include <utility>

// void find_intersected(std::list<geometry::triangle_t> &triangle_list) {
// 	octree::octree_t<geometry::triangle_t> tree (std::move(triangle_list));
	
// }



int main() {
	/////////////////////////////////////////////////////
	/// -------- TESTING PRIMITIVES ------------------///
	/////////////////////////////////////////////////////
	struct geometry::vector_t vec1{};
	std::cout << vec1.coords_[1] << std::endl;

	struct geometry::vector_t vec2{0, 1, 0};
	struct geometry::vector_t vec3{0, 0, 1};


	struct geometry::vector_t vec4{-5, -3, -3};
	struct geometry::vector_t vec5{-4, -1, -7};
	struct geometry::vector_t vec6{-6, -9, -10};

	struct geometry::vector_t vec7{10, 10, 10};
	struct geometry::vector_t vec8{-10, -10, -10};

	struct geometry::vector_t vec9{5, 3, 3};
	struct geometry::vector_t vec10{4, 1, 7};
	struct geometry::vector_t vec11{6, 9, 10};

	std::cout << vec2 << std::endl;

	std::cout << (unsigned)vec3.relative_pos(vec2) << std::endl;

	geometry::triangle_t triangl1(vec1, vec2, vec3);
	geometry::triangle_t triangl2(vec4, vec5, vec6);

	geometry::triangle_t triangl3(vec9, vec10, vec11);
	//geometry::triangle_t triangl2(vec4, vec5, vec6);

	/////////////////////////////////////////////////////
	/// ---------TESTING 3D INTRSECTION---------------///
	/////////////////////////////////////////////////////


	//intersection

	//1 tr
	struct geometry::vector_t vec12{3, 3, 3};
	struct geometry::vector_t vec13{1, 1, 1};
	struct geometry::vector_t vec14{0, 0, 0};
	//2 tr
	struct geometry::vector_t vec15{2, 2, 4.1};
	struct geometry::vector_t vec16{5, 5, 4};
	struct geometry::vector_t vec17{4, 4, 1.5};

	geometry::triangle_t triangl_1(vec12, vec13, vec14);
	geometry::triangle_t triangl_2(vec15, vec16, vec17);

	// bool res_intersec = intersection::intersection(triangl_1, triangl_2);
	// std::cout << std::boolalpha << res_intersec << std::endl;


	size_t N;
	std::cin >> N;

	std::list<geometry::triangle_t> triangle_list;
	for(size_t num = 0; num < N; ++num) {
		geometry::triangle_t triangle;
		std::cin >> triangle;
		triangle.name = num;
		triangle_list.emplace_back(std::move(triangle));
	}

	octree::octree_t<geometry::triangle_t> tree (std::move(triangle_list));
	tree.intersector();
}