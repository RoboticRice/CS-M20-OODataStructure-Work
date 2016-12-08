/**************************************************************
Topic F Project - CS M20

AVL Tree

Client File
****************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

#include "AVL.h"
#include "Soundtrack.h"

void display( FilmScore fs );  // Used as functon pointers
void all1950( FilmScore fs );

bool getInput( AvlTree<FilmScore> &av );



int main()
{
	AvlTree<FilmScore> av;

	cout << "Create and populate AVL tree\n" << endl;

	if ( getInput( av ) )
	{
		cout << "\n************************************ Press Enter to continue  -->  ";
		cin.ignore();

		cout << "Get item with key \"FSMBox 03 Disc 8\":" << endl;  // <-- Look at this as there were no records

		FilmScore fs1{ "FSM", "Box 03 Disc 8" }, FS;

		if ( av.AVL_Retrieve( fs1, FS ) )
			cout << FS << endl;
		else
			cout << "\nNo items found with key \"FSMBox 03 Disc 8\"\n" << endl; 

		cout << "\n\nGet item with key \"FSMBox 07 Disc 8\":" << endl ;

		FilmScore fs2{ "FSM", "Box 07 Disc 8" };

		if ( av.AVL_Retrieve( fs2, FS ) )
			cout << FS << endl;
		else
			cout << "\nNo items found with key \"FSMBox 07 Disc 8\"\n" << endl; 

		cout << "\n************************************ Press Enter to continue  -->  ";
		cin.ignore();

		cout << "Listing of all items in the tree: (There are " << av.AVL_Count()
				<< " items in the table) \n" << endl;

		av.AVL_Traverse( display );

		cout << "\n************************************ Press Enter to continue  -->  ";
		cin.ignore();

		cout << "\n\nList all soundtracks recorded in the 1950s:\n" << endl;
		av.AVL_Traverse( all1950 );
		cout << "\n************************************ Press Enter to continue  -->  ";
		cin.ignore();


		cout << "\nDelete all items with key \"FSM V8N11\":" << endl;

		FilmScore fs3{ "FSM", "V8N11" };

		if ( av.AVL_Retrieve( fs3, FS ) )
		{
		
			cout << "\n" << FS << endl;
			av.AVL_Delete( fs3 );
			cout <<  "has been deleted" << endl;
		}
		else
			cout << "NO items for \"FSM V8N11\"" << endl;

		cout << "\nAgain delete all items with key \"FSM V8N11\":" << endl;

		if ( av.AVL_Retrieve( fs3, FS ) )
		{
		
			cout << "\n" << FS << endl;
			av.AVL_Delete( fs3 );
			cout <<  "has been deleted" << endl;
		}
		else
			cout << "NO items for \"FSM V8N11\"" << endl;

		cout << "\n************************************ Press Enter to continue  -->  ";
		cin.ignore();

		cout << "Listing of all items in the tree: (There are " << av.AVL_Count()
				<< " items in the table) \n" << endl;

		av.AVL_Traverse( display );
	}

	cout << "\nProgram Ending\n\nPress Enter to end -->  ";
	cin.ignore();

	return 0;
}

void delTrailBlanks( string & str )
{
	int pos = str.length() - 1;

	for ( ; pos >= 0 && isspace( str[ pos ] ); --pos )
		;

	if ( pos < 0 )
		str = "";
	else
		if ( pos != str.length() - 1 )
			str.erase( pos + 1 );
}

bool getInput( AvlTree<FilmScore> &av )
{
	// File layout of input file
	const int FIELDS[] = { 24, 40, 16, 24, 8, 4 };
	const int NUM_FIELDS = 6;

	ifstream in( "Topic F Soundtrack.txt" );

	if ( !in )
	{
		cout << "Cannot open soundtrack.txt" << endl;
		return false;
	}

	string line, data[ 6 ];

	int strPos, // position in input string line
		dataFieldPos; // element of data array - input to FilmScore class AND element of FIELDS array

	unsigned int year;

	char *remain;  // for strtol

	FilmScore FS, fs;

	while ( !in.eof() )
	{
		getline( in, line );

		for ( dataFieldPos = strPos = 0; 
// starting position in line + (offset - 1) must be less than line length && more record fields to be processed
			  strPos + FIELDS[ dataFieldPos ] - 1 < static_cast<int>( line.length() ) && dataFieldPos < NUM_FIELDS; 
			  strPos += FIELDS[ dataFieldPos++ ] )  // move strPos to start of next field
		{
			data[ dataFieldPos ] = line.substr( strPos, FIELDS[ dataFieldPos ] );
			delTrailBlanks( data[ dataFieldPos ] );
		}
		
		if ( dataFieldPos != NUM_FIELDS )
		{  // record processing stopped before all fields were processed
			cout << endl << line << " has a problem.  Input record is ignored" << endl;
			continue;  // go on to next input record
		}

		year = strtol( data[ 5 ].c_str(), &remain, 0 );

		if ( strlen( remain ) != 0 )
			cout << endl << data[ 5 ] << " is not a numeric value.  This input ignored:\n"
			     << line << endl; 
		else
		{
			FS = FilmScore( data[ 0 ], data[ 1 ], data[ 2 ], data[ 3 ], 
			           data[ 4 ], year ); 

			if ( !( av.AVL_Retrieve( FS, fs ) ) )
				av.AVL_Insert( FS );
			else
				cout << FS << " is a duplicate" << endl;
		}		
	}

	in.close();

	if ( av.AVL_Count() == 0 )
		return false;
	else
		return true;
}

void display( FilmScore fs )
{
	static int count = 0;
	
	cout << fs << endl;

	if ( ++count % 75 == 0 )
	{
		cout << "\n************************************ Press Enter to continue -->  ";
		cin.ignore();
	}
}

void all1950( FilmScore fs )
{
	if ( fs.getRecordYr().find( "195" ) != string::npos || fs.getRecordYr().find( "/5" ) != string::npos )
		cout << fs << endl;
}


