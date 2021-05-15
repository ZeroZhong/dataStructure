#if !defined(__SKIPLIST__CPP_H__)
#define __SKIPLIST__CPP_H__

#include "../Dictionary_c++.h"
#include "QuadList_c++.h"
#include "../../BinSearchTree_learn/Entry_c++.h"
#include "../../List_learn/listNode/list_c++.h"
namespace shitong
{
    template <typename K, typename V>
    class SkipList : public Dictionary<K, V>, public List<QuadList<Entry<K, V>> *>
    {
    protected:
        /* data */
        bool skipSearch();

    public:
        int size() const { return last()->data->size(); }
        int level() const { return List::size(); }
        bool put(K, V);
        V *get(K);
        bool remove(K) :
    };

} // namespace shitong

#endif // __SKIPLIST__CPP_H__
