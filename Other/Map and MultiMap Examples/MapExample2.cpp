/*************************************************************
	This program was modified to use a class as the key

	strings in class

	Modified Fig.22.22 from Deitel 8-10th Editions

	Martin Chetlen

	CS M20
**********************************************************/

// Fig. 22.22: Fig22_22.cpp (8th Edition) (Fig. 15.18, page 672, in Deitel 9th Edition, Fig. 15.18, pages 689-690, 10th Edition)
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
	string label;
	string catNum;
};

// define short name for map type used in this program
typedef map< string, myClass, myClass > Mid;

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
   pairs.insert( make_pair( bern.ID(), bern ) ); // dup ignored
   pairs.insert( make_pair( barry.ID(), barry ) );
   pairs.insert( make_pair( herr.ID(), herr ) ); // dup ignored

   cout << "pairs contains:\nKey\tValue\n";
   
   // use const_iterator to walk through elements of pairs
   for ( Mid::const_iterator iter = pairs.begin();        
      iter != pairs.end(); ++iter )                       
      cout << iter->first << '\t' << iter->second << '\n';

   pairs[ herr.ID() ] = myClass( "bernard", "herrmann", "Psycho", "Varese Sarabande", "VSD-5765"  ); // use subscripting to change value for key 'b'
   pairs[ wax.ID() ] = wax;
   pairs[ korn.ID() ] = korn;
   
   cout << "\nAfter subscript operations, pairs contains:\nKey\tValue\n";
   
   // use const_iterator to walk through elements of pairs
   for ( Mid::const_iterator iter2 = pairs.begin();
      iter2 != pairs.end(); ++iter2 )           
      cout << iter2->first << '\t' << iter2->second << '\n';
                          
   cout << endl;
} // end main
