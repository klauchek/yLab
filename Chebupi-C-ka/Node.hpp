#ifndef __NODE__HPP__
#define __NODE__HPP__

#include <string>
#include <iostream>
#include <vector>

namespace ast {
struct INode {

    // virtual INode* clone() = 0; //????
    virtual void dump() const = 0;
    virtual ~INode();
};

template <typename T>
struct VarNode : public INode final {

    std::string name_;
    T value_;

    VarNode(const std::string name) : name_(name) {}
    void setVal(const T value) {  //& ? 
        value_ = value;
    }

    T getVal() const {
        return value_;
    }

    void dump() const override {
        std::cout << "name_: " << name_ << std::endl;
        std::cout << "value_: " << value_ << std::endl;
    }
};

//requires for T to be trivially copyable?
template <typename T>
struct NumNode : public INode final {
    T value_;

    NumNode(const T value) : value_(value) {}

    T getVal() const {
        return value_;
    }

    void dump() const override {
        std::cout << "value_: " << value_ << std::endl;
    }
};

struct BinOpNode : public INode {
    INode* left_;
    INode* right_;

    BinOpNode(INode* left, INode* right) : left_(left), right_(right) {}
    void dump() const override final {
        std::cout << "BinOpNode: " << std::endl; 
        left_->dump();
        right_->dump();
    }
};

struct UnOpNode : public INode {
    INode* child_;

    UnOpNode(INode* child) : child_(child) {}
    void dump() const override {
        std::cout << "UnOpNode: " << std::endl;
        child_->dump();
    }

};

struct ScopeNode : public INode {

    std::vector<INode*> statements_;

    ScopeNode(std::vector<INode*> statements) : statements_(statements) {}
    void dump() const override {
        std::cout << "ScopeNode: " << std::endl;
        for(const auto* node : statements_) {
            node->dump();
        }
    }
};

struct ConditionNode : public BinOpNode {};

// If?
// While?

}

#endif //__NODE__HPP__