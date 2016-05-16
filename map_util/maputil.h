#ifndef MAPUTIL_H_INCLUDED
#define MAPUTIL_H_INCLUDED

#include <map>
#include <iterator>
#include <algorithm>
#include <functional>

template <class KeyT, class ValueT>
struct key_has_value
{
    const ValueT val;

    key_has_value (const ValueT &v) : val(v) {}

    bool operator() (const std::pair<KeyT, ValueT> &pair) const
    {
        return pair.second == val;
    }
};

template <class KeyT, class ValueT>
struct key_satisfies_pred
{
    const std::function<bool (const ValueT&)> &pred;

    key_satisfies_pred (const std::function<bool (const ValueT&)> &pred) : pred(pred) {}

    bool operator() (const std::pair<KeyT, ValueT> &pair) const
    {
        return pred(pair.second);
    }
};

template <class KeyT, class ValueT, class Comparator = typename std::less<KeyT> >
class map_util
{
private:
    std::map<KeyT, ValueT, Comparator>* curMap;
public:
    typedef typename std::map<KeyT, ValueT>::iterator iterator;

    map_util (std::map<KeyT, ValueT, Comparator>& m) : curMap(&m) {}
    //map_util (std::map<KeyT, ValueT>& m) : curMap(&m) {}

    map_util& shift(int i = 1)
    {
        std::map<KeyT, ValueT, Comparator> oldMap = *curMap;
        iterator shiftedIt = oldMap.end();

        //in case the shift value (i) is greater than the size of the container
        for (int shiftValue = i % oldMap.size(); shiftValue > 0; shiftValue--)
        {
            shiftedIt--;
        }

        for (iterator it = curMap->begin(); it != curMap->end(); ++it)
        {
            it->second = (shiftedIt)->second;
            if(++shiftedIt == oldMap.end())    //in case we reached the end of the container
            {
                shiftedIt = oldMap.begin();
            }
        }

        return *this;
    }

    map_util& operator>>(int i)
    {
        this->shift(i);
        return *this;
    }

    map_util& use(std::map<KeyT, ValueT>& m)
    {
        curMap = &m;

        return *this;
    }

    map_util& erase(const ValueT &val)
    {
        key_has_value<KeyT, ValueT> pred(val);

        for (iterator it = curMap->begin(); it != curMap->end();)
        {
            if (pred(*it))
            {
                //only the iterators pointing to the erased value are invalidated
                //this is why we use it++ in the erase call
                curMap->erase(it++);
            }
            else
            {
                it++;
            }
        }

        return *this;
    }

    map_util& erase_if(const std::function<bool (const ValueT&)> &unaryPred)
    {
        key_satisfies_pred<KeyT, ValueT> pred(unaryPred);

        for (iterator it = curMap->begin(); it != curMap->end();)
        {
            if (pred(*it))
            {
                //only the iterators pointing to the erased value are invalidated
                //this is why we use it++ in the erase call
                curMap->erase(it++);
            }
            else
            {
                it++;
            }
        }

        return *this;
    }
};

#endif // MAPUTIL_H_INCLUDED
