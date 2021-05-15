#include "../../vecter_learn/vector/vector_c++.h"
namespace shitong
{

    template <typename T>
    class Stack : Vector<T>
    {
    public:
        void push(T const &e) { insert(this->size(), e); }
        T pop() { return remove(this->size() - 1); }
        T &top() { return (*this)[this->size() - 1]; }
    };
}
