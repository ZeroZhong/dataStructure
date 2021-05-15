#ifndef __LIST_CPP_H__
#define __LIST_CPP_H__
#include "listnode_c++.h"
#include <iostream>
#include <time.h>
namespace shitong
{
    unsigned seed = time(NULL);
    template <typename T>
    class List
    {
    private:
        /* data */
        int _size;
        ListNodePosi(T) header;
        ListNodePosi(T) trailer;

    protected:
        void init();
        int clear();
        void copyNodes(ListNodePosi(T) &, int);
        void merge(ListNodePosi(T) &, int, List &, ListNodePosi(T), int);
        void mergeSort(ListNodePosi(T) &, int);
        void selectionSort(ListNodePosi(T) &, int);
        void insertionSort(ListNodePosi(T) &, int);
        static void print(T const &e) { std::cout << e << ' '; }

    public:
        List(/* args */) { init(); };
        List(List<T> const &);
        List(List<T> const &, Rank, int);
        List(ListNodePosi(T), int);
        ~List();
        //ReadOnly
        Rank size() const { return _size; };
        bool empty() const { return !_size; };
        T &operator[](Rank r) const;
        ListNodePosi(T) first() const { return header->succ; };
        ListNodePosi(T) last() const { return trailer->pred; };
        bool valid(ListNodePosi(T) p) { return p && (p != header) && (p != trailer); };
        int disordered() const;
        ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
        ListNodePosi(T) find(T const &e) const { return find(e, _size, trailer); };
        ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
        ListNodePosi(T) search(T const &e) { return search(e, _size, trailer); };
        ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
        ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); };
        void output() { traverse(this->print); };
        //ReadAndWrite
        ListNodePosi(T) insertAsFirst(T const &e);
        ListNodePosi(T) insertAsLast(T const &e);
        ListNodePosi(T) insertP(ListNodePosi(T) p, T const &e);
        ListNodePosi(T) insertS(ListNodePosi(T) p, T const &e);
        T remove(ListNodePosi(T) p);
        void merge(List<T> &L);
        void sort(ListNodePosi(T) p, int n);
        void sort()
        {
            sort(first(), _size);
        };
        int deduplicate();
        int uniquify();
        void reverse();
        //traverse
        void traverse(void (*)(T &));
        template <typename VST>
        void traverse(VST &);
    }; //List
    template <typename T>
    void List<T>::init()
    {
        header = new ListNode<T>(0, nullptr, trailer);
        trailer = new ListNode<T>(0, header, nullptr);
        _size = 0;
    }
    template <typename T>
    int List<T>::clear()
    {
        int oldsize = _size;
        while (_size)
            remove(header->succ);
        return oldsize;
    }
    template <typename T>
    void List<T>::copyNodes(ListNodePosi(T) & p, int n)
    {
        init();
        while (n--)
        {
            header->insertAsSucc(p->data);
            p = p->succ;
        }
    }
    template <typename T>
    void List<T>::merge(ListNodePosi(T) & p, int a, List &L, ListNodePosi(T) q, int b)
    {
        ListNodePosi(T) pp = p->pred;
        while (b > 0)
        {
            if (a > 0 && !(p->data > q->data))
            {
                a--;
                if (q == (p = p->succ))
                    break;
            }
            else
            {
                insertP(p, L.remove((q = q->succ)->pred));
                b--;
            }
        }
        p = pp->succ;
    }
    template <typename T>
    void List<T>::mergeSort(ListNodePosi(T) & p, int n)
    {
        if (n < 2)
            return;
        int m = n >> 1;
        ListNodePosi(T) q = p;
        for (int i = 0; i < m; i++)
            q = q->succ;
        mergeSort(p, m);
        mergeSort(q, n - m);
        merge(p, m, *this, q, n - m);
    }
    template <typename T>
    void List<T>::selectionSort(ListNodePosi(T) & p, int n)
    {
        ListNodePosi(T) head = p->pred;
        ListNodePosi(T) tail = p;
        for (int r = 0; r < n; r++)
            tail = tail->succ;
        while (n > 1)
        {
            ListNodePosi(T) max = selectMax(head->succ, n);
            insertP(tail, remove(max));
            tail = tail->pred;
            n--;
        }
    }
    template <typename T>
    void List<T>::insertionSort(ListNodePosi(T) & p, int n)
    {
        for (int r = 0; r < n; r++)
        {
            insertP(search(p->data, r, p->pred), p->data);
            remove((p = p->succ)->pred);
        }
    }
    template <typename T>
    List<T>::List(List<T> const &L)
    {
        copyNodes(L.first(), L, size());
    }
    template <typename T>
    List<T>::List(List<T> const &L, Rank r, int n)
    {
        ListNodePosi(T) p = L.first();
        while (r--)
            p = p->succ;
        copyNodes(p, n);
    }
    template <typename T>
    List<T>::List(ListNodePosi(T) p, int n)
    {
        copyNodes(p, n);
    }
    template <typename T>
    List<T>::~List()
    {
        clear();
        delete header;
        delete trailer;
    }
    template <typename T>
    T &List<T>::operator[](Rank r) const
    {
        ListNodePosi(T) p = first();
        while (r--)
            p = p->succ;
        return p->data;
    }
    template <typename T>
    int List<T>::disordered() const
    {
        ListNodePosi(T) p = trailer;
        int i = _size;
        while ((p = p->pred) != first())
        {
            swap(p->data, this[rand() % --i]);
        }
        return i;
    }
    template <typename T>
    ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const
    {

        while (--n)
        {
            if (p->data == e)
                return p;
            p = p->pred;
        }
        return nullptr;
    }
    template <typename T>
    ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p) const
    {
        while (n--)
        {
            if (!(p->data > e))
                break;
            p = p->pred;
        }
        return p->succ;
    }
    template <typename T>
    ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
    {
        ListNodePosi(T) max = p;
        while (--n)
        {
            if (!((p = p->succ)->data < max->data))
                max = p;
            // std::cout << p->data << ' ' << max->data << std::endl;
        }
        return max;
    }
    template <typename T>
    ListNodePosi(T) List<T>::insertAsFirst(T const &e)
    {
        _size++;
        return header->insertAsSucc(e);
    }
    template <typename T>
    ListNodePosi(T) List<T>::insertAsLast(T const &e)
    {
        _size++;
        return trailer->insertAsPred(e);
    }
    template <typename T>
    ListNodePosi(T) List<T>::insertP(ListNodePosi(T) p, T const &e)
    {
        _size++;
        return p->insertAsPred(e);
    }
    template <typename T>
    ListNodePosi(T) List<T>::insertS(ListNodePosi(T) p, T const &e)
    {
        _size++;
        return p->insertAsSucc(e);
    }
    template <typename T>
    T List<T>::remove(ListNodePosi(T) p)
    {
        T e = p->data;
        p->succ->pred = p->pred;
        p->pred->succ = p->succ;
        delete p;
        _size--;
        return e;
    }
    template <typename T>
    void List<T>::sort(ListNodePosi(T) p, int n)
    {
        srand(seed);
        switch (rand() % 3)
        {
        case 1:
            std::cout << "insertion";
            insertionSort(p, n);
            break;
        case 2:
            std::cout << "selection";
            selectionSort(p, n);
            break;

        default:
            std::cout << "merge";
            mergeSort(p, n);
            break;
        }
        // insertionSort(p, n);
        // selectionSort(p, n);
        // mergeSort(p, n);
    }
    template <typename T>
    int List<T>::deduplicate()
    {
        if (_size < 2)
            return 0;
        int oldsize = _size;
        ListNodePosi(T) p = header;
        Rank r = 0;
        while ((p = p->succ) != trailer)
        {
            ListNodePosi(T) q = find(p->data, r, p);
            q ? remove(q) : r++;
        }
        return _size - oldsize;
    }
    template <typename T>
    int List<T>::uniquify()
    {
        if (_size < 2)
            return 0;
        int oldsize = _size;
        ListNodePosi(T) p = first();
        while ((p = p->succ) != trailer)
        {
            if (p->data == p->pred->data)
                remove(p->pred);
        }
        return oldsize - _size;
    }
    template <typename T>
    void List<T>::reverse()
    {
        Rank lo = 0, hi = _size;
        ListNodePosi(T) p = header->succ;
        ListNodePosi(T) s = trailer->pred;
        while ((++lo) < (--hi))
        {
            std::swap(p->data, s->data);
            p = p->succ;
            s = s->pred;
        }
    }
    template <typename T>
    void List<T>::traverse(void (*visit)(T &e))
    {
        ListNodePosi(T) p = header;
        while ((p = p->succ) != trailer)
        {
            visit(p->data);
        }
    }
    template <typename T>
    template <typename VST>
    void List<T>::traverse(VST &visit)
    {
        ListNodePosi(T) p = header;
        while ((p = p->succ) != trailer)
        {
            visit(p->data);
        }
    }

}
#endif //__LIST_CPP_H__