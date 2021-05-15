#ifndef __QUENE_CPP_H__
#define __QUENE_CPP_H__
#include "../List_learn/listNode/list_c++.h"
namespace shitong
{
    template <typename T>
    class Quene : public List<T>
    {
    public:
        Quene(){};
        void enquene(T const &e) { insertAsLast(e); }
        T dequene() { return remove(this->first()); }
        T &front() { return this->first(); }
        ~Quene(){};
    };
} // namespace shitong
#endif