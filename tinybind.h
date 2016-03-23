#ifndef TINY_BIND
#define TINY_BIND

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------XML---------------------------------------//

//#define TIXML_USE_STL
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#ifndef WIN32 
	//to solve "error: ‘stricmp’ was not declared in this scope"
	#define stricmp strcasecmp 
	#define strnicmp strncasecmp 
#endif

#define TXB_fromxml(X,Y) TXB_binding( X, Y, 1)
#define TXB_toxml(X,Y) TXB_binding( X, Y, 0)
#define TXB_fromxmldoc(X,Y) TXB_binding( X, TiXmlHandle(Y).FirstChild().ToElement(), 1)
#define TXB_toxmldoc(X,Y) TXB_binding( X, TiXmlHandle(Y).FirstChild().ToElement(), 0)

void TXB_attr_bind( TiXmlElement* xmle, bool from, bool* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
		{
			*attr_content = (std::string(xmle->Attribute(attr_name)).compare("true")==0);
		}
	}
	else //to xml
	{
		xmle->SetAttribute( attr_name, *attr_content?"true":"false");
	}
}
template <class T>
void TXB_attr_bind_int( TiXmlElement* xmle, bool from, T* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = (T)strtol(xmle->Attribute(attr_name),0,0);
	}
	else //to xml
	{
		char buf[100];
		snprintf(buf,100,"%d",*attr_content);
		xmle->SetAttribute( attr_name, buf);
	}
}
void TXB_attr_bind( TiXmlElement* xmle, bool from, int* attr_content, const char* attr_name)
{ TXB_attr_bind_int<int>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, unsigned int* attr_content, const char* attr_name)
{ TXB_attr_bind_int<unsigned int>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, char* attr_content, const char* attr_name)
{ TXB_attr_bind_int<char>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, unsigned char* attr_content, const char* attr_name)
{ TXB_attr_bind_int<unsigned char>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, short* attr_content, const char* attr_name)
{ TXB_attr_bind_int<short>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, unsigned short* attr_content, const char* attr_name)
{ TXB_attr_bind_int<unsigned short>(xmle,from,attr_content,attr_name); }

template <class T>
void TXB_attr_bind_float( TiXmlElement* xmle, bool from, T* attr_content, const char* attr_name)
{
	if ( from) //from xml
	{
		if ( xmle->Attribute(attr_name))
			*attr_content = (T)strtod(xmle->Attribute(attr_name),0);
	}
	else //to xml
	{
		char buf[100];
		snprintf(buf,100,"%f",*attr_content);
		xmle->SetAttribute( attr_name, buf);
	}
}
void TXB_attr_bind( TiXmlElement* xmle, bool from, float* attr_content, const char* attr_name)
{ TXB_attr_bind_float<float>(xmle,from,attr_content,attr_name); }
void TXB_attr_bind( TiXmlElement* xmle, bool from, double* attr_content, const char* attr_name)
{ TXB_attr_bind_float<double>(xmle,from,attr_content,attr_name); }

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
void TXB_ele_bind( TiXmlElement* xmle, bool from, std::vector<T>* ANI, const char* tagname)
{
	if ( from) //from xml
	{
		for( TiXmlElement* child = xmle->FirstChildElement(tagname);
			child;
			child = child->NextSiblingElement(tagname) )
		{
			T ani;
			TXB_binding(&ani, child, 1);
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
			TiXmlElement Xani(tagname);
			TXB_binding(ani, &Xani, 0);
			xmle->InsertEndChild( Xani);
		}
	}
}

//-----------------------------------JSON---------------------------------------//

#include "cJSON/cJSON.h"

//cJSON patches
cJSON* cJSON_FromFile(const char* filename)
{
	FILE *f=fopen(filename,"rb");fseek(f,0,SEEK_END);long len=ftell(f);fseek(f,0,SEEK_SET);
	char *data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
	cJSON* json = cJSON_Parse(data);
	free(data);
	if (!json)
	{
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return 0;
	}
	return json;
}
cJSON* cJSON_CreateNode(cJSON* json, const char* name)
{
	cJSON* node = cJSON_CreateObject();
	cJSON_AddItemToObject( json, name, node);
	return node;
}
void cJSON_Print(cJSON* json, FILE* out)
{
	char* print = cJSON_Print(json);
	fprintf( out, "%s", print);
	free(print);
}
//end cJSON patches

