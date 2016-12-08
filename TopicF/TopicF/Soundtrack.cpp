/*************************************************************************
	AVL Tree Project - Topic F

	FilmScore.cpp

	This class will hold the data read in from the input file

	The ID of each object is the combination of the label and the catalog number
*******************************************************************************/

#include "Soundtrack.h"


ostream & operator << ( ostream & out, const FilmScore fm )
{
	out << fm.getComposer() << "  " << fm.getFilm() << "  " << fm.getLabel() << "  "
		 << fm.getCatNum() << "  " << fm.getRecordYr() << "  " << fm.getReleaseYr();

	return out;
}



