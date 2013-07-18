#include "../tinyxmlbind.h"

const char* xml1=
"<svg version='1.1' baseProfile='full' xmlns='http://www.w3.org/2000/svg'"
"    width='100' height='100'>"
"    <defs>"
"        <linearGradient id='grad1'>"
"            <stop offset='0%' stop-color='red'/>"
"            <stop offset='100%' stop-color='red' stop-opacity='0' />"
"        </linearGradient>"
"    </defs>"
"    <path d='M50 10  A40 40 0 1 0 90 50'"
"        stroke='url(#grad1)' stroke-width='10' fill='none'/>"
"</svg>";

#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

#include "../tinyxmlbind_partA.h"
#include "2_svg.h"
#include "../tinyxmlbind_partB.h"
#include "2_svg.h"
#include "../tinyxmlbind_partC.h"

int main()
{
	TiXmlDocument DOC;
	DOC.Parse( xml1);

	svg SVG;
	TXB_fromxmldoc( &SVG, &DOC);

	TiXmlElement XELE("svg");
	TXB_toxml( &SVG, &XELE);
	XELE.Print( stdout, 0);
	
	printf("\n");
	return 1;
}
