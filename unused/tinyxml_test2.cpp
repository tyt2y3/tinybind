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

namespace svg_de
{
//helper functions
void attr_tostruct( TiXmlElement* xmle, const char* attr_content, const char* attr_name)
{
	*attr_content = xmle->Attribute( attr_name);
}
void attr_toxml( TiXmlElement* xmle, const char* attr_content, const char* attr_name)
{
	xmle->SetAttribute( attr_name, *attr_content);
}

void svg::print()
{
	printf("xmlns: %s, xmlns:xlink: %s\n", xmlns, xmlns_xlink);
}

int main()
{
	svg SVG;
	SVG.xmlns="hello";
	SVG.xmlns_xlink="world";
	SVG.print();
}
}

//this does not work anymore
//just for experimenting
