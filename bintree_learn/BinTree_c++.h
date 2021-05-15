#include "BinNode_c++.h"
namespace shitong
{

    template <typename T>
    class BinTree
    {
    protected:
        int _size;
        BinNodePosi(T) _root;
        virtual int updateHeight(BinNodePosi(T) x)
        {
            return 1 + std::max(stature(x->lc), stature(x->rc));
        }
        void updateHeightAbove(BinNodePosi(T) x)
        {
            while (x)
            {
                x->height = updateHeight(x);
                x = x->parent;
            }
        }

    public:
        BinTree() : _size(0), _root(nullptr){};
        ~BinTree()
        {
            if (0 < _size)
                remove(_root);
        }
        int size() const { return _size; }
        bool empty() const { return !_root; }
        BinNodePosi(T) root() const { return _root; }
        BinNodePosi(T) InsertAsRoot(T const &e);
        BinNodePosi(T) InsertAsLC(BinNodePosi(T) x, T const &e);
        BinNodePosi(T) InsertAsRC(BinNodePosi(T) x, T const &e);
        BinNodePosi(T) AttachAsLC(BinNodePosi(T) X, BinTree<T> const &t);
        BinNodePosi(T) AttachAsRC(BinNodePosi(T) X, BinTree<T> const &t);
        void remove(BinNodePosi(T) x) { delete x; };
        BinTree<T> *secede(BinNodePosi(T));
        template <typename VST>
        void travLevel(VST &visit)
        {
            if (_root)
                _root->travLevel(visit);
        }
        template <typename VST>
        void travPre(VST &visit)
        {
            if (_root)
                _root->travPre(visit);
        }
        template <typename VST>
        void travIn(VST &visit)
        {
            if (_root)
                _root->travIn(visit);
        }
        template <typename VST>
        void travPost(VST &visit)
        {
            if (_root)
                _root->travPost(visit);
        }
        bool operator<(BinTree<T> const &t)
        {
            return _root && t.root() && _root < t.root();
        }
        bool operator==(BinTree<T> const &t)
        {
            return _root && t.root() && _root == t.root();
        }
    };

    //defination
    template <typename T>
    BinNodePosi(T) BinTree<T>::InsertAsRoot(T const &e)
    {
        _size = 1;
        return _root = new BinNode<T>(e);
    }
    template <typename T>
    BinNodePosi(T) BinTree<T>::InsertAsRC(BinNodePosi(T) p, T const &e)
    {
        p->insertAsRC(e);
        _size++;
        updateHeightAbove(p);
        return p->rc;
    }
    template <typename T>
    BinNodePosi(T) BinTree<T>::InsertAsLC(BinNodePosi(T) p, T const &e)
    {
        p->insertAsLC(e);
        _size++;
        updateHeightAbove(p);
        return p->lc;
    }
} // namespace shitong