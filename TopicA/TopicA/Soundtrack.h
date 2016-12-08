/** Data Type for the list
@file Soundtrack.h */

#ifndef SOUNDTRACK_
#define SOUNDTRACK_

#include <string>

class Soundtrack
{
private:
	std::string composer, title, label, catalog, recorded, released;
public:
	Soundtrack();
	Soundtrack(std::string aComposer, std::string aTitle, std::string aLabel, std::string aCatalog, std::string recordedYear, std::string releasedYear);

	void setComposer(std::string aComposer);
	void setTitle(std::string aTitle);
	void setLabel(std::string aLabel);
	void setCatalog(std::string aCatalog);
	void setRecorded(std::string recordedYear);
	void setReleased(std::string releasedYear);
	void clear();

	std::string print() const;
	std::string getComposer() const;
	std::string getTitle() const;
	std::string getLabel() const;
	std::string getCatalog() const;
	std::string getRecorded() const;
	std::string getReleased() const;
}; //end Soundtrack

#endif