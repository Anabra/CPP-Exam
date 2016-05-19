#include <iostream>
#include <set>
#include "ffvec.h"
#include <vector>
#include <cstring>
#include "ffvec.h"
#include <string>

const unsigned int max = 1000;

int main()
{
    int your_mark = 1;

    const int a[] = {4, 8, 3, 1, 9};
    const std::string s[] = { "Hello", "World" };

    full_fledged_vector<int> vi( a, sizeof( a ) / sizeof( a[ 0 ] ) );
    full_fledged_vector<std::string> vs( s, sizeof( s ) / sizeof( s[ 0 ] ) );
    vs.push_back( "!" );
    vi.push_back( 7 );

    full_fledged_vector<int> t;
    for( unsigned int i = 0; i < max; ++i )
    {
        t.push_back( i % 5 );
    }

    const full_fledged_vector<int> tsv = t.subvec( 1, max / 2 );
    const full_fledged_vector<std::string> svs = vs.subvec( 1, 1 );

    if ( 3 == vs.size() &&
            "!" == vs.at( 2 ) &&
            5 == vs.at( 0 ).length() &&
            9 == vi.at( 4 ) &&
            7 == vi.at( 5 ) &&
            max / 2 == tsv.size() &&
            1 == svs.size() &&
            s[ 1 ] == svs.at( 0 ) &&
            2 == tsv.at( 1 ) &&
            max == t.size() &&
            1 == svs.subvec( 0, 1 ).size() )
    {
        your_mark = t.at( max - 3 );
    }


    //push_back
    full_fledged_vector<int> nf;
    nf.push_back( 404 );

    full_fledged_vector<int> p = tsv;
    p.append( a, sizeof( a ) / sizeof( a[ 0 ] ) );

    vs.append( s, sizeof( s ) / sizeof( s[ 0 ] ) );

    //find_first_of
    if ( full_fledged_vector<int>::npos == t.find_first_of( nf ) &&
            1 == t.find_first_of( vi ) &&
            0 == vi.find_first_of( t ) &&
            0 == tsv.find_first_of( t ) &&
            p[ max / 2 ] == a[ 0 ] &&
            5 == vs.size() &&
            vs[ 0 ] == vs[ 3 ] &&
            vs[ 1 ] == vs[ 4 ] )
    {
        your_mark = vi[ your_mark ];
    }


    vs += svs;  //append
    nf += vi;

    std::set<int> si;
    si.insert( 8 );
    si.insert( 2 );

    //should delete the remaining elements
    //basically copy and erase
    vi.replace( vi.begin() + 1, vi.begin() + 4, si.begin(), si.end() );

    std::vector<int> vec( si.begin(), si.end() );
    p.replace( p.begin(), p.end(), vec.begin(), vec.end() );

    if ( 7 == nf.size() &&
            nf[ 3 ] == a[ 2 ] &&
            6 == vs.size() &&
            3 == std::count( vs.begin(), vs.end(), s[ 1 ] ) &&
            5 == vi.size() &&
            2 == vi[ 1 ] )
    {
        your_mark = p.size() + p[ 0 ];
    }


    //should work for strings as well
    const wchar_t ws[] = L"C++ is cool!";
    full_fledged_vector<char> c( s[ 0 ].c_str(), s[ 0 ].length() );
    full_fledged_vector<wchar_t> cpp( ws, wcslen( ws ) );

    //if the type is a CharT it should be converted to basic_string
    std::string cc = c;
    std::wstring cppc = cpp;

    if ( cpp[ 1 ] == ws[ 1 ] &&
         c.size() == s[ 0 ].length() &&
         cppc.length() == cpp.size() &&
         cppc[ 6 ] == cpp[ 6 ] )
    {
      your_mark = cc.size();
    }

    std::cout << "Your mark is " << your_mark;
    std::endl( std::cout );
}
