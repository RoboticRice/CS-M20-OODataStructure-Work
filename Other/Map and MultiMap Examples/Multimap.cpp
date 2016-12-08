/*************************************************************************
	Based on Program 22.19 (page 945) Deitel 8th Edition

	Extensively modified to add more features

	CS M20
********************************************************************/

// Fig. 22.21: Fig22_21.cpp  (Fig. 15.17, page 670, Deitel 9th edition, Fig. 15-17, Pages 687-688, 10th Edition)
// Standard Library class multimap test program.

#include <iostream>
#include <map> // multimap class-template definition
using namespace std;

// define short name for multimap type used in this program
typedef multimap< int, double, less< int > > Mmid;

int main()
{
   Mmid pairs; // declare the multimap pairs

   cout << "There are currently " << pairs.count( 15 )
      << " pairs with key 15 in the multimap\n";

   // insert two value_type objects in pairs
   pairs.insert( Mmid::value_type( 15, 2.7 ) );
   pairs.insert( make_pair( 15, 99.3 ) );
   
   cout << "After inserts, there are " << pairs.count( 15 )
      << " pairs with key 15\n\n";
   
   // insert five value_type objects in pairs
   pairs.insert( Mmid::value_type( 30, 111.11 ) );
   pairs.insert( make_pair( 10, 22.22 ) );
   pairs.insert( Mmid::value_type( 25, 33.333 ) );
   pairs.insert( Mmid::value_type( 20, 9.345 ) );
   pairs.insert( Mmid::value_type( 5, 77.54 ) );
   
   cout << "Multimap pairs contains:\nKey\tValue\n";
   
   cout <<  "Use const_iterator to walk through elements of pairs" << endl;
   for ( Mmid::const_iterator iter = pairs.begin();
      iter != pairs.end(); ++iter )
      cout << iter->first << '\t' << iter->second << '\n';

   cout << "\nUse range based for to walk through elements of pairs" << endl;
   for ( auto mapItem : pairs )
	   cout << mapItem.first << "\t" << mapItem.second << endl;

   cout << "\nInsert 2 more values for 15" << endl;
   pairs.insert( Mmid::value_type( 15, 2.7 ) );
   pairs.insert( Mmid::value_type( 15, 3.8 ) );

   // equal_range returns a pair of iterators.
   pair<Mmid::const_iterator, Mmid::const_iterator> p = pairs.equal_range( 15 ); 

/* p consists of two parts where each represents a pair in the multimap
   One to the beginning of the key, the other to 1 after the last occurence of the key
   Each pair of p has a key and the value it is asscoiated with
*/
   Mmid::const_iterator ci;
   cout << "\nThere are " << pairs.count( 15 ) << " values associated with the 15 key  They are:" << endl;
   for ( ci = p.first; ci != p.second; ++ci )
	   cout << ci->second << endl;

   cout << endl;

   // get the first pair associated with 15
   ci = pairs.find( 15 );

   if ( ci != pairs.end() )
   {
	   cout << "\nUse find and count to get all values associated with key 15:" << endl;
	   for ( size_t c = 0; c < pairs.count( 15 ); ++ci, ++c )
		   cout << ci->second << endl;
	   cout << endl;
   }
   else
	   cout << "\nDid not find any values associated with 15" << endl;

   cout << endl;
} // end main


