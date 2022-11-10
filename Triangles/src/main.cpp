#include "vector.hpp"
#include "triangle.hpp"
#include "octree.hpp"
#include "intersection.hpp"

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

  //std::cout << triangle;
  //---------------------
  /////////////////////////////////////////////////////
  /// ------------ TESTING OCTREE ------------------///
  /////////////////////////////////////////////////////
  std::list<geometry::triangle_t> tr_list{triangl1, triangl2, triangl3};
  //octree::octree_node_t<geometry::triangle_t>* node = new octree::octree_node_t<geometry::triangle_t>(std::move(tr_list), std::move(vec8), std::move(vec7), nullptr);
  octree::octree_t<geometry::triangle_t> vosem_tree (new octree::octree_node_t<geometry::triangle_t>(std::move(tr_list), std::move(vec8), std::move(vec7), nullptr));
  for(auto obj : vosem_tree.root_->objects_)
    std::cout << obj;
  std::cout << "----------\n";
  vosem_tree.root_->sift();
 for(auto obj : vosem_tree.root_->objects_)
    std::cout << obj;
  for(auto obj : vosem_tree.root_->children_[0]->objects_) {
    std::cout << obj;
  }
  for(auto obj : vosem_tree.root_->children_[7]->objects_) {
    std::cout << obj;
  }
  /////////////////////////////////////////////////////
  /// ---------TESTING 3D INTRSECTION---------------///
  /////////////////////////////////////////////////////


  //det calculation

  double det2 = intersection::calc_det(vec4, vec5, vec6);
  double det3 = intersection::calc_det(vec4, vec5, vec6, vec7);
  double det3_1 = intersection::calc_det(vec4, vec5, vec6, vec8);
  std::cout << "det2: " << det2 << ", det3: " << det3 << ", det3_1: " << det3_1 <<  std::endl;

  //intersection

  //1 tr
  struct geometry::vector_t vec12{1.1, 0, 0};
  struct geometry::vector_t vec13{1, 1, 0};
  struct geometry::vector_t vec14{-1, 0, 0};
  //2 tr
  struct geometry::vector_t vec15{1, 0.5, 0};
  struct geometry::vector_t vec16{1, 0.8, 0};
  struct geometry::vector_t vec17{1.52, 0.61, 0};

  geometry::triangle_t triangl_1(vec12, vec13, vec14);
  geometry::triangle_t triangl_2(vec16, vec15, vec17);

  bool res_intersec = intersection::intersection(triangl_1, triangl_2);
  std::cout << std::boolalpha << res_intersec << std::endl;
}