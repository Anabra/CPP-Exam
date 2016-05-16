#ifndef UNSVEC_H_INCLUDED
#define UNSVEC_H_INCLUDED

#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>


/*
template <class Elem, class FirstCompare, class WrappedCompare>
struct Wrapper
{
    FirstCompare   firstCompare;
    WrappedCompare wrappedCompare;

    //if it is a baseWrapper then FirstComapre and WrappedCompare are the same
    Wrapper (FirstCompare first)
        : firstCompare(first), wrappedCompare(first) {}

    Wrapper (FirstCompare first, WrappedCompare wrapped)
        : firstCompare(first), wrappedCompare(wrapped) {}

    bool operator()(const Elem& lhs, const Elem& rhs)
    {
        bool isLhsLess = wrappedCompare(lhs, rhs);
        bool isRhsLess = wrapperCompare(rhs,lhs);

        if (!isLhsLess && !isRhsLess)
        {
            return firstCompare(lhs,rhs);
        }
        else
        {
            return isLhsLess;
        }
    }
};
*/

template <class T>
struct Comparator
{
    std::vector<std::function<bool (const T&, const T&)>> comparatorVect;

    Comparator () {}
    Comparator (const std::vector<std::function<bool (const T&, const T&)>> &comparatorVect) : comparatorVect(comparatorVect) {}

    Comparator& operator+=(std::function<bool (const T&, const T&)> f)
    {
        comparatorVect.push_back(f);
        return *this;
    }

    bool operator()(const T& lhs, const T& rhs) const
    {
        bool isLhsLess = comparatorVect.at(0)(lhs,rhs);
        bool isRhsLess = comparatorVect.at(0)(rhs,lhs);

        int i = 1;
        while (i < comparatorVect.size() && !isLhsLess && !isRhsLess)
        {
            isLhsLess = comparatorVect.at(i)(lhs,rhs);
            isRhsLess = comparatorVect.at(i)(rhs,lhs);
            i++;
        }

        return isLhsLess;
    }
};

template <class T>
struct UnaryComparator
{
    Comparator<T> comp;
    T elem;

    UnaryComparator (const T& elem, const Comparator<T> &comp) : comp(comp) {}

    bool operator()(const T& other) const
    {
        return comp(elem, other);
    }
};

template <class Container, class T, class Functor>
struct sort_inserter : public std::iterator<std::output_iterator_tag, T>
{
    Functor     unaryPred;
    Container   &container;

    sort_inserter (Container& container, const Functor& unaryPred) : unaryPred(unaryPred), container(container) {}

    sort_inserter& operator*  () { return *this; }
    sort_inserter& operator++ () { return *this; }
    sort_inserter& operator=(const T& elem)
    {
        unaryPred.elem = elem;
        container.insert(find_if(container.begin(), container.end(), unaryPred), elem);
        return *this;
    }
};





template <class T>
class unsortable_vector
{
private:
    Comparator<T>  comparator;
    std::vector<T> sortedVect;
    std::vector<T> unsortedVect;
    bool isSortOn;
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    template <class Container>
    explicit unsortable_vector (const Container &c) : isSortOn(false)
    {
        comparator += std::less<T>();
        unsortedVect.insert(unsortedVect.end(), c.cbegin(), c.cend());

        UnaryComparator<T> unaryComparator(*c.begin(), comparator);
        sort_inserter<std::vector<T>, T, UnaryComparator<T>> ins(sortedVect, unaryComparator);
        copy(unsortedVect.cbegin(), unsortedVect.cend(), ins);
    }

    explicit unsortable_vector (const T* p, int size) : isSortOn(false)
    {
        comparator += std::less<T>();
        unsortedVect.insert(unsortedVect.end(), p, p + size);

        UnaryComparator<T> unaryComparator(*p, comparator);
        sort_inserter<std::vector<T>, T, UnaryComparator<T>> ins(sortedVect, unaryComparator);
        copy(unsortedVect.cbegin(), unsortedVect.cend(), ins);
    }

    unsortable_vector& set_sort_off()
    {
        isSortOn = false;
        return *this;
    }
    unsortable_vector& set_sort_on()
    {
        isSortOn = true;
        return *this;
    }
    unsortable_vector& set_sort_on(std::function<bool (const T&, const T&)> f)
    {
        isSortOn = true;
        comparator += f;
        return *this;
    }

    int size() const
    {
        return unsortedVect.size();
    }

    T& at(int i)
    {
        if (isSortOn)
        {
            return sortedVect.at(i);
        }
        else
        {
            return unsortedVect.at(i);
        }
    }

    const T& at(int i) const
    {
        if (isSortOn)
        {
            return sortedVect.at(i);
        }
        else
        {
            return unsortedVect.at(i);
        }
    }

    T& operator[](int i)
    {
        if (isSortOn)
        {
            return sortedVect[i];
        }
        else
        {
            return unsortedVect[i];
        }
    }

    const T& operator[](int i) const
    {
        if (isSortOn)
        {
            return sortedVect[i];
        }
        else
        {
            return unsortedVect[i];
        }
    }

    unsortable_vector& operator+=(const unsortable_vector& other)
    {
        unsortedVect.insert(unsortedVect.end(), other.cbegin(), other.cend());

        UnaryComparator<T> unaryComparator(*other.cbegin(), comparator);
        sort_inserter<std::vector<T>, T, UnaryComparator<T>> ins(sortedVect, unaryComparator);
        copy(other.cbegin(), other.cend(), ins);
    }

    bool is_sorted() const
    {
        if (isSortOn)
        {
            return std::is_sorted(sortedVect.cbegin(), sortedVect.cend());
        }
        else
        {
            return std::is_sorted(unsortedVect.cbegin(), unsortedVect.cend());
        }
    }

    iterator begin()
    {
        if (isSortOn)
        {
            return sortedVect.begin();
        }
        else
        {
            return unsortedVect.begin();
        }

    }

    const_iterator begin() const
    {
        if (isSortOn)
        {
            return sortedVect.cbegin();
        }
        else
        {
            return unsortedVect.cbegin();
        }

    }

    iterator end()
    {
        if (isSortOn)
        {
            return sortedVect.end();
        }
        else
        {
            return unsortedVect.end();
        }

    }

    const_iterator end() const
    {
        if (isSortOn)
        {
            return sortedVect.cend();
        }
        else
        {
            return unsortedVect.cend();
        }

    }

    const_iterator cbegin() const
    {
        if (isSortOn)
        {
            return sortedVect.cbegin();
        }
        else
        {
            return unsortedVect.cbegin();
        }

    }

    const_iterator cend() const
    {
        if (isSortOn)
        {
            return sortedVect.cend();
        }
        else
        {
            return unsortedVect.cend();
        }
    }
};

#endif // UNSVEC_H_INCLUDED
