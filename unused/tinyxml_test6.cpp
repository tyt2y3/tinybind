#define USE_XML_BINDING
#include "tinyxml_test6.h"

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
struct desc : xvg
{
	TAG_NAME("desc");

	string class_;
	
	XML_BINDING
	{	
		ATTRIBUTE( class_,	"class");
	}
};

struct animation_elements
{
	//this is not a tag, just a group of elements
	vector<animate>			ANI;

	XML_BINDING
	{
		CHILD_ELEMENT( ANI, animate);
	}
};
struct descriptive_elements
{
	//this is not a tag, just a group of elements
	vector<desc>			DES;

	XML_BINDING
	{
		CHILD_ELEMENT( DES, desc);
	}
};

struct svg : xvg, //content elements
		animation_elements,
		descriptive_elements
{
	TAG_NAME("svg");

	XML_BINDING
	{
		INHERIT(animation_elements);
		INHERIT(descriptive_elements);
	}
};

int main()
{
	const char* xml1=
	"<svg id='hello'>"
	"<animate id='ani1' onbegin='hello' onend='bye'></animate>"
	"<desc class='classA'></desc>"
	"<animate id='ani2' onbegin='10'></animate>"
	"<desc class='classB'></desc>"
	"<animate id='ani3' ></animate>"
	"</svg>";

	TiXmlDocument DOC;
	DOC.Parse( xml1);
	TiXmlHandle DOCH( &DOC);

	svg SVG;

	SVG.fromxml( DOCH.FirstChild( svg::name()).ToElement());

	TiXmlElement	XSVG( svg::name());
	SVG.toxml( &XSVG);
	XSVG.Print( stdout, 0);

	printf("\n");

	return 1;
}
