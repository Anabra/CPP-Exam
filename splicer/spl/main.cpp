#include <iostream>
#include <deque>
#include <string>
#include "splicer.h"
#include <list>
#include "splicer.h"
#include <vector>
#include <set>

const int max = 1000;

struct string_size_less
{

    bool operator()( const std::string& a, const std::string& b ) const
    {
        return a.size() < b.size();
    }

};

//you need to implement a container that can store values from any container-type (you can move values from a container to this one)
//the container from which you want to transport the values from, will be cleared
int main()
{

    int your_mark = 1;

    std::list<int> ci;
    for( int i = 0; i < max; ++i )
    {
        ci.push_back( i );
    }
    splicer<int> spi( ci );           //needs a ctor from list&        --will eat up the elements of the list
    const splicer<int> cspi ( spi );  //needs a ctor from splicer&     --will eat up the elements of the splicer

    std::list<std::string> cs;
    cs.push_back( "Hello" );
    splicer<std::string> sps( cs );
    cs.push_back( "World" );
    sps.append( cs );                 //needs an "append(list)" member function

    if ( cs.empty() && ci.empty() && 0 == spi.size() &&                              //needs size() member function
            max / 2 == cspi.get( max / 2 ) && max / 3 == cspi.get( max / 3 ) &&      //needs get()  member function   --should return reference
            5 == sps.get( 0 ).size() )
    {
        your_mark = sps.size();
    }


    for( int i = 0; i < max; ++i )
    {
      ci.push_back( i );
    }
    splicer<int> t ( ci );
    for( int i = 0; i < t.size(); ++i )
    {
      if ( 0 == i % 2 )
      {
        t.get( i ) = max + 1;
      }
    }
    t += ci;              //is ci empty?   --it should be
    t -= ( max + 1 );     //removes all given elements

    cs.push_back( "?" );
    cs.push_back( "!" );
    sps += cs;
    sps -= "?";
    if ( cs.empty() && "!" == sps.get( 2 ) && max / 2 == t.size() &&
         ci.empty() && 3 == t.get( 1 ) )
    {
      your_mark = sps.size();
    }


    std::deque<double> s;
    s.push_back( 1.47 );

    std::deque<double> d = s;
    std::set<double> sd( s.begin(), s.end() );

    splicer<double> ts( sd );
    ts += d;        //basically append

    std::multiset<std::string, string_size_less> m;
    m.insert( "Assembly" );
    m.insert( "C++" );
    std::vector<std::string> vs;
    vs.push_back( "Ada" );
    splicer<std::string> ms( m );
    ms += vs;

    if ( d.empty() && 3 == ms.size() && m.empty() && vs.empty() &&
         "C++" == ms.get( 0 ) && "Ada" == ms.get( 2 ) )
    {
      your_mark = ms.get( 1 ).size() / ts.size();
    }


    std::deque<int> di;
    std::list<int> li;
    for( int i = 0; i < max; ++i )
    {
      di.push_back( i );
      li.push_back( i );
    }
    splicer<int> spt( li );
    spt.splice( di, di.begin() + 2, di.end() - 3 );

    m.insert( "Ada" );
    m.insert( "Java");
    ms.splice( m, m.begin(), m.end() );

    if ( 2 == spt.get( max ) && max < spt.size() &&
         m.empty() && "Ada" == ms.get( 3 ) )
    {
      your_mark = di.size();
    }

    std::cout << "Your mark is " << your_mark;
    std::endl( std::cout );
}
