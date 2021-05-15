#ifndef __BIN_NODE_CPP_H
#define __BIN_NODE_CPP_H

#include "../stack_learn/stack/stack_c++.h"
#include "../Quene_learn/Quene_c++.h"

#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;
namespace shitong
{
#define BinNodePosi(T) BinNode<T> *
    typedef enum
    {
        RB_RED,
        RB_BLACK
    } RBColor;

    template <typename T>
    class BinNode
    {
    public:
        T data;
        BinNodePosi(T) parent;
        BinNodePosi(T) lc;
        BinNodePosi(T) rc;
        int height;
        int npl; //null path length
        RBColor color;
        BinNode() : data(0), parent(nullptr), lc(nullptr), rc(nullptr), height(1), npl(1), color(RB_RED){};
        BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 1, int l = 1, RBColor c = RB_RED)
            : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){};

        int size();
        BinNodePosi(T) insertAsLC(T const &e) { return lc = new BinNode(e, this); }
        BinNodePosi(T) insertAsRC(T const &e) { return rc = new BinNode(e, this); }
        BinNodePosi(T) succ(BinNodePosi(T) p);

        template <typename VST>
        void travPre_R(BinNodePosi(T) p, VST &); //recursive
        template <typename VST>
        static void visitAlongLeftBranch(BinNodePosi(T) p, VST &visit, Stack<BinNodePosi(T)> &S);
        template <typename VST>
        void travPre_I1(BinNodePosi(T) p, VST &visit);
        template <typename VST>
        void travPre(VST &);

        template <typename VST>
        void travIn_R(BinNodePosi(T) p, VST &); //recursive
        template <typename VST>
        void goAlongLeftBranch(BinNodePosi(T) p, Stack<BinNodePosi(T)> &S);
        template <typename VST>
        void travIn_I1(BinNodePosi(T) p, VST visit);
        template <typename VST>
        void travIn_I2(BinNodePosi(T) p, VST visit);
        template <typename VST>
        void travIn_I3(BinNodePosi(T) p, VST visit);
        template <typename VST>
        void travIn(VST &);

        template <typename VST>
        void travPost_R(BinNodePosi(T) p, VST &); //recursive
        static void gotoHLVFL(Stack<BinNodePosi(T)> &S);
        template <typename VST>
        void travPost_I(BinNodePosi(T) p, VST &visit);
        template <typename VST>
        void travPost(VST &);

        template <typename VST>
        void travLevel(VST &);

        bool operator<(BinNode const &bn) { return data < bn.data; }
        bool operator==(BinNode const &bn) { return data == bn.data; }

        void print(T &data) { cout << data << endl; }
    };

    //BinNode
    template <typename T>
    inline bool IsRoot(BinNode<T> const &bn) { return !bn.parent; }
    template <typename T>
    inline bool IsLchild(BinNode<T> const &bn) { return !IsRoot(bn) && (&bn != bn.parent->lc); }
    template <typename T>
    inline bool IsRchild(BinNode<T> const &bn) { return !IsRoot(bn) && (&bn != bn.parent->rc); }
    template <typename T>
    inline bool HasParent(BinNode<T> const &bn) { return !IsRoot(bn); }
    template <typename T>
    inline bool HasLChild(BinNode<T> const &bn) { return bn.lc; }
    template <typename T>
    inline bool HasRChild(BinNode<T> const &bn) { return bn.rc; }
    template <typename T>
    inline bool HasChild(BinNode<T> const &bn) { return HasLChild(bn) && HasRChild(bn); }
    template <typename T>
    inline bool HasBothChild(BinNode<T> const &bn) { return HasLChild(bn) && HasRChild(bn); }
    template <typename T>
    inline bool IsLeaf(BinNode<T> const &bn) { return !HasChild(bn); }
    //BinNode pointer
    template <typename T>
    inline int stature(BinNodePosi(T) p)
    {
        return (p) ? (p)->height : -1;
    }
    template <typename T>
    inline BinNodePosi(T) sibling(BinNodePosi(T) p) { return IsLchild(*p) ? p->parent->rc : p->parent->lc; }
    template <typename T>
    inline BinNodePosi(T) uncle(BinNodePosi(T) p) { return IsLchild(*(p->parent)) ? p->parent->parent->rc : p->parent->parent->lc; }
    template <typename T>
    inline BinNodePosi(T) FromParentTo(BinNodePosi(T) p) { return IsRoot(*p) ? p : (IsLchild(*p) ? p->parent->lc : p->parent->rc); }

    //defination
    template <typename T>
    template <typename VST>
    void BinNode<T>::travPre_R(BinNodePosi(T) p, VST &visit)
    {
        if (!p)
            return;
        visit(p->data);
        travPre_R(p->lc, visit);
        travPre_R(p->rc, visit);
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::visitAlongLeftBranch(BinNodePosi(T) p, VST &visit, Stack<BinNodePosi(T)> &S)
    {
        while (p)
        {
            visit(p->data);
            S.push(p->rc);
            p = p->lc;
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travPre_I1(BinNodePosi(T) p, VST &visit)
    {
        Stack<BinNodePosi(T)> S;
        while (true)
        {
            visitAlongLeftBranch(p, visit, S);
            if (S.empty)
                break;
            p = S.pop;
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travPre(VST &visit)
    {
        travPre_I1(this, visit);
    }

    template <typename T>
    template <typename VST>
    void BinNode<T>::travIn_R(BinNodePosi(T) p, VST &visit)
    {
        if (!p)
            return;
        travPre_R(p->lc, visit);
        visit(p->data);
        travPre_R(p->rc, visit);
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::goAlongLeftBranch(BinNodePosi(T) p, Stack<BinNodePosi(T)> &S)
    {
        while (p)
        {
            S.push(p);
            p = p->lc;
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travIn_I1(BinNodePosi(T) p, VST visit)
    {
        Stack<BinNodePosi(T)> S;
        while (true)
        {
            goAlongLeftBranch(p, S);
            if (S.empty())
                break;
            p = S.pop();
            visit(p->data);
            p = p->rc;
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travIn_I2(BinNodePosi(T) p, VST visit)
    {
        Stack<BinNodePosi(T)> S;
        while (true)
        {
            if (p)
            {
                S.push(p);
                p = p->lc;
            }
            else if (!S.empty())
            {
                p = S.pop();
                visit(p->data);
                p = p->rc;
            }
            else
                break;
        }
    }
    template <typename T>
    BinNodePosi(T) BinNode<T>::succ(BinNodePosi(T) p)
    {
        BinNodePosi(T) s = p;
        if (HasRChild(*s))
        {
            s = s->rc;
            while (s->rc)
                s = s->rc;
        }
        else
        {
            while (IsRchild(*s))
                s = s->parent;
            s = s->parent;
        }
        return s;
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travIn_I3(BinNodePosi(T) p, VST visit)
    {
        bool backtrace = false;
        while (true)
        {
            if (!backtrace && HasLChild(*p))
            {
                p = p->lc;
            }
            else
            {
                visit(p->data);
                if (HasRChild(*p))
                {
                    p = p->rc;
                    backtrace = false;
                }
                else
                {
                    if (!(p = p->succ()))
                        break;
                    backtrace = true;
                }
            }
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travIn(VST &visit)
    {
        srand(unsigned(time(NULL)));
        switch (rand() % 3)
        {
        case 1:
            cout << "travIn_I1" << endl;
            travIn_I1(this, visit);
            break;
        case 2:
            cout << "travIn_I2" << endl;
            travIn_I2(this, visit);
            break;
        default:
            cout << "travIn_I3" << endl;
            travIn_I3(this, visit);
            break;
        }
    }

    template <typename T>
    template <typename VST>
    void BinNode<T>::travPost_R(BinNodePosi(T) p, VST &visit)
    {
        if (!p)
            return;
        travPre_R(p->lc, visit);
        travPre_R(p->rc, visit);
        visit(p->data);
    }
    template <typename T>
    void gotoHLVFL(Stack<BinNodePosi(T)> &S)
    {
        BinNodePosi(T) p = S.top;
        while (!IsLeaf(*p))
        {
            if (HasLChild(*p))
            {
                if (HasRChild(*p))
                    S.push(p->rc);
                S.push(p->lc);
                p = p->lc;
            }
            else
            {
                S.push(p->rc);
                p = p->rc;
            }
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travPost_I(BinNodePosi(T) p, VST &visit)
    {
        Stack<BinNodePosi(T)> S;
        if (p)
            S.push(p);
        while (!S.empty())
        {
            if (p->parent != S.top())
                gotoHLVFL(S);
            else
            {
                p = S.pop();
                visit(p->data);
            }
        }
    }
    template <typename T>
    template <typename VST>
    void BinNode<T>::travPost(VST &visit)
    {
        return travPost_I(this, visit);
    }

    template <typename T>
    template <typename VST>
    void BinNode<T>::travLevel(VST &visit)
    {
        Quene<BinNodePosi(T)> Q;
        Q.enquene(this->data);
        while (!Q.empty())
        {
            BinNodePosi(T) p = Q.dequene();
            visit(p->data);
            if (HasLChild(*p))
                Q.enquene(p->lc);
            if (HasRChild(*p))
                Q.enquene(p->rc);
        }
    }
} // namespace shitong
#endif //__BIN_NODE_CPP_H