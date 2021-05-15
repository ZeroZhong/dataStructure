#ifndef __BINSEARCHTREE_CPP_H__
#define __BINSEARCHTREE_CPP_H__

#include "../bintree_learn/BinTree_c++.h"

namespace shitong
{
    template <typename T>
    class BST : public BinTree<T>
    {
    protected:
        /* data */
        //记录父亲节点
        BinNodePosi(T) _hot;
        //3节点，4子树，统一重平衡算法
        BinNodePosi(T) connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3, BinNodePosi(T) T4);
        //对x及其父亲，祖父做统一旋转调整
        BinNodePosi(T) rotateAt(BinNodePosi(T) x);

    public:
        BST(/* args */);
        ~BST();
        virtual BinNodePosi(T) & search(T const &e);
        virtual BinNodePosi(T) insert(T const &e);
        virtual bool remove(T const &e);
    };

    template <typename T>
        static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, T const &e, BinNodePosi(T) & hot)
    {
        //二叉树二分查找，节点v开始查找元素e，记录查找结果父亲hot
        if (!v || v->data == e)
            return v;
        hot = v;
        return (searchIn((v->data > e) ? v->lc : v->rc), e, hot);
    }
    template <typename T>
        BinNodePosi(T) & BST<T>::search(T const &e)
    {
        return searchIn(_root, e, _hot = nullptr);
    }
    template <typename T>
    BinNodePosi(T) BST<T>::insert(T const &e)
    {
        BinNodePosi(T) &p = search(e);
        if (p)
            return p;
        p = new BinNode<T>(e, _hot);
        size++;
        updateHeightAbove(p);
        return p;
    }
    template <typename T>
    static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
    {
        BinNodePosi(T) p = x;
        BinNodePosi(T) succ = nullptr;
        if (!HasLChild(*p))
            x = succ = p->rc;
        else if (!HasRChild(*p))
            x = succ = p->lc;
        else
        {
            p = p->succ();
            std::swap(p->data, x->data);
            BinNodePosi(T) u = p->parent;            //回溯p父亲
            (x == u) ? u->rc : u->lc = succ = p->rc; //若p父亲为x则左连接否则右连接
        }
        hot = p->parent;
        if (succ)
            succ->parent = hot;
        //release(p->data);
        //release(p);
        return succ;
    }
    template <typename T>
    bool BST<T>::remove(T const &e)
    {
        BinNodePosi(T) &p = search(e);
        if (!p)
            return false;
        removeAt(p, _hot);
        size--;
        updateHeightAbove(_hot);
        return true;
    }
    template <typename T>
    BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3, BinNodePosi(T) T4)
    {
        //完成子树内部的连接
        a->lc = T1;
        if (T1)
            T1->parent = a;
        a->rc = T2;
        if (T2)
            T2->parent = a;
        updateHeight(a);
        c->lc = T3;
        if (T3)
            T3->parent = c;
        c->rc = T4;
        if (T4)
            T4->parent = c;
        updateHeight(c);
        b->lc = a;
        a->parent = b;
        b->rc = c;
        c->parent = b;
        updateHeight(b);
        return b;
    }
    template <typename T>
    BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
    {
        //选择子树旋转方式，完成子树根节点向上连接
        BinNodePosi(T) p = v->parent;
        BinNodePosi(T) g = p->parent;
        if (IsLchild(*p)) //zig(g)
        {

            if (IsLchild(*v)) //zig-zig
            {
                p->parent = g->parent;
                return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
            }
            else //zag(p)-zig(g)
            {
                v->parent = g->parent;
                return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
            }
        }
        else //zag(g)
        {
            if (IsRchild(*v)) //zag-zag
            {
                p->parent = g->parent;
                return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
            }
            else //zig(p)-zag(g)
            {
                v->parent = g->parent;
                return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
            }
        }
    }

} // namespace shitong

#endif