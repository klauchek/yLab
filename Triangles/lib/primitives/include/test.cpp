#include "vector.hpp"
#include "triangle.hpp"
#include "../../octree/include/octree.hpp"
#include "../../intersection/include/intersection.hpp"

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

  double det2 = calc_det(vec4, vec5, vec6);
  double det3 = calc_det(vec4, vec5, vec6, vec7);
  double det3_1 = calc_det(vec4, vec5, vec6, vec8);
  std::cout << "det2: " << det2 << ", det3: " << det3 << ", det3_1: " << det3_1 <<  std::endl;

}