#include <stdio.h>
#include <stdlib.h>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinyxml.cpp"
#include "../tinyxml/tinyxmlerror.cpp"
#include "../tinyxml/tinyxmlparser.cpp"
#include "../tinyxml/tinystr.cpp"	
#include "../tinyxml/tinystr.h"
#include "win32com.h" //to solve "error: ‘stricmp’ was not declared in this scope"
#define vgstr const char*	//meaning Svg strING
#define vgval double		//meaning Svg valUE

//the svg container tag
struct _svg			//pre _classes
{
	//attributes
	vgstr xmlns;
	vgstr xmlns_xlink;
};

//common attributes of svg
struct _svgcommon		
{
	vgstr id;
	vgstr class_;		//when names collide with C++ keywords, they are preceded by a _
	vgstr style;
	vgstr transform;
	vgval x;	vgval y;
	vgval width;	vgval height;
};

//rect
struct _rect/*:_svgcommon*/ //actual class should inherit from _svgcommon
{
	vgval rx;	vgval ry;
};

//
//

void attr_fromxml( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name)
{
	*attr_content = xmle->Attribute( attr_name);
}
void attr_fromxml_val( TiXmlElement* xmle, vgval* attr_content, const char* attr_name)
{
	xmle->Attribute( attr_name, attr_content);
}

void attr_toxml( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name)
{
	//printf( "attr_name: %s,\t\tattr_content: %s\n", attr_name, *attr_content);
	if ( *attr_content)
	{
		xmle->SetAttribute( attr_name, *attr_content);
	}
}
void attr_toxml_val( TiXmlElement* xmle, vgval* attr_content, const char* attr_name)
{
	//printf( "attr_name: %s,\t\tattr_content: %.2f\n", attr_name, *attr_content);
	if ( *attr_content)
	{
		xmle->SetDoubleAttribute( attr_name, *attr_content);
	}
}

struct _xvg //tinyXml for svg read write
{
	virtual vgstr name()=0;		//return tag name
	virtual void print()=0;		//print content
	virtual bool binding( TiXmlElement* xmle, 
		void (*bind_function)( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name), 
		void (*bind_function_val)( TiXmlElement* xmle, vgval* attr_content, const char* attr_name))=0;

	bool fromxml( TiXmlElement* xmle)
	{
		binding( xmle, &attr_fromxml, &attr_fromxml_val);
	}
	bool toxml( TiXmlElement* xmle)
	{
		binding( xmle, &attr_toxml, &attr_toxml_val);
	}
};

struct svg : _svg, _xvg
{
	vgstr name()
	{
		return ("svg");
	}
	void print()
	{
		printf("xmlns: %s, xmlns:xlink: %s\n", xmlns, xmlns_xlink);
	}
	bool binding( TiXmlElement* xmle, 
		void (*bind_function)( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name), 
		void (*bind_function_val)( TiXmlElement* xmle, vgval* attr_content, const char* attr_name))
	{
		bind_function( xmle, &xmlns,		"xmlns");
		bind_function( xmle, &xmlns_xlink,	"xmlns:xlink");
	}
};

struct svgcommon : _svgcommon, _xvg
{
	vgstr name()
	{
		return ("svgcommon");
	}
	void print()
	{
		printf("id: %s, class: %s, style: %s, transform: %s, x: %.2f, y: %.2f, width: %.2f, height: %.2f\n",
		id, class_, style, transform, x, y, width, height);
	}
	bool binding( TiXmlElement* xmle, 
		void (*bind_function)( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name), 
		void (*bind_function_val)( TiXmlElement* xmle, vgval* attr_content, const char* attr_name))
	{
		bind_function( xmle, &id,		"id");
		bind_function( xmle, &class_,		"class");
		bind_function( xmle, &style,		"style");
		bind_function( xmle, &transform,	"transform");
		//
		bind_function_val( xmle, &x,		"x");
		bind_function_val( xmle, &y,		"y");
		bind_function_val( xmle, &width,	"width");
		bind_function_val( xmle, &height,	"height");
	}
};

struct rect : _rect, svgcommon
{
	vgstr name()
	{
		return ("rect");
	}
	void print()
	{
		printf("rx: %.2f, ry: %.2f, ", rx, ry);
		svgcommon::print();
	}
	bool binding( TiXmlElement* xmle, 
		void (*bind_function)( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name), 
		void (*bind_function_val)( TiXmlElement* xmle, vgval* attr_content, const char* attr_name))
	{
		bind_function_val( xmle, &rx,	"rx");
		bind_function_val( xmle, &ry,	"ry");
		svgcommon::binding( xmle, bind_function, bind_function_val);
	}
};

int main()
{
	//here we often use capital letters

	const char* xml1 = 
	"<svg  xmlns=\"http://www.w3.org/2000/svg\""
	"	xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
	"	<rect id=\"rectangle1\" rx=\"2\" ry=\"2\" x=\"10\" y=\"20\" height=\"100\" width=\"200\" style=\"stroke:#ff0000; fill: #0000ff\"/>"
	"</svg>";

	TiXmlDocument DOC;
	DOC.Parse( xml1);
	TiXmlHandle DOCH( &DOC);

	svg SVG;			//struct svg ( corresponds to the tag svg)
	SVG.fromxml( DOCH.FirstChild( "svg").ToElement() );  //convert xml element to struct svg
	SVG.print();		//print content of struct svg

	rect RECT;
	RECT.fromxml( DOCH.FirstChild( "svg").FirstChild( "rect").ToElement() );
	RECT.print();

	TiXmlElement	XSVG(	SVG.name());
	TiXmlElement	XRECT(	RECT.name());
	SVG.	toxml(	&XSVG);
	RECT.	toxml(	&XRECT);

	XSVG.InsertEndChild( XRECT);
	XSVG.Print( stdout, 0);
	printf("\n");

	return 1;
}
