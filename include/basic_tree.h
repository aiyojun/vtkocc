#ifndef VTKOCC_BASIC_TREE_H
#define VTKOCC_BASIC_TREE_H

#include <vector>
#include <string>

template<typename T>
class Node {
public:
    Node(): _uuid(""), _parent(nullptr), _depth(0) {}
    int getDepth() { return _depth; }
    void setDepth(int d) { _depth = d; }
    const T& getData() const { return _data; }
    void setData(T d) { _data = d; }
    void addChild(Node<T> *c);
    bool hasChild() { return !_children.empty(); }
    Node<T> *getChild(int i) { return _children[i]; }
    void removeChildren() { _children.clear(); }
    int childNumber() { return (int) _children.size(); }
    void setParent(Node<T> *p) { _parent = p; }
    Node<T> *getParent() { return _parent; }
protected:
    T _data;
private:
    std::vector<Node<T> *> _children;
    Node<T> *_parent;
    std::string _uuid;
    int _depth;
};

template<typename T>
void Node<T>::addChild(Node<T> *c)  {
    c->setParent(this);
    _children.emplace_back(c);
}

#endif //VTKOCC_BASIC_TREE_H
