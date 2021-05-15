#ifndef __LISTNODE_CPP_H__
#define __LISTNODE_CPP_H__
namespace shitong
{
    typedef int Rank;
#define ListNodePosi(T) ListNode<T> *

    template <typename T>
    class ListNode
    {
    public:
        /* data */
        T data;
        ListNodePosi(T) pred;
        ListNodePosi(T) succ;

    public:
        ListNode(/* args */){};
        ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s){};
        ~ListNode(){};

        ListNodePosi(T) operator=(ListNodePosi(T) p)
        {
            this = p;
            return this;
        }
        ListNodePosi(T) insertAsPred(T const &e);
        ListNodePosi(T) insertAsSucc(T const &e);
    };

    template <typename T>
    ListNodePosi(T) ListNode<T>::insertAsPred(T const &e)
    {
        ListNodePosi(T) insert = new ListNode(e, pred, this);
        this->pred->succ = insert;
        this->pred = insert;
        return insert;
    }
    template <typename T>
    ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e)
    {
        ListNodePosi(T) insert = new ListNode(e, this, succ);
        this->succ->pred = insert;
        this->succ = insert;
        return insert;
    }
} // namespace shitong

#endif //__LISTNODE_CPP_H__