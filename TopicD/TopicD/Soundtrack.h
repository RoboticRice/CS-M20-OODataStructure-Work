/*************************************
	CS M20 Topic A Project

	soundtrack class
	
**********************************/
/*Added the #def section since it was not in the original code written by prof, which caused an error when I accidentally called this twice*/
#ifndef SOUNDTRACK
#define SOUNDTRACK

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <iomanip>

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
	bool operator > (const soundtrack & right) const; //compares released years
	bool operator >= (const soundtrack & right) const; //compares released years


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

static inline std::string &rtrim(std::string &s);

#endif