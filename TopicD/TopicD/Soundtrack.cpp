/****************************************
	Topic A Project 

	CS M20

	soundtrack.cpp

**************************************/

#include "Soundtrack.h"

bool soundtrack::operator == (const soundtrack & right) const
{
	if (this == &right)
		return true;
	return title==right.title || composer==right.composer || label==right.label || cat_num==right.cat_num || recorded==right.recorded || released==right.released;
	/*
	bool bComposer = false, bTitle = false, bLabel = false, bCat_Num = false,
		bRecorded = false, bReleased = false;

	// what is the major assumption for these comparisons?
	// can these be written more efficiently?

	if (composer == "" || right.composer == "" || composer == right.composer)
		bComposer = true;

	if (bComposer && (title == "" || right.title == "" || title == right.title))
		bTitle = true;

	if (bComposer && bTitle && (label == "" || right.label == "" || label == right.label))
		bLabel = true;

	if (bComposer && bTitle && bLabel && (cat_num == "" || right.cat_num == "" || cat_num == right.cat_num))
		bCat_Num = true;

	if (bComposer && bTitle && bLabel && bCat_Num && (recorded == "1900" || right.recorded == "1900" || recorded == right.recorded) )
		bRecorded = true;

	if (bComposer && bTitle && bLabel && bCat_Num && bRecorded &&
		(released == 1900 || right.released == 1900 || released == right.released) )
		bReleased = true;

	return bComposer && bTitle && bLabel && bCat_Num && bRecorded && bReleased;
	*/
}

bool soundtrack::operator > (const soundtrack & right) const
{
	if (title > right.title)
		return true;
	return false;
}

bool soundtrack::operator >= (const soundtrack & right) const
{
	if (title >= right.title)
		return true;
	return false;
}

ostream &operator << (ostream & out, const soundtrack & val)
{
	out << left << setw(24) << val.getComposer() << "  " << setw(40) << val.getTitle() << "  " << setw(16) << val.getLabel() << "  "
		<< setw(24) << val.getCat_Num() << "  " << setw(8) << val.getRecorded() << "  " << setw(4) << val.getReleased() << endl;

	return out;
}

istream &operator >> (istream &in, soundtrack &val)
{
	string buf;

	getline(in, buf); //this doesn't remove whitepsace YET
	val.setComposer(rtrim(buf.substr(0, 24)));
	val.setTitle(rtrim(buf.substr(24, 40)));
	val.setLabel(rtrim(buf.substr(64, 16))); //24+40=64
	val.setCat_Num(rtrim(buf.substr(80, 24))); //64+16=80
	val.setRecorded(rtrim(buf.substr(104, 8))); //80+24=104
	val.setReleased(std::stoi(buf.substr(112, 4))); //104+8=112

	return in;
}

static inline std::string &rtrim(std::string &s) {
	//This function was inspired by Evan Teran @ stackOverFlow
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}