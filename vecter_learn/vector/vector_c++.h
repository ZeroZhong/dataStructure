#ifndef __SHITONG_VECTOR__
#define __SHITONG_VECTOR__

#include <iostream>
#include <cstdlib>
namespace shitong
{

    typedef int Rank;
#define DEFAULT_CAPACITY 3
    unsigned seek;

    template <typename T>
    class Vector
    {
    protected:
        Rank _size;
        int _capacity;
        T *_elem;

        void copyFrom(T const *A, Rank lo, Rank hi);
        void expand();
        void shrink();
        Rank binSearch(T const *A, T const &e, Rank lo, Rank hi);
        //Rank FibSearch(T const *A, T const &e, Rank lo, Rank hi);
        bool bubble(Rank lo, Rank hi);     //扫描交换
        void bubbleSort(Rank lo, Rank hi); //冒泡排序
        Rank max(Rank lo, Rank hi);
        void selectionSort(Rank lo, Rank hi);  //选择排序
        void merge(Rank lo, Rank mi, Rank hi); //归并
        void mergeSort(Rank lo, Rank hi);      //归并排序
        static void print(T &e) { std::cout << e << ' '; }

    public:
        Vector(int c = DEFAULT_CAPACITY, int s = 3, T v = 0)
        {
            _elem = new T[_capacity = c];
            for (_size = 0; _size < s; _elem[_size++] = v)
                ;
        } //整体构造，初始化为0
        Vector(T const *A, Rank lo, Rank hi)
        {
            copyFrom(A, lo, hi);
        }
        Vector(T const *A, Rank n)
        {
            copyFrom(A, 0, n);
        } //数组复制构造
        Vector(Vector<T> const &A, Rank lo, Rank hi)
        {
            copyFrom(A._elem, lo, hi);
        }
        Vector(Vector<T> const &A, Rank n)
        {
            copyFrom(A._elem, 0, n);
        } //向量复制构造
        ~Vector() { delete[] _elem; }

        Rank size() const { return _size; };
        bool empty() const { return !_size; };
        int disordered() const;
        Rank find(T const &e, Rank lo, Rank hi) const; //无序向量区间查找
        Rank find(T const &e) const
        {
            return find(e, 0, _size);
        }
        Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找
        Rank search(T const &e) const
        {
            return (0 >= _size ? -1 : search(e, 0, _size));
        }

        T &operator[](Rank r) const { return _elem[r]; }
        Vector<T> &operator=(Vector<T> const &A) { return Vector(A, A.size()); }
        int remove(Rank lo, Rank hi); //移除
        T remove(Rank r)
        {
            T old = _elem[r];
            remove(r, r + 1);
            return old;
        }
        Rank insert(Rank r, T const &e); //插入
        Rank insert(T const &e) { return insert(_size, e); }
        void sort(Rank lo, Rank hi); //有序
        void sort() { sort(0, _size); }
        void unsort(Rank lo, Rank hi); //乱序
        void unsort() { unsort(0, _size); }
        int deduplicated(); //无序去重
        int uniquify();     //有序去重

        void output() { this->traverse(this->print); }

        void traverse(void (*)(T &));
        template <typename VST>
        void traverse(VST &);
    }; //Vector

