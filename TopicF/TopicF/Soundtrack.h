/*************************************************************************
	CS M20

	AVL Tree Project - Topic F

	FilmScore.h

	This class will hold the data read in from the input file

	The ID of each object is the combination of the label and the catalog number
	Because this constitutes the ID, these objects are const.
	As a result, these values are required therefore there is no default constructor
*******************************************************************************/


#include <iostream>
#include <string>

using namespace std;

class FilmScore
{
public:
	FilmScore() : composer{ "" }, film{ "" }, label{ " " }, catNum{ " " }, recordYr{ "" },
		releaseYr{ 1900 } {}
	FilmScore(string label, string catNum) : label{ label }, catNum{ catNum } {}
	FilmScore( string & composer, string & film, string & label, string & catNum, string & recordYr,
		       unsigned int & releaseYr ) 
		: composer{ composer }, film{ film }, label{ label }, catNum{ catNum }, recordYr{ recordYr },
		  releaseYr{ releaseYr } {}

	string ID() const { return label + catNum; }  // extract the ID

	string getComposer() const { return composer; }
	string getFilm() const { return film; }
	string getLabel() const { return label; }
	string getCatNum() const { return catNum; }
	string getRecordYr() const { return recordYr; }
	unsigned int getReleaseYr() const { return releaseYr; }

	void setComposer( string & comp ) { composer = comp; }
	void setFilm( string & f ) { film = f; }
	void setRecordYr( string & ryr ) { recordYr = ryr; }
	void setReleaseYr( unsigned int ry ) { releaseYr = ry; }

	bool operator == ( const FilmScore & right ) const { return ( ID() == right.ID() ); }
	bool operator != ( const FilmScore & right ) const { return ( ID() != right.ID() ); }
	bool operator > ( const FilmScore & right ) const { return ( ID() > right.ID() ); }
	bool operator < ( const FilmScore & right ) const { return ( ID() < right.ID() ); }

private:
	string composer, film, recordYr;
	unsigned int releaseYr;
	string label, catNum;
};

ostream & operator << ( ostream & out, const FilmScore fm );