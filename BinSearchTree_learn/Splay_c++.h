#ifndef __SPLAY_CPP_H__
#define __SPLAY_CPP_H__
#include "BinSearchTree_c++.h"
namespace shitong
{

    template <typename T>
    class Splay : public BST<T> //伸展树
    {
    protected:
        /* data */
        BinNodePosi(T) splay(BinNodePosi(T) v); //将v移动至_root
    public:
        BinNodePosi(T) & search(T const &e);
        BinNodePosi(T) insert(T const &e);
        bool remove(T const &e);
        template <typename T>
        inline void attachAsLChild(BinNodePosi(T) p, BinNodePosi(T) lc)
        {
            p->lc = lc;
            if (lc)
                lc->parent = p;
        }
        template <typename T>
        inline void attachAsRChild(BinNodePosi(T) p, BinNodePosi(T) rc)
        {
            p->rc = rc;
            if (rc)
                rc->parent = p;
        }
    };
    template <typename T>
    BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
    {
        //从节点v逐层伸展，将v移动至根节点
        if (!v)
            return v;
        BinNodePosi(T) p = nullptr, g = nullptr;
        while ((p = v->parent) && (g = p->parent))
        {
            //zigzig和zagzag压缩高度（双层优于单层所在），zigzag和zagzig与单层效果一样
            BinNodePosi(T) gg = g->parent; //每次伸展结束后v的父亲（原来的爷爷的爹）
            if (IsLchild(*p))
            {
                if (IsLchild(*v)) //zig-zig
                {
                    attachAsLChild(g, p->rc);
                    attachAsRChild(p, g);
                    attachAsLChild(p, v->rc);
                    attachAsRChild(v, p);
                }
                else //zag-zig
                {
                    attachAsRChild(p, v->lc);
                    attachAsLChild(v, p);
                    attachAsLChild(g, v->rc);
                    attachAsRChild(v, g);
                }
            }
            else
            {
                if (IsRchild(*p)) //zag-zag
                {
                    attachAsRChild(g, p->lc);
                    attachAsLChild(p, g);
                    attachAsRChild(p, v->lc);
                    attachAsLChild(v, p);
                }
                else //zig-zag
                {
                    attachAsLChild(p, v->rc);
                    attachAsRChild(v, p);
                    attachAsRChild(g, v->lc);
                    attachAsLChild(v, g);
                }
            }
            if (!gg)
                v->parent = nullptr;
            else
            {
                (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
                updateHeight(g);
                updateHeight(p);
                updateHeight(v);
            }
        }
        if (p = v->parent)
        {
            if (IsLchild(*v))
            {
                attachAsLChild(p, v->rc);
                attachAsRChild(v, p);
            }
            else
            {
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
            }
            updateHeight(p);
            updateHeight(v);
        }
        return v;
    }

    template <typename T>
        BinNodePosi(T) & Splay<T>::search(T const &e)
    {
        BinNodePosi(T) p = searchIn(_root, e, _hot);
        _root = splay(p ? p : _hot);
        return _root;
    }

    template <typename T>
    BinNodePosi(T) Splay<T>::insert(T const &e)
    {
        if (!_root)
        {
            _size++;
            return _root = new BinNode<T>(e);
        }
        if (e == search(e)->data)
            return _root;
        _size++;
        BinNodePosi(T) p = _root;
        if (p->data > e)
        {
            _root = new BinNode<T>(e, nullptr, p->lc, p);
            if (HasLChild(*p))
            {
                p->lc->parent = _root;
                p->lc = nullptr;
            }
        }
        else
        {
            _root = new BinNode<T>(e, nullptr, p, p->rc);
            if (HasRChild(*p))
            {
                p->rc->parent = _root;
                p->rc = nullptr;
            }
        }
        updateHeightAbove(p);
        return _root;
    }
    template <typename T>
    bool Splay<T>::remove(T const &e)
    {
        BinNodePosi(T) p = search(e);
        if (!_root || e != p->data)
            return false;
        BinNodePosi(T) s = _root;
        if (!HasLChild(*_root))
        {
            _root = _root->rc;
            if (_root)
                _root->parent = nullptr;
        }
        else if (!HasRChild(*_root))
        {
            _root = _root->lc;
            if (_root)
                _root->parent = nullptr;
        }
        else
        {
            BinNodePosi(T) lTree = _root->lc;
            lTree->parent = nullptr;
            _root->lc = nullptr;
            _root = _root->rc;
            _root->parent = nullptr;
            search(e);
            _root->lc = lTree;
            lTree->parent = _root;
        }
        _size--;
        release(s->data);
        release(s);
        if (_root)
            updateHeight(_root);
        return true;
    }
} // namespace shitong
#endif