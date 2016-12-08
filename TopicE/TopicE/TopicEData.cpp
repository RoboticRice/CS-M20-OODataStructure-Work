/***************************************************************
	CS M20 Topic E Project - Heaps
	Fall 2014
	Martin Chetlen
*********************************************************************/



#include "TopicEdata.h"

int TopicEData::lastSeqNum = 0;

// every TopicEData object generates a sequence number, including those not put into the queue.  
TopicEData::TopicEData(double load) : seqNum{ ++lastSeqNum }, totLoad{ 0 }
{
	if ( load != 0 )
		add( load );
}


void TopicEData::add( double load )
{
	totLoad += load;
	loads.push_back( load );
}
	

ostream & operator << ( ostream & out, const TopicEData & val )
{
	if ( val.totLoad == 0 )
	{
		out << "Box " << val.seqNum << " has no load" << endl;
		return out;
	}

	out << "For box " << val.seqNum << ", Total Items:  " << val.loads.size() << ", Total Load:  " 
		<< val.totLoad << ", consisting of " << flush;

	for ( unsigned int i = 0; i < val.loads.size(); ++i )
		out << val.loads.at( i ) << " " << flush;

	return out;
}


