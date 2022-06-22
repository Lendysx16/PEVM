#pragma once

#include "avl_tree.h"
#include "iostream"
class VariableValue {
private:
    bool value_ = false;
    unsigned char name_ = 0;
public:
    VariableValue(unsigned char name = 0, bool value = false) : name_(name), value_(value) {}

    void setvalue(bool value) { value_ = value; }

    unsigned char name() const {
        return name_;
    }

    bool value() const {
        return value_;
    }

    std::string str() const {
        return std::string("x") + (char)name_;
    }

    friend bool operator>(const VariableValue &lhs, const VariableValue &rhs) {
        return lhs.name_ > rhs.name_;
    }

    friend bool operator<(const VariableValue &lhs, const VariableValue &rhs) {
        return lhs.name_ < rhs.name_;
    }

    friend bool operator==(const VariableValue &lhs, const VariableValue &rhs) {
        return lhs.name_ == rhs.name_;
    }
};

namespace global {
    extern avltree<VariableValue> Workspace;
}


class AbstractNode {
public:
    virtual bool calc() const = 0;
    virtual std::string str() const = 0;

    virtual ~AbstractNode(){};

    virtual AbstractNode *make_node() const = 0;
};

class VariableNode : public AbstractNode {
private:
    unsigned char name_ = 0;
public:
    VariableNode(unsigned char name) : name_(name){};

    bool calc() const {
        auto it = global::Workspace.find(VariableValue(name_, false));
        if (it == nullptr)
            throw std::invalid_argument("Tree does not contain neccesary value");
        return (*it).value();
    }


    std::string str() const {
        return std::string("x") +  (char)name_;
    }

    AbstractNode *make_node() const {
        return new VariableNode(name_);
    }

};

class ConstNode : public AbstractNode {
private:
    const bool value_ = false;
public:
    ConstNode(bool value) : value_(value) {};

    bool calc() const { return value_; }

    std::string str() const {
        return {value_ ? "1" : "0"};
    }

    AbstractNode *make_node() const {
        return new ConstNode(value_);
    }
};


class BinNode : public AbstractNode {
protected:
    AbstractNode *left_ = nullptr, *right_ = nullptr;
public:
    BinNode(AbstractNode *left, AbstractNode *right) : left_(left), right_(right) {}

    ~BinNode() {
        delete left_;
        delete right_;
        left_ = right_ = nullptr;
    }

};

class UnarNode : public AbstractNode {
protected:
    AbstractNode *child_ = nullptr;
public:
    UnarNode(AbstractNode *child) : child_(child) {}

    bool calc() const {
        return child_->calc();
    }

    ~UnarNode() {
        delete child_;
        child_ = nullptr;
    }
};

class AndNode : public BinNode {
public:
    AndNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() & right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return left_->str() + std::string(" & ") + right_->str();
        else
            return {""};
    }

    AbstractNode *make_node() const {
        return new AndNode(left_->make_node(), right_->make_node());
    }
};

class OrNode : public BinNode {
public:
    OrNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() | right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" v ") + right_->str() + std::string(")");
        else
            return {""};
    }

    AbstractNode *make_node() const {
        return new OrNode(left_->make_node(), right_->make_node());
    }
};

class XorNode : public BinNode {
public:
    XorNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() ^ right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" + ") + right_->str() + std::string(")");
        else
            return {""};
    }

    AbstractNode *make_node() const {
        if(left_ and right_)
        return new XorNode(left_->make_node(), right_->make_node());
    }
};

class ImplicationNode : public BinNode {
public:
    ImplicationNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() <= right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") +  left_->str() + std::string(" > ") + right_->str() + std::string(")");
    }

    AbstractNode *make_node() const {
        return new ImplicationNode(left_->make_node(), right_->make_node());
    }
};

class rImplicationNode : public BinNode {
public:
    rImplicationNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() >= right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" < ") + right_->str() + std::string(")");
    }

    AbstractNode *make_node() const {
        return new rImplicationNode(left_->make_node(), right_->make_node());
    }
};

class EqNode : public BinNode {
public:
    EqNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return left_->calc() == right_->calc();
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" = ") + right_->str() + std::string(")") ;
    }

    AbstractNode *make_node() const {
        return new EqNode(left_->make_node(), right_->make_node());
    }
};

class StrokeNode : public BinNode {
public:
    StrokeNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return !(left_->calc() | right_->calc());
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" ^ ") + right_->str()+  std::string(")") ;
    }

    AbstractNode *make_node() const {
        return new StrokeNode(left_->make_node(), right_->make_node());
    }
};

class NorNode : public BinNode {
public:
    NorNode(AbstractNode *left, AbstractNode *right) : BinNode(left, right) {};

    bool calc() const {
        return !(left_->calc() & right_->calc());
    };

    std::string str() const {
        if(left_ and right_)
        return std::string("(") + left_->str() + std::string(" | ") + right_->str() + std::string(")");
    }

    AbstractNode *make_node() const {
        return new NorNode(left_->make_node(), right_->make_node());
    }
};


class NegationNode : public UnarNode {
public:
    NegationNode(AbstractNode *child) : UnarNode(child) {};

    bool calc() const {
        return !child_->calc();
    };

    std::string str() const {
        if(child_)
        return  std::string("~") + child_->str();
    }

    AbstractNode *make_node() const {
        return new NegationNode(child_->make_node());
    }
};


