#include "TopicEData.h"

topicEData::topicEData()
{
	seqNum = 0;
	totLoad = 0;
}

topicEData::topicEData(int numbered)
{
	seqNum = numbered;
	totLoad = 0;
}

void topicEData::setNumber(int number)
{
	seqNum = number;
}

void topicEData::add(double amount)
{
	loads.push_back(amount);
	totLoad += amount;
}

double topicEData::getTotal() const
{
	return totLoad;
}

int topicEData::getNumber() const
{
	return seqNum;
}

int topicEData::getNumLoads() const
{
	return (int)loads.size();
}

std::vector<double> topicEData::getAllLoads() const
{
	return loads;
}

bool topicEData::operator == (const topicEData & right) const
{
	if (totLoad == right.totLoad)
		return true;
	return false;
}

bool topicEData::operator <= (const topicEData & right) const
{
	if (totLoad <= right.totLoad)
		return true;
	return false;
}

bool topicEData::operator > (const topicEData & right) const
{
	if (totLoad > right.totLoad)
		return true;
	return false;
}

std::ostream &operator << (std::ostream & out, const topicEData & val)
{
	out << "Box#: " << val.getNumber() << ". Total items: " << val.getNumLoads() << ", Total load: " << val.getTotal() << ", consisting of";
	for (int i = 0; i < val.getNumLoads(); i++)
		out << " " << val.getAllLoads().at(i);

	return out;
}

std::istream &operator >> (std::istream &in, topicEData &val)
{
	double iBuf;

	//getline(in, buf);
	//val.setComposer(buf);

	in >> iBuf;
	//std::cout << "DB::iBuf::" << iBuf << std::endl;
	val.add(iBuf);

	in.get();  // why is this here?

	return in;
}