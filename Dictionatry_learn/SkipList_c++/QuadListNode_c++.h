#if !defined(__QUADLISTNODE_CPP_H__)
#define __QUADLISTNODE_CPP_H__
#include "../../BinSearchTree_learn/Entry_c++.h"
namespace shitong
{
#define QListNodePosi(T) QuadListNode<T> *
    template <typename T>
    struct QuadListNode
    {
        /* data */
        T entry;
        QListNodePosi(T) pred, succ;
        QListNodePosi(T) above, below;
        QuadListNode(T e = T(), QListNodePosi(T) p = nullptr, QListNodePosi(T) s = nullptr,
                     QListNodePosi(T) a = nullptr, QListNodePosi(T) b = nullptr)
            : entry(e), pred(p), succ(s), above(a), below(b);
        ~QuadListNode();
        QListNodePosi(T) insertAsSuccAbove(T entry, QListNodePosi(T) b = nullptr)
        {
            //以当前节点为前驱，以b为下邻
            QListNodePosi(T) r = new QuadListNode(entry, this, nullptr, nullptr, b);
            return r;
        }
    };

} // namespace shitong

#endif // __QUADLISTNODE_CPP_H__
