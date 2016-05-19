#include <iostream>
#include <deque>
#include <string>
#include "stringimpl.h"
#include <list>
#include <vector>
#include "stringimpl.h"
#include <iterator>

const int max = 1000;

int main()
{
    int your_mark = 1;

    char hello[] = "Hello World";
    const string_implemented_with<std::list<char>, char> hw( hello );   //should eat up the container from which it is constructed

    wchar_t t[ max + 1 ];
    for( int i = 0; i < max; ++i )
    {
        t[ i ] = L'A';
    }
    t[ max ] = L'\0';
    string_implemented_with<std::vector<wchar_t>, wchar_t> st( t );

    st.erase( 0, max / 2 ).erase( 0, max / 4 ).erase( 0, max / 8 );     //erase(firstpos, length)

    char d[] = "Dummy text";
    string_implemented_with<std::list<char>, char> ds( d );
    ds.erase( 5, 1 );

    //std::cerr << ( sizeof( st ) ) << std::endl;

    //copy(st.cbegin(), st.cend(), std::ostream_iterator<wchar_t>(std::cerr));

    //the sizeof() comparison is implementation dependent
    //since the sizeof(list) is not specified by the standard
    if ( 0 == std::char_traits<char>::length( hello ) &&
            0 == std::char_traits<wchar_t>::length( t ) &&
            0 == std::char_traits<char>::length( d ) &&
            sizeof( st ) != sizeof( hw ) &&
            'W' == hw.at( 6 ) &&
            'e' == hw.at( 1 ) &&
            'u' == ds.at( 1 ) &&
            'x' == ds.at( 7 ) &&
            L'A' == st.at( max / 10 ) &&
            max / 8 == st.length() )
    {
        your_mark = hw.length() - ds.length();
    }


    st[ 1 ] = L'B';         //operator[]
    ds[ 7 ] = 's';
    char p[] = "D my teux";
    string_implemented_with<std::list<char>, char> ps( p );
    char m[] = "Hi!";
    string_implemented_with<std::list<char>, char> ms( m );

    //std::cerr << ( st.find_first_not_of( st ) ) << std::endl;

    //copy(st.cbegin(), st.cend(), std::ostream_iterator<wchar_t>(std::cerr));

    if ( 0 == ds.find_first_not_of( hw ) &&     //find_first_not_of() member function
         0 == hw.find_first_not_of( ds ) &&
         'H' == hw[ 0 ] &&
         string_implemented_with<std::vector<wchar_t>, wchar_t>::npos == st.find_first_not_of( st ) &&      //should have npos static member field
         7 == ds.find_first_not_of( ps ) )
    {
      your_mark += hw.find_first_not_of( ms );
    }


    char hell[] = "Hell";
    string_implemented_with<std::deque<char> > hds( hell );     //should work with deque as well

    wchar_t passwd[] = L"AAAAAA";
    string_implemented_with<std::deque<wchar_t> > pds( passwd );

    if ( 1 == st.find_first_not_of( pds ) &&
         string_implemented_with<std::deque<wchar_t> >::npos == pds.find_first_not_of( st ) )
    {
      your_mark = hw.find_first_not_of( hds );
    }


    string_implemented_with<std::list<char> >::const_iterator cit =             //iterators
      std::find( hw.begin(), hw.end(), 'd' );

    string_implemented_with<std::vector<wchar_t> >::const_iterator nfit =
      std::find( st.begin(), st.end(), L'd' );

    if ( cit != hw.end() &&
         nfit == st.end() &&
         4 == your_mark )
    {
      your_mark = std::count( hw.begin(), hw.end(), 'l' ) +
                  std::count( hw.begin(), hw.end(), 'o' );
    }

    std::cout << "Your mark is " << your_mark;
    std::endl( std::cout );
}
