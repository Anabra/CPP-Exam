#include <map>
#include <algorithm>
#include <iostream>
#include "maputil.h"
#include <string>
#include "maputil.h"

struct contains
{

    bool operator()( const std::string& s ) const
    {
        return std::find( s.begin(), s.end(), 'A' ) != s.end();
    }

};

struct string_size_less
{

    bool operator()( const std::string& lhs,
                     const std::string& rhs ) const
    {
        return lhs.size() < rhs.size();
    }

};

const int max = 1000;

struct size_pred
{

    bool operator()( const std::string& s ) const
    {
        return max / 2 < s.size();
    }

};


//you need to implement a container that can alter the current parameter (type should be std::map)
//it will be a wrapper container for a map, which will allow the usage of certain operations on that map (for example shifting the values)
//these operations WILL alter the current map's structure
//you can change the current map, by calling the use() member function (this will ditch the old map, and set the current map to the given parameter)
int main()
{
    int your_mark = 1;

    std::map<int, std::string> mis;
    std::map<int, std::string> amis;
    for( int i = 0; i < max; ++i )
    {
        mis[ i ] = std::string( i, 'A' );
        amis[ i ] = std::string( i, 0 == i % 2 ? 'R' : 'r' );
    }
    map_util<int, std::string> uis( mis );        //it will "use" mis
    uis.shift();                                  //it will shift the currently used map's values to the right
    uis.use( amis );                              //it will change the map being used
    uis.shift();

    std::map<std::string, int> msi;
    msi[ "Hello" ] = 4;
    msi[ "World" ] = 7;
    map_util<std::string, int> usi( msi );
    usi.shift();

    if ( 4 == msi[ "World" ] && max - 1u == mis[ 0 ].length() &&
            max * 1u == mis.size() && mis[ 1 ].empty() && "r" == amis[ 2 ] )
    {
        your_mark = amis[ 3 ].length();
    }


    uis.shift( max / 2 );       //shift by value
    uis.use( mis );
    uis.shift( 2 );
    uis.erase( "AAA" );         //erase key-value pair with the given value
    uis.erase( "AAAAA" );
    uis.erase( "A" );

    usi.erase( 4 );             //it currently uses msi


    if ( 1 == msi.size() && 0 == msi.count( "World" ) && 0 == mis.count( 6 ) &&
         amis[ max / 2 + 1 ].empty() && 'r' == amis.begin()->second.at( 0 ) &&
         "AAAA" == mis[ 7 ] )
    {
      your_mark = amis.size() - mis.size();
    }


    msi[ "World" ] = 1;
    usi >> 1;                           //overloaded operator>>

    uis >> 2;
    uis.erase_if( contains() );         //erase_if with unary predicate
    uis.use( amis );
    uis.erase_if( size_pred() );
    uis >> 3;


    if ( 7 == msi[ "World" ] && 1 == mis.size() && max / 2u + 1  == amis.size() &&
         1 == amis.count( 0 ) && 1 == amis.count( max - 1 ) && 0 == amis.count( max / 2 ) )
    {
      your_mark = msi.size() + mis.size() + msi[ "Hello" ];
    }


    std::map<std::string, int, string_size_less> ls;            //sort by binary predicate
    ls[ "C++" ] = 5;
    ls[ "Eiffel" ] = 1;
    ls[ "Java" ] = 0;
    ls[ "Go" ] = 2;


    //ls[ "Go" ] = 2;
    //ls[ "C++" ] = 5;
    //ls[ "Java" ] = 0;
    //ls[ "Eiffel" ] = 1;

    map_util<std::string, int, string_size_less> uls( ls );
    uls >> 2;
    uls.erase( 2 );

    if ( 0 == ls.count( "Java" ) && 3 == ls.size() && 0 == ls.begin()->second )
    {
      your_mark = ls[ "Eiffel" ];
    }

    std::cout << "Your mark is " << your_mark;
    std::endl( std::cout );
}
