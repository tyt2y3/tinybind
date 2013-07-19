#define TIXML_USE_STL
#include "tinybind.cpp"
#include <stdio.h>
#include <vector>
#include <list>
//
using namespace std;
//
//	svg base
	struct svg_base
	{
		const char*	id;
		const char*	style;
	};
	//
	TiXmlBinding<svg_base> const *
	GetTiXmlBinding( svg_base const &, Identity<svg_base> )
	{
		static MemberTiXmlBinding<svg_base> binding;
		if( binding.empty() ) {
			binding.AddMember( "id",	MemberAttribute(	&svg_base::id ))	->setFlags(MemberOptional);
			binding.AddMember( "style",	MemberAttribute(	&svg_base::style) )	->setFlags(MemberOptional);
		}
		return &binding;
	}
//
//	symbol
	struct symbol
	{
		svg_base	svgbase;
		//although the better way is to make symbol inherit from svgbase, it seemed impossible for tinybind.
		vector<int> 	path;
	};
	//
	TiXmlBinding<symbol> const *
	GetTiXmlBinding( symbol const &, Identity<symbol> )
	{
		static MemberTiXmlBinding<symbol> binding;
		if( binding.empty() ) {
			binding.AddMember( "svgbase",	Member(	&symbol::svgbase ))	->setFlags(MemberOptional);
			binding.AddMember( "path",	Member(	&symbol::path) )	->setFlags(MemberOptional);
		}
		return &binding;
	}
//
//
int main()
{
	symbol test1;
	test1.svgbase.id = "sym1";
	test1.svgbase.style = "test style";
	test1.path.push_back(1);
	test1.path.push_back(2);
	test1.path.push_back(3);

	TiXmlElement xmltest("symbol");
	BindToXml( &xmltest, test1 );
	printf( "print xml from a program-generated struct:\n");
	xmltest.Print( stdout, 0 );
	printf( "\n\n");

	TiXmlDocument doc;
	const char* xml1 = 
	"<symbol>"
		"<svgbase id=\"sym2\" style=\"test style\" />"
		"<path>"
			"<path>1728121</path>"
		"</path>"
	"</symbol>";
	printf( "original string: \n%s\n\n", xml1);
	doc.Parse( xml1);
	printf( "pretty print:\n");
	doc.Print( stdout, 0);

	TiXmlHandle docHandle( &doc );

	TiXmlElement* child = docHandle.FirstChild( "symbol").ToElement();
	symbol test2;
	if ( child )
	{
		BindFromXml( *child, &test2 );
		printf("\nprint content of struct from parsed xml:\n");
		printf("test2:\n"
			"\tsvgbase:\n"
			"\t\tid: %s\n"
			"\t\tstyle: %s\n"
			"\tpath:\n"
			"\t\t%d\n",
			test2.svgbase.id,
			test2.svgbase.style,
			test2.path[0]
		);
		printf( "correct vale for id: %s\n", docHandle.FirstChild( "symbol").FirstChild( "svgbase").ToElement()->Attribute( "id"));
		printf( "conclusion: tinybind has some errors\n");
	}


	return 1;
};
