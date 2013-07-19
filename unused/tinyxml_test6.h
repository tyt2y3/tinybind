#ifndef XML_BINDER_FOR_SVG_H
#define XML_BINDER_FOR_SVG_H

#ifdef USE_XML_BINDING
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

	#define TAG_NAME(X) static const char* name() { return X;}
	#define XML_BINDING bool binding( TiXmlElement* xmle, int m)
	#define ATTRIBUTE(HOLDER,ATTR_NAME) attr_fromtoxml( xmle, m, & HOLDER, ATTR_NAME)
	#define CHILD_ELEMENT(HOLDER,CHILD_STRUCT) ele_fromtoxml<CHILD_STRUCT>( xmle, m, & HOLDER)
	#define INHERIT(X) X ::binding( xmle,m)
#else
	#define TAG_NAME(X) static const char* name() { return X;}
	#define XML_BINDING bool binding() 
	#define ATTRIBUTE(HOLDER,ATTR_NAME)  
	#define CHILD_ELEMENT(HOLDER,CHILD_STRUCT)  
	#define INHERIT(X)  
#endif

#ifdef USE_XML_BINDING
using namespace std;
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
	//this structure merely provides the interface "fromxml" and "toxml"
	// ,actually xml binding service can operate without "xvg"
	// ,so dont bother inheritance issue
	// ,if things mess up, inplement your own "fromxml" and "toxml" and that's it.
	//
	//inherit from "xvg" only for a *real* tag which you would give it a tag name
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

#endif //XML_BINDER_FOR_SVG_H
