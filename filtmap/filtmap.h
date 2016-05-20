#ifndef FILTMAP_H_INCLUDED
#define FILTMAP_H_INCLUDED

#include <map>
#include <algorithm>

template <class KeyT, class ValueT, class Filter, class Comp = std::less<KeyT> >
class filterable_map
{
public:
    typedef typename std::map<KeyT, ValueT, Comp>::iterator iterator;
    typedef typename std::map<KeyT, ValueT, Comp>::const_iterator const_iterator;

    filterable_map () : isFilterOn(false), fSize(0) {}
    //default copy ctor is sufficient for us

    std::pair<iterator, bool> insert(const KeyT& key, const ValueT& value)
    {
        if (filter(key))
        {
            fSize++;
        }
        return data.insert(std::make_pair(key, value));
    }

    filterable_map& set_filter_off ()
    {
        isFilterOn = false;
        return *this;
    }

    filterable_map& set_filter_on ()
    {
        isFilterOn = true;
        return *this;
    }

    int size() const
    {
        return isFilterOn ? fSize : data.size();
    }

    int count(const KeyT& key) const
    {
        bool isNotFiltered = !filter(key);
        int c = data.count(key);    //zero or one -> false or true
        return isFilterOn ? isNotFiltered && c : c;
    }

    ValueT& at(const KeyT& key)
    {
        return data.at(key);
    }

    const ValueT& at(const KeyT& key) const
    {
        return data.at(key);
    }

    operator std::map<KeyT, ValueT, Comp> ()  const
    {
        if (!isFilterOn)
        {
            return data;
        }
        /* c++98
        std::map<KeyT, ValueT, Comp> m;
        for(const_iterator cit = data.begin(); cit != data.end(); ++cit)
        {
            if (!filter(cit->first)) {m.insert(*cit);}
        }

        return m;
        */
        const Filter& cFilterRef = this->filter;
        std::map<KeyT, ValueT, Comp> filteredMap;
        copy_if(data.cbegin(), data.cend(), std::inserter(filteredMap, filteredMap.end()),
             [this] (const typename std::map<KeyT, ValueT, Comp>::value_type& cur) -> bool { return !filter( cur.first); }   );

        return filteredMap;
    }






private:
    std::map<KeyT, ValueT, Comp> data;
    bool isFilterOn;
    typename std::map<KeyT, ValueT, Comp>::size_type fSize;
    Filter filter;
    Comp comp;


};

#endif // FILTMAP_H_INCLUDED
