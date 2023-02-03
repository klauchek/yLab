#ifndef __OCTREE__H__
#define __OCTREE__H__

#include <array>
#include <stack>
#include <list>
#include <utility>
#include <memory>
#include <algorithm>
#include <unordered_set>

#include "vector.hpp"
#include "intersection.hpp"

namespace octree{

const double min_space = 0.1;

template <typename Obj>
class octree_node_t {

    octree_node_t *parent_{};

    // z y x
    // 0 0 0 - part №0
    // 0 0 1 - part №1
    // 0 1 0 - part №2 etc.
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
    geometry::vector_t left_border_{}, right_border_{};
    std::array<octree_node_t<Obj>*, 8> children_{};
    std::list<Obj> objects_;

    octree_node_t(std::list<Obj> &&objects_list, geometry::vector_t &&left, geometry::vector_t &&right, octree_node_t<Obj> *parent = nullptr) :
                    parent_(parent), left_border_(std::move(left)), right_border_(std::move(right)), objects_(std::move(objects_list)) {}
    
    struct octree_node_deleter{
        void operator()(octree_node_t *root){
            if(root == nullptr)
                return;
            std::stack<octree_node_t *> stack;
            stack.push(root);

            std::stack<octree_node_t *> to_delete;

            while(!stack.empty()) {
                octree_node_t *cur = stack.top();
                stack.pop();

                to_delete.push(cur);
                for(auto child : cur->children_)
                    if(child)
                        stack.push(child);
            }
            while(!to_delete.empty()) {
                octree_node_t *cur = to_delete.top();
                to_delete.pop();
                delete cur;
            }
        }

    };
    octree_node_t *get_parent() const{
        return parent_;
    }

    
    unsigned char where(const Obj &object) const{
        size_t num_vertex = object.get_nvertex();
        unsigned char part[num_vertex]{}; //we can do it because in triangle vertices is an array
        for(size_t i = 0; i < num_vertex; ++i) {
            geometry::vector_t cur_vertex = object[i];
            geometry::vector_t middle_of_diag = (left_border_ + right_border_) / 2.0;
            part[i] = cur_vertex.relative_pos(middle_of_diag);
        }
        auto x = part[0];
        auto y = part[1];
        auto z = part[2];

        if (x == y)
            if (y == z)
                return part[0];
        return UCHAR_MAX;
    }
    void sift() {

        double diag = (left_border_[0] - right_border_[0]) * (left_border_[0] - right_border_[0]) +
                    (left_border_[1] - right_border_[1]) * (left_border_[1] - right_border_[1]) +
                    (left_border_[2] - right_border_[2]) * (left_border_[2] - right_border_[2]);

        if(objects_.size() == 1 || cmp::dbl_cmp(diag, (min_space * min_space)) < 0)
            return;

        std::array<std::list<Obj>, 8> children_objs{};
        for(auto it = objects_.begin(), it_end = objects_.end(); it != it_end;) {

            unsigned char place = where(*it);
            if(place == UCHAR_MAX) {
                ++it;
                continue;
            }
            auto tmp_it = std::next(it); //bc of splice, but maybe it can be better
            children_objs[place].splice(children_objs[place].begin(), objects_, it, std::next(it));
            it = tmp_it;
        }
        for(int i = 0; auto child_list : children_objs) {
            if(child_list.empty()) {
                ++i;
                continue;
            }
            
            std::pair<geometry::vector_t, geometry::vector_t> borders = define_borders(i);
            children_[i] = new octree_node_t(std::move(child_list), std::move(borders.first), std::move(borders.second), this);
            ++i;
        }

        for(auto child : children_){
            if(child) {
                child->sift();

            }
        }
    }

    octree_node_t (const octree_node_t &rhs) = delete;
    octree_node_t (octree_node_t &&rhs) = delete;
    octree_node_t &operator=(octree_node_t &&rhs) = delete;
    octree_node_t &operator=(const octree_node_t &rhs) = delete;
    virtual ~octree_node_t() = default;
};

template <typename Obj>
class octree_t final{
    std::unique_ptr<octree_node_t<Obj>, typename octree_node_t<Obj>::octree_node_deleter> root_;
    geometry::vector_t define_right(std::list<Obj>& objs){
        double max = 0.0;
        for(auto obj : objs) {
            for(auto vert : obj.vertices_) {
                double new_max = std::abs(*std::max_element(vert.coords_.begin(), vert.coords_.end(), [](geometry::point_t a, geometry::point_t b){return std::abs(a) < std::abs(b);}));
                max = new_max > max ? new_max : max;
            }
        }
        max += 0.5;
        return geometry::vector_t{max, max, max};
    }

public:
    octree_t(std::list<Obj>&& objs_list){
        geometry::vector_t right = define_right(objs_list);
        geometry::vector_t left = -right;
        root_ = std::unique_ptr<octree_node_t<Obj>, typename octree_node_t<Obj>::octree_node_deleter>(new octree_node_t<Obj>(std::move(objs_list), std::move(left), std::move(right)));
        root_->sift();
    }

    void insert_intersected(const Obj &obj_1, const Obj &obj_2, std::unordered_set<int> &intersected) {
        bool res_intersec = intersection::intersection(obj_1, obj_2);
        if(res_intersec) {
            intersected.insert(obj_1.name);
            intersected.insert(obj_2.name);
        }
    }

    void intersector(){
        std::stack<octree_node_t<Obj> *> stack;

        auto *root = root_.get();
        stack.push(root);
        
        std::unordered_set<int> intersected;
        std::stack<octree_node_t<Obj> *> to_intersect;

        while(!stack.empty()) {
            auto* cur = stack.top();
            stack.pop();

            to_intersect.push(cur);

            for(auto child : cur->children_)
                if(child)
                    stack.push(child);
        }
        while(!to_intersect.empty()) {
            auto* cur = to_intersect.top();
            to_intersect.pop();

            //intersection between objs in one node
            for (auto obj_it_1 = cur->objects_.begin(); obj_it_1 != std::prev(cur->objects_.end()); obj_it_1 = std::next(obj_it_1)) {
                for (auto obj_it_2 = std::next(obj_it_1); obj_it_2 != cur->objects_.end(); obj_it_2 = std::next(obj_it_2))
                    insert_intersected(*obj_it_1, *obj_it_2, intersected);
            }
            //intersection between objs from one node with objs from parents
            auto* parent = cur->get_parent();
            while(parent) {
                for(auto obj : cur->objects_) {
                    for(auto parent_obj : parent->objects_)
                        insert_intersected(obj, parent_obj, intersected);
                }
                parent = parent->get_parent();
            }
        }
        std::cout << "Intersected triangles: " << intersected.size() << std::endl;
        std::vector<int> v_intersected(intersected.begin(), intersected.end());
        std::sort(v_intersected.begin(), v_intersected.end());
        for(auto v : v_intersected)
           std::cout << v << " ";
    }

};


}

#endif //__OCTREE__H__