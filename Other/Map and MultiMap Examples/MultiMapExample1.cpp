/*************************************************************
	Uses multimap

	Cannot use [] operator as multimap can have multiple values associated with a single key

	CS M20

	Martin Chetlen
**********************************************************/

// Fig. 22.22: Fig22_22.cpp  (Fig, 15.17, page 670, in Detel 9th Edition, Fig. 15.17, pages 687-688, 10th Edition)
// Standard Library class map test program.
#include <iostream>
#include <map> // map class-template definition
#include <string>
using namespace std;

class myClass
{
	friend ostream & operator << ( ostream & out, const myClass & val ) 
	   { out << val.composer_first << "  " << val.composer_last << "  " << val.film 
	   << "  " << val.label << "  " << val.catNum << endl; return out; }

public:
	myClass( const string & first = "", const string &last = "", const string &film = "", 
		     const string & l = "", const string &cat = "" ) 
		  : composer_first( first ), composer_last( last ), film( film ), label( l ), catNum( cat )
	        {}

	bool operator () ( const string & str1, const string & str2 ) const
	{ return str1 < str2 ; }

	string ID () const
	{
		return label + catNum;
	}



private:
	string composer_first;
	string composer_last;
	string film;
	const string label;
	const string catNum;
};

// define short name for map type used in this program
typedef multimap< string, myClass, myClass > Mid;

int main()
{
   Mid pairs;

   myClass bern( "Elmer", "Bernstein", "Great Escape", "Varese Sarabande", "VCL-0804-1029-2" );
   myClass herr ( "Bernard", "Herrmann", "Jane Eyre", "Marco Polo", "8.223535" );
   myClass north ( "Alex", "North", "Cleopatra", "Varese Sarabande", "3020662242" );
   myClass newman ( "Alfred", "Newman", "How The West Was Won", "Rhino", "RZ72458" );
   myClass miklos ( "Miklos", "Rozsa", "Ben-Hur", "Rhino", "R272197" );
   myClass barry ( "John", "Barry", "Goldfinger", "EMI", "72435-80891-2-7" );
   myClass wax( "Franz", "Waxman", "Story of Ruth", "Varese Sarabande", "VCL 08031024" );
   myClass korn( "Erich", "Korngold", "Sea Hawk", "Naxos", "8.570110-11" );


   // insert eight value_type objects in pairs
   pairs.insert( make_pair( bern.ID(), bern ) );
   pairs.insert( make_pair( herr.ID(), herr ) );
   pairs.insert( make_pair( north.ID(), north ) );
   pairs.insert( make_pair( newman.ID(), newman ) );
   pairs.insert( make_pair( miklos.ID(), miklos ) );
   pairs.insert( make_pair( bern.ID(), bern ) ); // duplicate
   pairs.insert( make_pair( barry.ID(), barry ) );
   pairs.insert( make_pair( herr.ID(), herr ) );   // duplicate

   cout << "pairs contains:\nKey\tValue\n";
   
   // use const_iterator to walk through elements of pairs
   for ( Mid::const_iterator iter = pairs.begin();        
      iter != pairs.end(); ++iter )                       
      cout << iter->first << '\t' << iter->second << '\n';

// equal range returns an iterator to the start of a key and another to one after the last of that key
// count (not used here) returns the number of items associated with a single key
	typedef pair<Mid::const_iterator, Mid::const_iterator> IMid;
	IMid const_iter = pairs.equal_range( bern.ID() );

	Mid::const_iterator out_iter;

	cout << "Output all bern ID\n";

// const_iter.first is the start iterator returned by equal_range to the first value associated with the key
// const_iter.second is the iterator returned by equal_range that points to the item one after the key.
// Followed example in Stroustrop, "Programming Principles and Practice in C++", pages 824 - 825
//  Also Dietel, "C++ How to Program", 7th Edition, pages 944 - 947 [pages 665 - 667 9th edition] (multiset - equal_range, count, find) and
//     pages 948 - 950 [pages 669 - 671 9th edition] (multimap)
	for ( out_iter = const_iter.first; out_iter != const_iter.second; ++out_iter )
		cout << out_iter->first << "   " << out_iter->second << endl;
                          
   cout << endl;

   Mid::const_iterator iter;
   iter = pairs.find( herr.ID() );
   if ( iter != pairs.end() )
   {
	   cout << "\nFound:\n" << iter->first << "  " << iter->second << endl;
	   ++iter;
	   cout << "\nFound:\n" << iter->first << "  " << iter->second << endl;
	   ++iter;
	   cout << "\nFound:\n" << iter->first << "  " << iter->second << endl;
   }
   else
	   cout << "\nNot found first find" << endl;



} // end main

