#ifndef SPLICER_H_INCLUDED
#define SPLICER_H_INCLUDED

#include <vector>
#include <algorithm>
/*
template <class T>
class splicer;

namespace detail
{

template<class T>
class SplicerIterator : public std::iterator<std::forward_iterator_tag, T>
{
private:
    typename std::vector<T>::iterator it;
public:
    explicit SplicerIterator (splicer<T>& spl) : it(spl.v.begin()) {}
    explicit SplicerIterator (typename std::vector<T>::iterator vit) : it(vit) {}

    SplicerIterator operator++()
    {
        return SplicerIterator(it++);
    }

    T& operator*()
    {
        return *it;
    }

    bool operator==(SplicerIterator other) const
    {
        return it == other.it;
    }

    bool operator!=(SplicerIterator other) const
    {
        return !(*this == other);
    }
};

}
*/
template<class T>
class splicer
{
private:
    typedef typename std::vector<T>::iterator Iterator;
    std::vector<T> v;

    void clear()
    {
        v.clear();
    }

public:

    template<class Container>
    splicer (Container &c)
    {
        v.insert(v.end(), c.begin(), c.end());
        c.clear();
    }

    template<class Container>
    splicer& append(Container &c)
    {
        v.insert(v.end(), c.begin(), c.end());
        c.clear();

        return *this;
    }

    int size() const
    {
        return v.size();
    }

    T& get(int i)
    {
        return v.at(i);
    }

    const T& get(int i) const
    {
        return v.at(i);
    }

    template <class Container>
    splicer& operator+=(Container &c)
    {
        (*this).append(c);
        c.clear();

        return *this;
    }

    template <class Elem>
    splicer& operator-=(const Elem& e)
    {
        v.erase(remove(v.begin(), v.end(), e), v.end());
        return *this;
    }

    template <class Container>
    splicer& splice(Container &c, typename Container::iterator first, typename Container::iterator last)
    {
        v.insert(v.end(), first, last);
        c.erase(first, last);
        return *this;
    }

    Iterator begin()
    {
        return v.begin();
    }

    Iterator end()
    {
        return v.end();
    }
};


#endif // SPLICER_H_INCLUDED
