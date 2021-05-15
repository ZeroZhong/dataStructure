#if !defined(__DICTIONARY_CPP_H__)
#define __DICTIONARY_CPP_H__

namespace shitong
{
    template <typename K, typename V>
    struct Dictionary
    {
        virtual int size() const = 0;
        virtual bool put(K, V) = 0;
        virtual V *get(K) = 0;
        virtual bool remove(K) = 0;
    };

} // namespace shitong

#endif // __DICTIONARY_CPP_H__
