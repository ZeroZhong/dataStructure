#if !defined(__SKIPLIST__CPP_H__)
#define __SKIPLIST__CPP_H__

#include "../Dictionary_c++.h"
#include "QuadList_c++.h"
#include "../../BinSearchTree_learn/Entry_c++.h"
#include "../../List_learn/listNode/list_c++.h"
#include <ctime>
#include <iostream>
namespace shitong
{
#define Qlist ListNode<QuadList<Entry<K, V>> *> *
#define QlistNode QuadListNode<Entry<K, V>> *
    template <typename K, typename V>
    class SkipList : public Dictionary<K, V>, public List<QuadList<Entry<K, V>> *>
    {
    protected:
        /* data */
        bool skipSearch(Qlist &qlist, QlistNode &p, K &k);

    public:
        int size() const { return last()->data->size(); }
        int level() const { return List::size(); }
        bool put(K, V);
        V *get(K);
        bool remove(K) :
    };
    template <typename K, typename V>
    bool SkipList<K, V>::skipSearch(Qlist &qlist, QlistNode &p, K &k)
    {
        while (true)
        {
            /* code */
            while (p->succ && (p->entry.key <= k))
                p = p->succ;
            p = p->pred;
            if (p->pred && (p->entry.key == k))
                return true;
            qlist = qlist->succ;
            if (!qlist->succ)
                return false;
            p = (p->pred) ? p->below : qlist->data->first();
        }
    }

    template <typename K, typename V>
    bool SkipList<K, V>::put(K k, V v)
    {
        srand(time(NULL));
        Entry<K, V> e = Entry<K, V>(k, v); //建立副本
        if (empty())                       //空则插入一行
            insertAsFirst(new QuadList<Entry<K, V>>);
        Qlist qlist = first(); //找到首节点
        QlistNode p = qlist->data->first();
        if (skipSearch(qlist, p, k)) //查找定位
            while (p->below)         //找到则深入底层
                p = p->below;
        qlist = last();                                    //qlist深入底层
        QlistNode b = qlist->data->insertAfterAbove(e, p); //插入为p后继，底层
        while (rand() & 1)
        {
            while (qlist->data->valid(p) & !p->above) //向前找到有上节点的节点
                p = p->pred;
            if (!qlist->data->valid(p)) //如果是header
            {
                if (qlist == first())
                    insertAsFirst(new QuadList<Entry<K, V>>);
                p = qlist->pred->data->first()->pred; //回到上一header
            }
            else
                p = p->above; //否则p直接上升到above
            qlist = qlist->pred;
            qlist->data->insertAfterAbove(e, p, b);
        }
        return true;
    }
    template <typename K, typename V>
    V *SkipList<K, V>::get(K k)
    {
        if (empty())
            return nullptr;
        Qlist qlist = first();
        p = qlist->data->first();
        return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;
    }
    template <typename K, typename V>
    bool SkipList<K, V>::remove(K k)
    {
        Qlist qlist = first();
        QlistNode p = qlist->data->first();
        if (!skipSearch(qlist, p, k))
            return false;
        do
        {
            QlistNode lower = p->below;
            qlist->data->remove(p);
            p = lower;
            qlist = qlist->succ;
        } while (qlist->succ);
        while (!empty && first()->data->empty())
        {
            List::remove(first());
            return true;
        }
    }

} // namespace shitong

#endif // __SKIPLIST__CPP_H__
