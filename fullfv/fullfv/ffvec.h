#ifndef FFVEC_H_INCLUDED
#define FFVEC_H_INCLUDED

#include <vector>
#include <algorithm>
#include <iterator>

template <class T>
class full_fledged_vector
{
public:
    static const int npos;

    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    full_fledged_vector () {}
    full_fledged_vector (const T* p, const int length) : data(p, p + length) {}
    full_fledged_vector (const_iterator first, const_iterator last) : data(first, last) {}

    full_fledged_vector& push_back(const T& e)
    {
        data.push_back(e);
        return *this;
    }

    full_fledged_vector subvec (const int pos, const int length) const
    {
        return full_fledged_vector(this->cbegin() + pos, this->cbegin() + pos + length);
    }

    int size() const
    {
        return data.size();
    }

    T& at(int pos)
    {
        return data.at(pos);
    }

    const T& at(int pos) const
    {
        return data.at(pos);
    }

    full_fledged_vector& append(const T* p, const int length)
    {
        for (const T* q = p; q != p + length; q++)
        {
            data.insert(data.end(), *q);
        }

        return *this;
    }

    template <class ContainerT>
    full_fledged_vector& append(const ContainerT& cont)
    {
        copy(cont.begin(), cont.end(), std::back_insert_iterator<std::vector<T>>(data));
        return *this;
    }

    template <class ContainerT>
    int find_first_of(const ContainerT& cont) const
    {
        for (const_iterator cit = this->cbegin(); cit !=  this->cend(); ++cit)
        {
            if (find(cont.cbegin(), cont.cend(), *cit) != cont.cend())
            {
                return std::distance(this->cbegin(), cit);
            }
        }

        return npos;
    }

    T& operator[] (const int pos)
    {
        return data[pos];
    }

    full_fledged_vector& operator+=(const full_fledged_vector<T>& other)
    {
        this->append(other);
    }

    template <class ConstIteratorType>
    full_fledged_vector& replace (iterator d_first,
                                  iterator d_last,
                                  ConstIteratorType f_first,
                                  ConstIteratorType f_last)
    {
        iterator pos = data.erase(d_first, d_last);
        for(ConstIteratorType cit = f_first; cit != f_last; ++cit)
        {
            data.insert(pos++, *cit);
        }

        return *this;
    }

    operator typename std::basic_string<T>()
    {
        return std::basic_string<T>(this->cbegin(), this->cend());
    }

    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator cbegin() const { return data.cbegin(); }
    const_iterator begin() const { return data.cbegin(); }
    const_iterator cend() const { return data.cend(); }
    const_iterator end() const { return data.cend(); }

private:
    std::vector<T> data;
};

template <class T>
const int full_fledged_vector<T>::npos = -1;

#endif // FFVEC_H_INCLUDED