#define TXB_fromjson(X,Y) TXB_binding( X, Y, 1)
#define TXB_tojson(X,Y) TXB_binding( X, Y, 0)

template <class T>
void TXB_attr_bind_int( cJSON* json, bool from, T* attr_content, const char* attr_name)
{
	if ( from) //from json
	{
		cJSON* item = cJSON_GetObjectItem(json,attr_name);
		if( item && item->type == cJSON_Number)
			*attr_content = item->valueint;
	}
	else //to json
	{
		cJSON_AddNumberToObject(json,attr_name,*attr_content);
	}
}
void TXB_attr_bind( cJSON* json, bool from, int* attr_content, const char* attr_name)
{	TXB_attr_bind_int<int>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, unsigned int* attr_content, const char* attr_name)
{	TXB_attr_bind_int<unsigned int>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, char* attr_content, const char* attr_name)
{	TXB_attr_bind_int<char>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, unsigned char* attr_content, const char* attr_name)
{	TXB_attr_bind_int<unsigned char>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, short* attr_content, const char* attr_name)
{	TXB_attr_bind_int<short>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, unsigned short* attr_content, const char* attr_name)
{	TXB_attr_bind_int<unsigned short>(json,from,attr_content,attr_name); }

template <class T>
void TXB_attr_bind_float( cJSON* json, bool from, T* attr_content, const char* attr_name)
{
	if ( from) //from json
	{
		cJSON* item = cJSON_GetObjectItem(json,attr_name);
		if( item && item->type == cJSON_Number)
			*attr_content = item->valuedouble;
	}
	else //to json
	{
		cJSON_AddNumberToObject(json,attr_name,*attr_content);
	}
}
void TXB_attr_bind( cJSON* json, bool from, double* attr_content, const char* attr_name)
{	TXB_attr_bind_float<double>(json,from,attr_content,attr_name); }
void TXB_attr_bind( cJSON* json, bool from, float* attr_content, const char* attr_name)
{	TXB_attr_bind_float<float>(json,from,attr_content,attr_name); }

void TXB_attr_bind( cJSON* json, bool from, std::string* attr_content, const char* attr_name)
{
	if ( from) //from json
	{
		cJSON* item = cJSON_GetObjectItem(json,attr_name);
		if( item && item->type == cJSON_String)
			*attr_content = item->valuestring;
	}
	else //to json
	{
		if ( attr_content->length()>0)
			cJSON_AddStringToObject(json,attr_name, attr_content->c_str());
	}
}
void TXB_text_bind( cJSON* json, bool from, std::string* attr_content)
{
	TXB_attr_bind( json, from, attr_content, "text");
}

template <class T>
void TXB_ele_bind( cJSON* json, bool from, std::vector<T>* ANI, const char* tagname)
{
	if ( from) //from json
	{
		cJSON* arr = cJSON_GetObjectItem(json,tagname);
		if( arr != NULL && arr->type == cJSON_Array)
		for (int i=0, length=cJSON_GetArraySize(arr); i<length; i++)
		{
			cJSON* child=cJSON_GetArrayItem(arr,i);
			T ani;
			TXB_binding(&ani, child, 1);
			ANI->push_back(ani);
		}
	}
	else //to json
	{
		cJSON* arr = cJSON_CreateArray();
		cJSON_AddItemToObject(json, tagname, arr);
		for ( int i=0; i<ANI->size(); i++)
		{
			T* ani = &ANI->at(i);
			cJSON* jani = cJSON_CreateObject();
			TXB_binding(ani, jani, 0);
			cJSON_AddItemToArray(arr, jani);
		}
	}
}

#endif //TINY_BIND
