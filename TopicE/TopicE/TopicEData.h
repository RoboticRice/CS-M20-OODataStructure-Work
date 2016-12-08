#ifndef _TOPIC_E_DATA
#define _TOPIC_E_DATA

#include <iostream>
#include <fstream>
#include <vector>

class topicEData //aka, BOX
{
private:
	double totLoad;
	int seqNum;
	std::vector<double> loads;
public:
	topicEData();
	topicEData(int numbered); 
	//By preventing the use of the default constructor, the client can not create boxes without numbers.
	//^Well, that's what I WAS going to do, until it caused an error. See line 66 of ArrayMaxHeap.h
	//this line creates error C3931 '_Elem': cannot call a function that has restriction specifiers that are incompatible with the ambient context when no default constructor
	
	void setNumber(int number);
	void add(double amount);
	double getTotal() const;
	int getNumber() const;
	int getNumLoads() const;
	std::vector<double> getAllLoads() const;

	bool topicEData::operator == (const topicEData & right) const;
	bool topicEData::operator <= (const topicEData & right) const;
	bool topicEData::operator >  (const topicEData & right) const;
};

std::ostream &operator << (std::ostream & out, const topicEData & val);
std::istream &operator >> (std::istream &in, topicEData &val);

#endif