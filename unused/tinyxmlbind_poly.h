#ifndef TINY_XML_BIND
#define TINY_XML_BIND

//a version utilizing polymorphism
#ifdef USE_TINY_XML_BIND
	#include <string>
	#include <vector>
	#include <stdio.h>
	#include <stdlib.h>
	//#define TIXML_USE_STL
	#include "../tinyxml/tinystr.h"
	#include "../tinyxml/tinystr.cpp"
	#include "../tinyxml/tinyxml.h"
	#include "../tinyxml/tinyxml.cpp"
	#include "../tinyxml/tinyxmlerror.cpp"
	#include "../tinyxml/tinyxmlparser.cpp"
	#ifndef WIN32 
		//to solve "error: ‘stricmp’ was not declared in this scope"
		#define stricmp strcasecmp 
		#define strnicmp strncasecmp 
	#endif

	#define TXB_BIND(NAME) static const char* TXB_tagname() { return NAME;}; \
			bool TXB_binding( TiXmlElement* xmle, bool m)
	#define TXB_ATTR(HOLDER) TXB_attr_bind( xmle, m, & HOLDER, #HOLDER)
	#define TXB_TEXT(HOLDER) TXB_text_bind( xmle, m, & HOLDER)
	#define TXB_ATTR_NAME(HOLDER,NAME) TXB_attr_bind( xmle, m, & HOLDER, NAME)
	#define TXB_CHILD(HOLDER,CHILD_STRUCT) TXB_ele_bind<CHILD_STRUCT>( xmle, m, & HOLDER)
	#define TXB_INHERIT(X) X ::TXB_binding( xmle,m)
#else
	#define TXB_BIND(NAME) bool TXB_binding() 
	#define TXB_ATTR(HOLDER)
	#define TXB_TEXT(HOLDER)  
	#define TXB_ATTR_NAME(HOLDER,NAME)  
	#define TXB_CHILD(HOLDER,CHILD_STRUCT)  
	#define TXB_INHERIT(X)  
#endif

#ifdef USE_TINY_XML_BIND
void TXB_attr_bind( TiXmlElement* xmle, bool from, std::string* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = xmle->Attribute( attr_name);
	}
	else //to xml
	{
		if ( attr_content->length()>0)
			xmle->SetAttribute( attr_name, attr_content->c_str());
	}
}
void TXB_attr_bind( TiXmlElement* xmle, bool from, int* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = strtol(xmle->Attribute(attr_name),0,0);
	}
	else //to xml
	{
		char buf[100];
		snprintf(buf,100,"%d",*attr_content);
		xmle->SetAttribute( attr_name, buf);
	}
}
void TXB_attr_bind( TiXmlElement* xmle, bool from, double* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = strtod(xmle->Attribute(attr_name),0);
	}
	else //to xml
	{
		char buf[100];
		snprintf(buf,100,"%f",*attr_content);
		xmle->SetAttribute( attr_name, buf);
	}
}
void TXB_attr_bind( TiXmlElement* xmle, bool from, float* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = strtod(xmle->Attribute(attr_name),0);
	}
	else //to xml
	{
		char buf[100];
		snprintf(buf,100,"%f",*attr_content);
		xmle->SetAttribute( attr_name, buf);
	}
}

void TXB_text_bind( TiXmlElement* xmle, bool from, std::string* attr_content)
{
	if ( from) //from xml
	{
		const TiXmlNode* child = xmle->FirstChild();
		if ( child ) {
			const TiXmlText* childText = child->ToText();
			if ( childText ) {
				*attr_content = childText->Value();
			}
		}
	}
	else //to xml
	{
		if ( attr_content->length()>0)
		{
			TiXmlText txt( attr_content->c_str());
			if( xmle->FirstChild())
				xmle->InsertBeforeChild( xmle->FirstChild(), txt);
			else
				xmle->InsertEndChild( txt);
		}
	}
}
template <class T>
void TXB_ele_bind( TiXmlElement* xmle, bool from, std::vector<T>* ANI)
{
	if ( from) //from xml
	{
		for( TiXmlElement* child = xmle->FirstChildElement( T::TXB_tagname());
			child;
			child = child->NextSiblingElement( T::TXB_tagname()) )
		{
			T ani;
			ani.TXB_fromxml( child);
			ANI->push_back(ani);
		}
	}
	else //to xml
	{
		for ( int i=0;
			i<ANI->size();
			i++)
		{
			T* ani = &ANI->at(i);
			TiXmlElement Xani( ani->TXB_tagname());
			ani->TXB_toxml ( &Xani);
			xmle->InsertEndChild( Xani);
		}
	}
}
struct TXB //base class
{
	//this structure merely provides the interface "fromxml" and "toxml"
	// ,actually xml binding service can operate without "xvg"
	// ,so dont bother inheritance issue
	// ,if things mess up, inplement your own "fromxml" and "toxml" and that's it.
	//
	//inherit from "xvg" only for a *real* tag which you would give it a tag name
	virtual bool TXB_binding( TiXmlElement* , bool)=0;

	void TXB_fromxml( TiXmlElement* xmle)
	{
		if ( xmle) TXB_binding( xmle, 1);
	}
	void TXB_fromxmldoc( TiXmlDocument* DOC)
	{
		if( DOC)
			TXB_fromxml(TiXmlHandle(DOC).FirstChild().ToElement());
	}
	void TXB_toxml( TiXmlElement* xmle)
	{
		if ( xmle) TXB_binding( xmle, 0);
	}
};
#else
struct TXB
{
	virtual bool TXB_binding( )=0;
};
#endif //USE_TINY_XML_BIND

#endif //TINY_XML_BIND
