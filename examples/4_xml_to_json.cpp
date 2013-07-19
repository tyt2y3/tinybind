#include "../tinybind.h"
//compile by g++ ../tinybind.cpp 4_xml_to_json.cpp -o 4_xml_to_json

#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

#include "../tinybind_struct.h"
#include "2_svg.h"
#include "../tinybind_xml.h"
#include "2_svg.h"
#include "../tinybind_json.h"
#include "2_svg.h"
#include "../tinybind_clean.h"

int main()
{
	TiXmlDocument DOC;
	DOC.LoadFile("2_sample.svg");

	svg SVG;
	TXB_fromxmldoc( &SVG, &DOC);

	TiXmlElement XELE("svg");
	TXB_toxml( &SVG, &XELE);
	XELE.Print( stdout, 0);
	printf("\n");

	cJSON* json = cJSON_CreateObject();
	TXB_tojson ( &SVG, cJSON_CreateNode(json,"svg"));
	cJSON_Print( json, stdout);
	cJSON_Delete(json);
	printf("\n");

	return 1;
}
