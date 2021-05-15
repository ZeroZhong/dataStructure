#if !defined(__QUADLIST_CPP_H__)
#define __QUADLIST_CPP_H__
#include "QuadListNode_c++.h"
namespace shitong
{
    template <typename T>
    class QuadList
    {
    private:
        /* data */
        int _size;
        QListNodePosi(T) header;
        QListNodePosi(T) trailer;

    protected:
        void init();
        void clear();

    public:
        QuadList(/* args */){init()};
        ~QuadList();
        QListNodePosi(T) first() const { return header->succ; }
        QListNodePosi(T) last() const { return trailer->pred; }
        int size() const { return _size; }
        bool empty() const { return _size < 1; }
        bool valid(QListNodePosi(T) p) const {return p && (p != header) && (p != trailer)); }
        QListNodePosi(T) insertAsSuccAbove(T entry, QListNodePosi(T) p, QListNodePosi(T) b)
        {
            QListNodePosi(T) p = new QuadListNode(entry, p, nullptr, nullptr, b);
        }
    };
} // namespace shitong

#endif // __QUADLIST_CPP_H__