    //defination
    template <typename T>
    void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
    {
        _capacity = (_size = hi - lo + 1) << 1;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; i++)
            _elem[i] = A[lo + i];
    }
    template <typename T>
    void Vector<T>::expand()
    {
        if (_capacity - _size < _capacity >> 2)
        {
            T *old = _elem;
            _elem = new T[_capacity << 1];
            for (int i = 0; i < _size; _elem[i++] = old[i])
                ;
            delete[] old;
            return;
        }
        else
            return;
    }
    template <typename T>
    void Vector<T>::shrink()
    {
        if (_capacity >> 2 > _size)
        {
            T *old = _elem;
            _elem = new T[_size << 1];
            for (int i = 0; i < _size; i++)
                _elem[i] = old[i];
            delete[] old;
            return;
        }
        else
            return;
    }
    template <typename T>
    Rank Vector<T>::binSearch(T const *A, T const &e, Rank lo, Rank hi)
    {
        while (lo < hi)
        {
            Rank mi = (hi + lo) >> 1;
            (e < A[mi]) ? hi = mi : lo = mi;
        }
        return --lo;
    }
    // template <typename T>
    // Rank Vector<T>::FibSearch(T const *A, T const &e, Rank lo, Rank hi)
    // {

    // }
    template <typename T>
    int Vector<T>::disordered() const
    {
        int n = 0;
        for (int i = 1; i < _size; i++)
        {
            if (_elem[i - 1] > _elem[i])
                n++;
        }
        return n;
    }
    template <typename T>
    bool Vector<T>::bubble(Rank lo, Rank hi)
    {
        bool sorted = true;
        while (++lo < hi)
        {
            if (_elem[lo - 1] > _elem[lo])
            {
                sorted = false;
                std::swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return sorted;
    }
    template <typename T>
    void Vector<T>::bubbleSort(Rank lo, Rank hi)
    {
        while (!bubble(lo, hi--))
            ;
    }
    template <typename T>
    Rank Vector<T>::max(Rank lo, Rank hi)
    {
        Rank r = lo;
        while (lo++ < hi)
        {
            if (_elem[r] < _elem[lo])
                r = lo;
        }
        return r;
    }
    template <typename T>
    void Vector<T>::selectionSort(Rank lo, Rank hi)
    {
    }
    template <typename T>
    void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
    {
        T *A = _elem + lo;
        Rank lb = mi - lo;
        Rank lc = hi - mi;
        T *B = new T[lb];
        for (int i = 0; i < lb; i++)
            B[i] = A[i];
        T *C = _elem + mi;
        Rank i = 0, j = 0, k = 0;
        while (j < lb || k < lc)
        {
            if (!(k < lc) && (j < lb) || !(C[k] < B[j]) && (j < lb))
                A[i++] = B[j++];
            if (!(j < lb) && (k < lc) || C[k] < B[j] && (k < lc))
                A[i++] = C[k++];
        }
        delete[] B;
    }
    template <typename T>
    void Vector<T>::mergeSort(Rank lo, Rank hi)
    {
        if (hi - lo < 2)
            return;
        Rank mi = (hi + lo) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }
    template <typename T>
    Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
    {
        while ((lo < hi--) && e != _elem[hi])
            ;
        return hi;
    }
    template <typename T>
    Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const
    {
        // return (rand() % 2) ? binSearch(_elem, e, lo, hi) : FibSearch(_elem, e, lo, hi);
        return binSearch(_elem, e, lo, hi);
    }
    template <typename T>
    int Vector<T>::remove(Rank lo, Rank hi)
    {
        if (lo == hi)
            return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    template <typename T>
    Rank Vector<T>::insert(Rank r, T const &e)
    {
        expand();
        for (int i = _size; i > r; _elem[i--] = _elem[i - 1])
            ;
        _elem[r] = e;
        _size++;
        return r;
    }
    template <typename T>
    void Vector<T>::sort(Rank lo, Rank hi)
    {
        std::srand(seek);
        return (rand() % 2) ? bubbleSort(lo, hi) : mergeSort(lo, hi);
        // return bubbleSort(lo, hi);
        // return mergeSort(lo, hi);
    }
    template <typename T>
    void Vector<T>::unsort(Rank lo, Rank hi)
    {
        std::srand(seek);
        T *V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
            std::swap(V[i - 1], V[rand() % i]);
    }
    template <typename T>
    int Vector<T>::deduplicated()
    {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size)
            (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
        return oldSize - _size;
    }
    template <typename T>
    int Vector<T>::uniquify()
    {
        Rank i = 0, j = 0;
        while (j < _size)
        {
            if (_elem[i] != _elem[j++])
                _elem[i++] = _elem[j];
        }
        _size = i + 1;
        shrink();
        return j - i;
    }
    template <typename T>
    void Vector<T>::traverse(void (*visit)(T &))
    {
        for (int i = 0; i < _size; i++)
            visit(_elem[i]);
    }
    template <typename T>
    template <typename VST>
    void Vector<T>::traverse(VST &visit)
    {
        for (int i = 0; i < _size; i++)
            visit(_elem[i]);
    }
} // namespace shitong
#endif