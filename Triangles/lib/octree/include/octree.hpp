#ifndef __OCTREE__H__
#define __OCTREE__H__

#include <array>
#include <vector>
#include <list>
#include <utility>

namespace octree{

const double min_space = 0.1;

template <typename Obj>
class octree_node_t {

    geometry::vector_t right_border_{}, left_border_{};
    octree_node_t *parent_{};

    std::pair<geometry::vector_t, geometry::vector_t> define_borders(int part) {

        geometry::vector_t mid = (left_border_ + right_border_) / 2.0;
        geometry::vector_t new_left = left_border_;
        geometry::vector_t new_right = right_border_;
        for(int cur_coord = 0; cur_coord < 3; ++cur_coord){
            int res = part & (1 << cur_coord);
            if(res)
                new_left[cur_coord] = mid[cur_coord];
            else
                new_right[cur_coord] = mid[cur_coord];
        }
        return std::make_pair(new_left, new_right);
    }
    
public:
    std::array<octree_node_t<Obj>*, 8> children_{};
    std::list<Obj> objects_;

    octree_node_t(std::list<Obj> &&objects_list, geometry::vector_t &&right, geometry::vector_t &&left, octree_node_t<Obj> *parent) :
                    parent_(parent), right_border_(std::move(right)), left_border_(std::move(left)), objects_(std::move(objects_list)) {}

    unsigned char where(const Obj &object) const{
        size_t num_vertex = object.get_nvertex(); //TODO: define for each object class
        unsigned char part[num_vertex]{};
        for(size_t i = 0; i < num_vertex; ++i) {
            geometry::vector_t cur_vertex = object.get_vertex(i); //TODO: define for each object class
            geometry::vector_t middle_of_diag = (left_border_ + right_border_) / 2.0;
            part[i] = cur_vertex.relative_pos(middle_of_diag);
            
            if(!std::equal(part, part + num_vertex, part))
                return UCHAR_MAX;
        }
        return part[0];
    }
    void sift() {
        if(objects_.size() == 1) //+ diag < min_space //TODO
            return;
        std::array<std::list<Obj>, 8> children_objs{};
        for(auto it = objects_.begin(), it_end = objects_.end(); it != it_end;) {
            unsigned char place = where(*it);
            if(place == UCHAR_MAX) {
                ++it;
                continue;
            }
            auto tmp_it = std::next(it);
            children_objs[place].splice(children_objs[place].begin(), objects_, it, std::next(it));
            it = tmp_it;
            std::cout << "im here" <<std::endl;
        }
        for(int i = 0; auto child_list : children_objs){
            if(child_list.empty()) {
                ++i;
                continue;
            }
            std::pair<geometry::vector_t, geometry::vector_t> borders = define_borders(i); //TODO
            children_[i] = new octree_node_t(std::move(child_list), std::move(borders.first), std::move(borders.second), this);
            ++i;
        }
        for(auto child : children_){
            if(child)
                child->sift();
        }
    }
};

// class octree_t {

//     octree_node_t *root_;

// public:

//     octree_t() : root_(new octree_node_t) {};

// };


}




#endif //__OCTREE__H__