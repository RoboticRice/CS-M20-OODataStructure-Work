/*************************************
	CS M20 Topic D Project

	soundtrack class

	Modified from the Topic A class by the addition of != and < overloads
	
**********************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class soundtrack  
{
public:
	soundtrack(string composer = "", string title = "", string label = "", string cat_num = "", 
				string recorded = "1900", int released = 1900) 
				: 
				composer(composer), title(title), label(label), cat_num(cat_num),
				recorded(recorded), released(released) {}

	string getComposer() const { return composer; }
	string getTitle()    const { return title; }
	string getLabel()    const { return label;  }
	string getCat_Num()  const { return cat_num; }
	string getRecorded() const { return recorded; }
	int    getReleased() const { return released; }

	void setComposer( string comp )  { composer = comp; }
	void setTitle   ( string name )  { title = name; }
	void setLabel   ( string Label ) { label = Label; }
	void setCat_Num ( string cat )   { cat_num = cat; }
	void setRecorded( string rec )   { recorded = rec; }
	void setReleased( int rel )      { released = rel; }

	void clear() { 
		composer = "";
		title = "";
		label = "";
		cat_num = "";
		recorded = "1900";
		released = 1900;
	}

	bool operator == (const soundtrack & right) const;

	// Added functions for this project
	bool operator != (const soundtrack & right) const { return (!(*this == right)); }
	bool operator < (const soundtrack & right) const { return (title < right.title); }


private:
	string composer;
	string title;
	string label;
	string cat_num;
	string recorded;
	int released;
};

ostream &operator << (ostream & out, const soundtrack & val);
istream &operator >> (istream &in, soundtrack &val);

