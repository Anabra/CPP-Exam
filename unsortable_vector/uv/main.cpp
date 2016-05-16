#include <numeric>
#include <iostream>
#include <functional>
#include "unsvec.h"
#include <string>
#include "unsvec.h"
#include <algorithm>

struct string_size_less
{

    bool operator()( const std::string& a, const std::string& b ) const
    {
        return a.size() < b.size();
    }

};

const int max = 128;

struct pred
{

    bool operator()( const std::string& s ) const
    {
        return s.size() % max != 0;
    }

};

//you need to implement a container that stores sorted and an unsorted version of elements in itself
//you can set_sort_on and off, meaning that you want handle the stored elements sorted or unsorted
//with the set_sort_on function you can ADD additional layers of comparators (the sorts stack, the first one added is the strongest) --you need this only for mark 4 and 5
//the default sort is std::less<T>
int main()
{
    int your_mark = 1;

    const std::string a[] = {"Java", "C++", "Fortran"};
    const unsortable_vector<std::string> cvs( a, sizeof( a ) / sizeof( a[ 0 ] ) );        //needs a ctor that copies from vector and sets its size
    unsortable_vector<std::string> vs( a, sizeof( a ) / sizeof( a[ 0 ] ) );

    const int v[] = { 7, 1, 8, 4 };
    unsortable_vector<int> s ( v, sizeof( v ) / sizeof( v[ 0 ] ) );

    for( int i = 0; i < max; ++i )
    {
        s.set_sort_on().set_sort_off();
    }



    vs.set_sort_on().set_sort_off().set_sort_on();                    //should store a sorted, and a default container

    if ( 3 == cvs.size() && "C++" == vs.at( 0 ) &&
            cvs.at( 0 ) == vs.at( 2 ) && "Fortran" == cvs.at( 2 ) &&      //alphabetical sort
            !cvs.is_sorted() && vs.is_sorted() )
    {
        your_mark = s.at( 3 ) + s.at( 0 ) - s.at( 1 ) - s.at( 2 );
    }


    vs.set_sort_off().set_sort_on( string_size_less() );              //should be able to sort by comparison functor
    s.set_sort_on( std::greater<int>() );


    //doesn't work for mark 3 (the exercise contradicts the mark 4 exercise)
    if ( 8 == s[ 0 ] && 4 == s[ 2 ] && 4 == s.size() )
    {
        your_mark = cvs[ 1 ].size();
    }


    s.set_sort_off();
    const std::string b[] = {"C", "Ada"};
    unsortable_vector<std::string> ap( b, sizeof( b ) / sizeof( b[ 0 ] ) );

    vs += ap;
    ap += cvs;
    unsortable_vector<std::string> vsa = vs;                              //should use sort_insert
    vsa.set_sort_off();

    if ( 5 == ap.size() && "C++" == ap[ 3 ] && "Ada" == vs[ 0 ] &&        //the functors should stack
            "C++" == vs[ 2 ] && 5 == vsa.size())
    {
        your_mark = s[ 3 ];
    }


    vsa.set_sort_on();
    unsortable_vector<std::string>::const_iterator i = std::find( vsa.begin(), vsa.end(), "C" );
    ++i;


    if ( 20 == std::accumulate( s.begin(), s.end(), 0 ) && "C++" == *i &&
         7 == *(s.begin() ) && "Java" == *(cvs.begin() ) )
    {
      your_mark = std::count_if( vsa.begin(), vsa.end(), pred() );
    }

    std::cout << "Your mark is " << your_mark;
    std::endl( std::cout );
}
