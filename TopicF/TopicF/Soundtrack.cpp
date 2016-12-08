/*************************************
CS M20 Topic F Project
Rice, Sammuel
**********************************/

#include "Soundtrack.h"

bool soundtrack::operator < (const soundtrack & right) const
{
	if (this == &right)
		return false;

	string compare = label + cat_num;
	string withThis = right.label + right.cat_num;

	return ((compare < withThis) ? true : false);
}

bool soundtrack::operator > (const soundtrack & right) const
{
	if (this == &right)
		return false;

	string compare = label + cat_num;
	string withThis = right.label + right.cat_num;

	return ((compare > withThis) ? true : false);
}


bool soundtrack::operator == (const soundtrack & right) const
{
	if (this == &right)
		return true;

	string compare  = label + cat_num;
	string withThis = right.label + right.cat_num;

	return ((compare == withThis) ? true : false);
}

ostream &operator << (ostream & out, const soundtrack & val)
{
	//out << val.getComposer() << "  " << val.getTitle() << "  " << val.getLabel() << "  "
		//<< val.getCat_Num() << "  " << val.getRecorded() << "  " << val.getReleased() << endl;

	out << left << setw(24) << val.getComposer() << "  " << setw(40) << val.getTitle() << "  " << setw(16) << val.getLabel() << "  "
		<< setw(24) << val.getCat_Num() << "  " << setw(8) << val.getRecorded() << "  " << setw(4) << val.getReleased();// << endl;

	return out;

	return out;
}

istream &operator >> (istream &in, soundtrack &val)
{
	string buf;
	int iBuf;

	getline(in, buf);
	val.setComposer(buf);

	getline(in, buf);
	val.setTitle(buf);

	getline(in, buf);
	val.setLabel(buf);

	getline(in, buf);
	val.setCat_Num(buf);

	getline(in, buf);
	val.setRecorded(buf);

	in >> iBuf;
	val.setReleased(iBuf);

	in.get();  // why is this here?

	return in;
}