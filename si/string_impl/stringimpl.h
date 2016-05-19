#ifndef STRINGIMPL_H_INCLUDED
#define STRINGIMPL_H_INCLUDED

#include <algorithm>


//template <class Container, class CharT>
template<class Container, class CharT = typename Container::value_type>
class string_implemented_with
{
private:
    Container cont;
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    static const int npos;

    string_implemented_with (CharT* p) : cont(p, p + std::char_traits<CharT>::length(p))
    {
        *p = '\0';
    }

    string_implemented_with& erase (const int startpos, const int length)
    {
        iterator first = cont.begin();

        std::advance(first, startpos);
        iterator last = first;
        std::advance(last, length);

        cont.erase(first, last);    //all iterators can be invalidated --depending on the type of the container

        return *this;
    }

    CharT& at(int i)                            //should throw exception
    {
        iterator it = cont.begin();
        std::advance(it, i);
        return *it;
    }

    const CharT& at(int i) const                //should throw exception
    {
        const_iterator cit = cont.cbegin();
        std::advance(cit, i);
        return *cit;
    }

    CharT& operator[](int i)
    {
        this->at(i);
    }

    const CharT& operator[](int i) const
    {
        this->at(i);
    }

    template<class ConT, class ChT = typename ConT::value_type>
    int find_first_not_of(const string_implemented_with<ConT, ChT> &simw) const
    {
        for (const_iterator cit = this->cbegin(); cit != this->cend(); ++cit)
        {
            if (find(simw.cbegin(), simw.cend(), *cit) == simw.cend())
            {
                return std::distance(this->cbegin(), cit);
            }
        }

        return npos;
    }

    int length() const
    {
        return cont.size();
    }

    iterator begin()        { return cont.begin();}
    iterator end()          { return cont.end();}
    const_iterator cbegin() const { return cont.cbegin();}
    const_iterator begin()  const { return cont.cbegin();}
    const_iterator cend()   const { return cont.cend();}
    const_iterator end()    const { return cont.cend();}

};

template <class ContainerT, class CharT>
const int string_implemented_with<ContainerT, CharT>::npos = -1;

#endif // STRINGIMPL_H_INCLUDED
