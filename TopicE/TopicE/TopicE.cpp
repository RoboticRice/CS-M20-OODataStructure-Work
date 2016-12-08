/*********************************************************************
	CS M20 Topic E Project - Heap Project

	Martin Chetlen
**********************************************************************/


#pragma warning( disable: 4290 )  // disable warnings about the use of throw in function headers

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#include "topiceData.h"
#include "HeapPriorityQueue.h"

const double LOAD = 1.0;

bool readFile( deque<double> &data, deque<double> &error );
bool doBoxes( deque<double> & data, Heap_PriorityQueue<TopicEData> & pq, deque<TopicEData> &result, int & sum );
void displayResults( Heap_PriorityQueue<TopicEData> &pq, const deque<TopicEData> &result, int & sum );

int main( void )
{
	try {
		deque<double> data, error;
		Heap_PriorityQueue<TopicEData>pq(200);  // initialize heap with a value for capacity
		deque<TopicEData> result;

		if (!readFile(data, error))
		{
			cout << "Nothing in input file\nProgram terminating." << endl;
			exit(1);
		}

		cout << "Valid data entered is:" << endl;
		ostream_iterator<double> screen(cout, " ");
		copy(data.begin(), data.end(), screen);
		cout << endl << static_cast<int>(data.size()) << " is the total number of valid data items\n" << endl;

		if (error.size() > 0)
		{
			cout << "Invalid data entered:" << endl;
			copy(error.begin(), error.end(), screen);
			cout << endl << static_cast<int>(error.size()) << " is the total number of invalid data items\n" << endl;
		}

		int sum = 0;  // total number of items from boxes, not input file

		if (doBoxes(data, pq, result, sum))
			displayResults(pq, result, sum);
		else
			cout << "\n\nExceeded heap capacity\n" << endl;
	}
	catch (PrecondViolatedExcep &pve)
	{
		cout << pve.what() << endl;
	}

	cout << endl << "Program Over" << endl << endl;

	cin.ignore( cin.rdbuf()->in_avail() );
	cout << "Press Enter to end -->  ";
	cin.ignore();

	return 0;
}


bool readFile( deque<double> &data, deque<double> &error  )
{
	
	string fileName{ "TopicEin.txt" };
	ifstream infile( fileName );
	double d;

	while ( !infile )
	{
		cout << "Cannot open file " << fileName << endl;
		infile.clear();
		cout << "Please enter a file name for input:  " << flush;
		cin >> fileName;
		infile.open( fileName );
	} 

	while ( infile >> d )
	{
		if ( d > 0 && d <= 1.0 )
			data.push_back( d );
		else
			error.push_back( d );
	}

	infile.close();

	if ( data.size() != 0 )
		return true;
	else
		return false;
}


bool doBoxes( deque<double> & data, Heap_PriorityQueue<TopicEData> & pq, deque<TopicEData> &result, int & sum )
{
	vector<TopicEData> overload;
	int i, limit = static_cast<int>( data.size() );
	unsigned int j;
	TopicEData l6d;
	bool OK, ret{ true };

	for ( i = 0; ret && i < limit; ++i )
	{
		OK = false;
		while ( !OK )  // while the weight has not been boxed
		{
			if ( ( !pq.isEmpty() ) )  // look at the root of the pq by removing it
			{
				l6d = pq.peek();  // look at the root of the pq
				pq.remove( );  //  remove it

				if ( l6d + data.at( i ) <= LOAD )  // check to see if the box can hold the load
				{
					l6d.add( data.at( i ) );  // put the load in the box
					// since having exactly the LOAD is not likely, will get close to it
					if ( l6d >= LOAD - .01 )  // if the box has reached its limit put it somewhere else since it cannot hold any more
					{
						sum += l6d.getTotItems();  // accumulate number of items from "full" boxes
						result.push_back( l6d );
					}
					else
					{
						pq.add( l6d );  // re-insert into heap
					}
					OK = true;
				}
				else  // box cannot hold the weight
				{
					overload.push_back( l6d );  // put it into a temporary holding vector
				}
			}
			else // pq is empty - but unused boxes may be available
			{
				l6d = TopicEData( data.at( i ) );  // get the weight from the dequeue and create a new box object

				if ( l6d >= LOAD - .01 )  // if the box is already at its limit put it somewhere else since it cannot hold any more
				{
					sum += l6d.getTotItems();  // accumulate number of items from "full" boxes
					result.push_back( l6d );
				}
				else  // insert new box into the pq
				{
					if ( !pq.add( l6d ) )  // put the new box into the pq
						ret = false;  // Exceeded capacity of heap
				}
			
				OK = true;  // handled load
			}
		}

		if ( overload.size() > 0 )  // once the current weight is boxed, put back the nodes in the temporary holding vector
		{
			for  ( j = 0; j < overload.size(); ++j )
				pq.add( overload.at( j ) );

			overload.clear();  // vector is empty after each iteration
		}
	}

	return ret;
}


void displayResults( Heap_PriorityQueue<TopicEData> &pq, const deque<TopicEData> &result, int & sum )
{
	if ( result.size() > 0 )
	{
		cout << "Boxes which are considered to be full:\n";
		ostream_iterator<TopicEData> screen( cout, "\n" );
		copy( result.begin(), result.end(), screen );
	}

	cout << endl << "There are " << result.size() << " boxes considered to be full" << endl 
		 << "\nBoxes still in the heap:" << endl;

	TopicEData l6d;
	int i = 1;

	int heapTotal = 0;
	size_t total = result.size();

	while ( !pq.isEmpty()  )
	{
		l6d = pq.peek();
		pq.remove();
		cout << i << ".  " << l6d << endl;
		sum += l6d.getTotItems();
		++heapTotal;

		++i;
	}

	cout << endl << "There are " << heapTotal << " boxes in the heap\n" << endl;
	cout << total + heapTotal << " is the total number of boxes " << endl;
	cout << sum << " is the total number of items " << endl;
}

	





