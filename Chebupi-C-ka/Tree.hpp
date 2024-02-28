#ifndef __TREE__HPP__
#define __TREE__HPP__

#include "Node.hpp"

#include <<memory>

namespace ast {

    // struct octree_node_deleter{
    //     void operator()(octree_node_t *root){
    //         if(root == nullptr)
    //             return;
    //         std::stack<octree_node_t *> stack;
    //         stack.push(root);

    //         std::stack<octree_node_t *> to_delete;

    //         while(!stack.empty()) {
    //             octree_node_t *cur = stack.top();
    //             stack.pop();

    //             to_delete.push(cur);
    //             for(auto child : cur->children_)
    //                 if(child)
    //                     stack.push(child);
    //         }
    //         while(!to_delete.empty()) {
    //             octree_node_t *cur = to_delete.top();
    //             to_delete.pop();
    //             delete cur;
    //         }
    //     }


class Tree final {
    
    std::unique_ptr<ScopeNode> root_;
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
        std::vector<int> v_intersected(intersected.begin(), intersected.end());
        std::sort(v_intersected.begin(), v_intersected.end());
        for(auto v : v_intersected)
           std::cout << v << std::endl;
    }

};


}


#endif //__TREE__HPP__