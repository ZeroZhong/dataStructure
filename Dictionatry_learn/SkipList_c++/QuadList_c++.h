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
        QListNodePosi(T) insertAfterAbove(T entry, QListNodePosi(T) p, QListNodePosi(T) b)
        {
            _size++;
            return p->insertAsSuccAbove(entry, b);
        }
        T remove(QListNodePosi(T) p)
        {
            if (!p)
                return NULL;
            _size--;
            p->pred->succ = p->succ;
            p->succ->pred = p->pred;
            T e = p->entry;
            delete p;
            return e;
        }
        void clear()
        {
            int oldsize = _size;
            while (_size)
                remove(header->succ);
            return oldsize;
        }
    };
    template <typename T>
    void QuadList<T>::init()
    {
        header = new QuadListNode<T>;
        trailer = new QuadListNode<T>;
        header->succ = trailer;
        trailer->pred = header;
        _size = 0;
    }
} // namespace shitong

#endif // __QUADLIST_CPP_H__
