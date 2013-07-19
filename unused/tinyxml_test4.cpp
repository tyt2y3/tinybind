#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

//#define TIXML_USE_STL
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinyxml.cpp"
#include "../tinyxml/tinyxmlerror.cpp"
#include "../tinyxml/tinyxmlparser.cpp"
#include "../tinyxml/tinystr.cpp"	
#include "../tinyxml/tinystr.h"
#include "win32com.h" //to solve "error: ‘stricmp’ was not declared in this scope"

using namespace std;

//
//xvg definition
void attr_fromtoxml( TiXmlElement* xmle, int mode, string* attr_content, const char* attr_name)
{
	//mode: 0 stands for from xml, 1 stands for to xml
	if ( mode == 0)	//from xml
	{
		if ( xmle->Attribute( attr_name))
		{
			*attr_content = xmle->Attribute( attr_name);
		}
	}
	else if ( mode == 1) //to xml
	{
		if ( attr_content)
		{
			if ( attr_content->length()>0)
				xmle->SetAttribute( attr_name, attr_content->c_str());
		}
	}
}

template <class T>
void ele_fromtoxml( TiXmlElement* xmle, int mode, vector<T>* ANI)
{
	if ( mode==0) //from xml
	{
		for( TiXmlElement* child = xmle->FirstChildElement( T::name());
			child;
			child = child->NextSiblingElement( T::name()) )
		{
			T ani;
			ani.fromxml( child);
			ANI->push_back(ani);
		}
	}
	else if ( mode==1) //to xml
	{
		for ( int i=0;
			i<ANI->size();
			i++)
		{
			T* ani = &ANI->at(i);
			TiXmlElement Xani( ani->name());
			ani->toxml ( &Xani);
			xmle->InsertEndChild( Xani);
		}
	}
}

struct xvg //tinyXml for svg read write
{
	virtual bool binding( TiXmlElement* , int)=0;

	bool fromxml( TiXmlElement* xmle)
	{
		binding( xmle, 0);
	}
	bool toxml( TiXmlElement* xmle)
	{
		binding( xmle, 1);
	}
};

//
//svg definition
struct animate : xvg
{
	string id;
	string onbegin;
	string onend;
	
	static const char* name() { return "animate";}
	bool binding( TiXmlElement* xmle, int m) //m: 0 stands for from xml, 1 stands for to xml
	{
		attr_fromtoxml( xmle, m, &id,		"id");
		attr_fromtoxml( xmle, m, &onbegin,	"onbegin");
		attr_fromtoxml( xmle, m, &onend,	"onend");
	}
};

struct animation_elements : xvg
{
	string		id;

	vector<animate>			ANI;	

	static const char* name() { return "animation_elements";}
	bool binding( TiXmlElement* xmle, int m)
	{
		attr_fromtoxml( xmle, m, &id,	"id");

		ele_fromtoxml<animate>( xmle, m, &ANI);
	}
};

struct svg : xvg
{
	string		xmlns;
	string		xmlns_xlink;

	vector<animation_elements>	ANI_ELE;

	static const char* name() { return "svg";}
	bool binding( TiXmlElement* xmle, int m)
	{
		attr_fromtoxml( xmle, m, &xmlns,	"xmlns");
		attr_fromtoxml( xmle, m, &xmlns_xlink,	"xmlns_xlink");

		ele_fromtoxml<animation_elements>( xmle, m, &ANI_ELE);
	}
};

int main()
{
	const char* xml1=
		"<svg xmlns='http://www.w3.org/2000/svg'>"
		"<animation_elements id='element1 bla bla bla'>"
		"<animate id='ani1' onbegin='10 yo' onend='100'></animate>"
		"<animate id='ani2'></animate>"
		"<foo id='foo'></foo>"
		"<animate id='ani3'></animate>"
		"</animation_elements>"
		"</svg>";

	TiXmlDocument DOC;
	DOC.Parse( xml1);
	TiXmlHandle DOCH( &DOC);

	svg SVG;

	SVG.fromxml( DOCH.FirstChild( "svg").ToElement());

	TiXmlElement	XSVG("svg");
	SVG.toxml( &XSVG);
	XSVG.Print( stdout, 0);

	printf("\n");

	return 1;
}
