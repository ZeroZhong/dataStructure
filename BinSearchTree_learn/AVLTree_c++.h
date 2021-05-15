#ifndef __AVL_CPP_H__
#define __AVL_CPP_H__
#include "BinSearchTree_c++.h"
namespace shitong
{
    template <typename T>
    class AVL : public BST<T>
    {
        //通过设定适度平衡标准并借助zig，zag等等价变换，实现相对理想平衡。
        //在渐近意义下，控制AVL树的高度在O（logn）内
    public:
        AVL(/* args */);
        ~AVL();
        //重载查找和移除
        BinNodePosi(T) insert(T const &e);
        bool remove(T const &e);
        inline bool Balanced(BinNodePosi(T) p) { return stature(p->lc) == stature(p->rc); }
        inline int BalFac(BinNodePosi(T) p) { return stature(p->lc) - stature(p->rc); }
        inline bool AvlBalanced(BinNodePosi(T) p) { return (BalFac(p)) < 2 && (BalFac > -2); }
        inline BinNodePosi(T) tallerChild(BinNodePosi(T) p) { return stature(p->lc) > stature(p->rc) ? p->lc : (stature(p->lc) < stature(p->rc) ? p->rc : (IsLchild(*p) ? p->lc : p->rc)); }
    };

    template <typename T>
    BinNodePosi(T) AVL<T>::insert(T const &e)
    {
        BinNodePosi(T) p = search(e);
        if (p)
            return p;
        BinNodePosi(T) x = p = new BinNode<T>(e, _hot);
        size++;
        for (BinNodePosi(T) g = _hot; g; g = g->parent)
        {
            if (!AvlBalanced(g))
            {
                FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
                break;
            }
            else
                updateHeight(g);
        }
        return x;
    }
    template <typename T>
    bool AVL<T>::remove(T const &e)
    {
        BinNodePosi(T) &p = search(e);
        if (!x)
            return false;
        removeAt(x, _hot);
        size--;
        for (BinNodePosi(T) g = _hot; g; g = g->parent)
        {
            if (!AvlBalanced(g))
                g = FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
            updateHeight(g);
        }
        return true;
    }

} // namespace shitong

#endif