#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

#define USE_XML_BINDING
#ifdef USE_XML_BINDING
	//#define TIXML_USE_STL
	#include "../tinyxml/tinyxml.h"
	#include "../tinyxml/tinyxml.cpp"
	#include "../tinyxml/tinyxmlerror.cpp"
	#include "../tinyxml/tinyxmlparser.cpp"
	#include "../tinyxml/tinystr.cpp"	
	#include "../tinyxml/tinystr.h"
	#include "win32com.h" //to solve "error: ‘stricmp’ was not declared in this scope"

	#define TAG_NAME(X) static const char* name() { return X;}
	#define XML_BINDING bool binding( TiXmlElement* xmle, int m)
	#define ATTRIBUTE(HOLDER,ATTR_NAME) attr_fromtoxml( xmle, m, & HOLDER, ATTR_NAME)
	#define CHILD_ELEMENT(HOLDER,CHILD_STRUCT) ele_fromtoxml<CHILD_STRUCT>( xmle, m, & HOLDER)
#else
	#define TAG_NAME(X) static const char* name() { return X;}
	#define XML_BINDING bool binding() 
	#define ATTRIBUTE(HOLDER,ATTR_NAME)  
	#define CHILD_ELEMENT(HOLDER,CHILD_STRUCT)  
#endif

using namespace std;

#ifdef USE_XML_BINDING
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

	void fromxml( TiXmlElement* xmle)
	{
		if ( xmle) binding( xmle, 0);
	}
	void toxml( TiXmlElement* xmle)
	{
		if ( xmle) binding( xmle, 1);
	}
};
#else
struct xvg
{
	virtual bool binding( )=0;
};
#endif //USE_XML_BINDING

//
//svg definition
struct animate : xvg
{
	TAG_NAME("animate");

	string id;
	string onbegin;
	string onend;
	
	XML_BINDING
	{
		ATTRIBUTE( id,		"id");
		ATTRIBUTE( onbegin,	"onbegin");
		ATTRIBUTE( onend,	"onend");
	}
};

struct animation_elements : xvg
{
	TAG_NAME("animation_elements");

	string		id;
	vector<animate>			ANI;	

	XML_BINDING
	{
		ATTRIBUTE( id,	"id");
		CHILD_ELEMENT( ANI, animate);
	}
};

struct svg : xvg
{
	TAG_NAME("svg");

	string		xmlns;
	string		xmlns_xlink;
	vector<animation_elements>	ANI_ELE;

	XML_BINDING
	{
		ATTRIBUTE( xmlns,	"xmlns");
		ATTRIBUTE( xmlns_xlink,	"xmlns_xlink");
		CHILD_ELEMENT( ANI_ELE, animation_elements);
	}
};

int main()
{
#ifdef USE_XML_BINDING
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
#else
	printf("xml binding not used.\n");
#endif
	return 1;
}
