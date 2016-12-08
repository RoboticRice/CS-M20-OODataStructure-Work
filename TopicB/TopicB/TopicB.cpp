/********************************
	Topic B Project Client File

	CS M20  

	Stack/queue project - Balanced symbols

	Both basic and extra credit
*********************************/

#pragma warning( disable: 4290 )  // disable warnings about the use of throw in function headers


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "LinkedQueue.h"
#include "LinkedStack.h"

void getInput( LinkedQueue<string> &lq );
bool validExp( const string &exp );

int main()
{
	cout << "Create queue object lq\n" << endl;
	LinkedQueue<string> lq;

	cout << "Get the file input\n" << endl;

	getInput( lq );
	
	cout << "\n\nAfter getting the file nput,  test other functions*******\nCreate lq1, a copy of the queue" << endl;
	LinkedQueue<string> lq1 = lq;
	cout << "\nDisplay the contents of the copy queue lq1:" << endl;
	while( !( lq1.isEmpty() ) )
	{
		cout << lq1.peekFront() << endl;
		lq1.dequeue();
	}

	cout << "\nAttempt to peek the now empty copy queue lq1:" << endl;
	try
	{
		lq1.peekFront();
	}
	catch( PrecondViolatedExcept &exc )
	{
		cout << exc.what();
	}
	
	cout << "\n\nAssign lq to lq1 and then display lq1:" << endl;
	lq1 = lq;

	while( !( lq1.isEmpty() ) )
	{
		cout << lq1.peekFront() << endl;
		lq1.dequeue();
	}

	cout << "\nPut the first string in lq into a stack of chars, ls1" << endl;
	LinkedStack<char> ls1;
	string exp = lq.peekFront();
	for( size_t i = 0; i < exp.size(); ++i )
		ls1.push( exp[ i ] );

	cout << "\nCreate a copy, ls2, of the stack and display the copy:" << endl;
	LinkedStack<char> ls2 = ls1;
	while ( !( ls2.isEmpty() ) )
	{
		cout << ls2.peek() << " ";
		ls2.pop();
	}

	cout << "\n\nAssign the first stack, ls1, to the second stack, ls2, and then display the second stack:" << endl;
	ls2 = ls1;
	while ( !( ls2.isEmpty() ) )
	{
		cout << ls2.peek() << " ";
		ls2.pop();
	}

	cout << endl << endl;

	cout << "\n\nDo the expression checking:\n" << endl;

	while( !( lq.isEmpty() ) )
	{
		cout << "\n\nThe next string is:   " << lq.peekFront() << "  ";
		if ( validExp( lq.peekFront() ) )
			cout << " is ";
		else
			cout << " is NOT ";

		cout << " a correct expression" << endl;

		lq.dequeue();
	}

	cout << "\n\nProgram Over\n" << endl;

	cout << "Press Enter to end -->  ";
	cin.ignore();

	return 0;
}

void getInput( LinkedQueue<string> &lq )
{
	ifstream inFile;
	string name;

	do
	{
		cout << "Enter input file name:  ";
		cin >> name;
		inFile.clear();
		inFile.open( name.c_str() );

		if ( !inFile )
		{
			cout << name << " cannot be opened.\n";
		}
	} while ( !inFile );

	cin.ignore();

	while ( getline( inFile, name ) )
		lq.enqueue( name );
}

bool validExp( const string &exp )
{
// #define EXTRA_CREDIT

	LinkedStack<char> ls;

	const string open  = "([{";
	const string close = ")]}";
	const string other = "\"'";

	char val;
	size_t index;

	bool OK = true;

#ifdef EXTRA_CREDIT
	bool next{ true };
#endif

	for (size_t pos{ 0 }; OK && pos < exp.size(); ++pos)
	{
#ifdef EXTRA_CREDIT
		if( !next )
		{
			next = true;
			continue;
		}

		if ( exp[ pos ] == '\\' )
			next = false;
#endif

		if( open.find( exp[ pos ] ) != string::npos )
			ls.push( exp[ pos ] );

		else if ( ( index = close.find( exp[ pos ] ) ) != string::npos )
		{
			try 
			{
				val = ls.peek();
				if ( val == open[ index ] )  // does the token on the stack match the cognate open token
					ls.pop();
				else
					OK = false;
			}
			catch( PrecondViolatedExcept & )
			{
				OK = false;
			}
		}

		else if ( other.find( exp[ pos ] ) != string::npos )  // " or '
		{
			try 
			{
				val = ls.peek();
				if ( val == exp[ pos ] )
					ls.pop();
				else
					ls.push( exp[ pos ] );
			}
			catch( PrecondViolatedExcept & )
			{
				ls.push( exp[ pos ] );
			}
		}
	}

	if ( !( ls.isEmpty() ) )  // should be no leftover tokens
		OK = false;

#ifdef EXTRA_CREDIT
#undef EXTRA_CREDIT
#endif

	return OK;
}