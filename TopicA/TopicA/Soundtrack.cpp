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
}


ostream &operator << (ostream & out, const soundtrack & val)
{
	out << val.getComposer() << "  " << val.getTitle() << "  " << val.getLabel() << "  "
		<< val.getCat_Num() << "  " << val.getRecorded() << "  " << val.getReleased() << endl;

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