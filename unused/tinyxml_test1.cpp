#include <stdio.h>
#include <stdlib.h>
#include "svg_cpp_definition.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinyxml.cpp"
#include "../tinyxml/tinyxmlerror.cpp"
#include "../tinyxml/tinyxmlparser.cpp"
#include "../tinyxml/tinystr.cpp"	
#include "../tinyxml/tinystr.h"
#include "win32com.h" //to solve "error: ‘stricmp’ was not declared in this scope"

/*
tab width:8
*/

using namespace svg_de;
typedef const char* vgstr;

//helper functions
void attr_tostruct( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name)
{
	*attr_content = xmle->Attribute( attr_name);
}
void attr_toxml( TiXmlElement* xmle, vgstr* attr_content, const char* attr_name)
{
	xmle->SetAttribute( attr_name, *attr_content);
}

//struct _svg
	bool svg_tostruct( TiXmlElement* xmle, svg* svge)
	{
		attr_tostruct( xmle, &svge->xmlns,	"xmlns");
		attr_tostruct( xmle, &svge->xmlns_xlink,"xmlns:xlink");
	}
	bool svg_toxml( TiXmlElement* xmle, svg* svge)
	{
		*xmle = TiXmlElement( "svg");
		attr_toxml( xmle, &svge->xmlns,		"xmlns");
		attr_toxml( xmle, &svge->xmlns_xlink,	"xmlns:xlink");
	}
	void svg_print(_svg* svge){ printf("xmlns: %s, xmlns:xlink: %s\n", svge->xmlns, svge->xmlns_xlink);}

//struct _svg_common
	bool svgcommon_tostruct( TiXmlElement* xmle, common_attributes* svgc)
	{
		attr_tostruct( xmle, &svgc->id,		"id");
		attr_tostruct( xmle, &svgc->class_,	"class");
		attr_tostruct( xmle, &svgc->style,	"style");
	}
	bool svgcommon_toxml( TiXmlElement* xmle, common_attributes* svgc)
	{
		attr_toxml( xmle, &svgc->id,		"id");
		attr_toxml( xmle, &svgc->class_,	"class");
		attr_toxml( xmle, &svgc->style,		"style");
		attr_toxml( xmle, &svgc->transform,	"transform");
	}
	void svgcommon_print(common_attributes* svgc)
	{
		printf( "id: %s, ", svgc->id);
		printf( "x: %f, y: %f, w: %f, h: %f\n", 
		svgc->x, svgc->y, svgc->w, svgc->h);
	}

int main()
{
	//here we often use capital letters

	const char* xml1 = 
	"<svg  xmlns=\"http://www.w3.org/2000/svg\""
	"	xmlns:xlink=\"http://www.w3.org/1999/xlink\">"
	"	<rect x=\"10\" y=\"10\" height=\"100\" width=\"100\" style=\"stroke:#ff0000; fill: #0000ff\"/>"
	"</svg>";

	TiXmlDocument DOC;
	DOC.Parse( xml1);
	TiXmlHandle DOCH( &DOC);

	svg SVG;			//struct svg ( corresponds to the tag svg)
	svg_tostruct( DOCH.FirstChild( "svg").ToElement(), &SVG);  //convert xml element to struct svg
	svg_print( &SVG);		//print content of struct svg

	TiXmlElement XMLe("1");		//xml element
	svg_toxml( &XMLe, &SVG);	//convert struct svg into xml element
	XMLe.Print( stdout,0);		//print content of xml element
	printf("\n");

	rect RECT;
	RECT.id="rectangle1";
	RECT.x = 10; RECT.y = 12;
	svgcommon_print(&RECT);

	printf("\n");
	return 1;
}
