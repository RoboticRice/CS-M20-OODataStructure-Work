#include "Soundtrack.h"

Soundtrack::Soundtrack() : composer(""), title(""), label(""), catalog(""), recorded(""), released("")
{
	//Nothing more needs to be done
} //end default constructor

Soundtrack::Soundtrack(std::string aComposer, std::string aTitle, std::string aLabel, std::string aCatalog, std::string recordedYear, std::string releasedYear)
	: composer(aComposer), title(aTitle), label(aLabel), catalog(aCatalog), recorded(recordedYear), released(releasedYear) 
{
	//Nothing more needs to be done
} //end constructor

void Soundtrack::setComposer(std::string aComposer)
{
	composer = aComposer;
} //end setComposer

void Soundtrack::setTitle(std::string aTitle)
{
	title = aTitle;
} //end setTitle

void Soundtrack::setLabel(std::string aLabel)
{
	label = aLabel;
} //end setLabel

void Soundtrack::setCatalog(std::string aCatalog)
{
	catalog = aCatalog;
} //end setCatalog

void Soundtrack::setRecorded(std::string recordedYear)
{
	recorded = recordedYear;
} //end setRecorded

void Soundtrack::setReleased(std::string releasedYear)
{
	released = releasedYear;
} //end setReleased

void Soundtrack::clear()
{
	composer = "";
	title = "";
	label = "";
	catalog = "";
	recorded = "";
	released = "";
} //end clear

std::string Soundtrack::print() const
{
	return composer + ", " + title + ", " + label + ", " + catalog + ", " + recorded + ", " + released + "."; 
} //end print

std::string Soundtrack::getComposer() const
{
	return composer;
} //end getComposer

std::string Soundtrack::getTitle() const
{
	return title;
} //end getTitle

std::string Soundtrack::getLabel() const
{
	return label;
} //end getLabel

std::string Soundtrack::getCatalog() const
{
	return catalog;
} //end getCatalog

std::string Soundtrack::getRecorded() const
{
	return recorded;
} //end getRecorded

std::string Soundtrack::getReleased() const
{
	return released;
} //end getReleased