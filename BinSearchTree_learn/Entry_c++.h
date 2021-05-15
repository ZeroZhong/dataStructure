#ifndef __ENTRY_CPP_H__
#define __ENTRY_CPP_H__

namespace shitong
{
    template <typename K, typename V>
    struct Entry
    {
        /* data */
        K key;
        V value;
        Entry(K k = K(), V v = V()) : key(k), value(v){};
        Entry(Entry<K, V> const &E) : key(E.key), value(E.value){};
        bool operator<(Entry<K, V> const &e){return key < e.key};
        bool operator>(Entry<K, V> const &e){return key > e.key};
        bool operator==(Entry<K, V> const &e){return key == e.key};
        bool operator!=(Entry<K, V> const &e){return key != e.key};
    };

} // namespace shitong

#endif template < typename K, typename V>