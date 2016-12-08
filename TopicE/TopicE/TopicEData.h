/***************************************************************
	CS M20 Topic E Project - Heaps
	Fall 2014
	Martin Chetlen
*********************************************************************/


#include<iostream>
#include <vector>

using namespace std;

class TopicEData
{
	friend ostream & operator << ( ostream & out, const TopicEData & val );

public:
	TopicEData( double load = 0 );
	void add( double load );
	double operator + ( double val ) const { return totLoad + val; };

	bool operator < ( double val ) const { return totLoad < val; };
	bool operator == ( double val ) const { return totLoad == val; };
	bool operator <= ( double val ) const { return ( totLoad <= val ); };

	bool operator < ( const TopicEData & val ) const { return totLoad < val.totLoad; };
	bool operator == ( const TopicEData & val ) const { return totLoad == val.totLoad; };
	bool operator <= ( const TopicEData & val ) const { return totLoad <= val.totLoad; };
	bool operator > ( const TopicEData & val ) const { return totLoad > val.totLoad; };
	bool operator >= ( const TopicEData & val ) const { return totLoad >= val.totLoad; };

	double getTotLoad( void ) const { return totLoad; }
	double getSeqNum( void ) const { return seqNum; }
	int getTotItems( void ) const {return static_cast<int>( loads.size() ); }

private:
	double totLoad;
	int seqNum;
	vector<double> loads;
	static int lastSeqNum;
};