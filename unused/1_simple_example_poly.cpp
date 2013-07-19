#define USE_TINY_XML_BIND
#include "tinyxmlbind_poly.h"

const char* xml1=
"<bakery name='Janes'>"
"<cake name='New York Cheese'>"
"	<fruit name='blue berries' quantity='25'>freshness topping</fruit>"
"</cake>"
"<cake name='white forest'>"
"	<fruit name='blue berries' quantity='10' illegal='attribute'></fruit>"
"	<fruit name='strawberries' quantity='8'></fruit>"
"</cake>"
"</bakery>";

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

struct fruit : TXB
{
	string name;
	string text;
	int quantity;

	TXB_BIND("fruit")
	{
		TXB_ATTR(name);
		TXB_TEXT(text);
		TXB_ATTR(quantity);
	}
};

struct cake : TXB
{
	string name;
	vector<fruit> fruits;
	
	TXB_BIND("cake")
	{
		TXB_ATTR(name);
		TXB_CHILD(fruits,fruit);
	}
};

struct bakery : TXB
{
	string name;
	vector<cake> cakes;
	int unbinded;

	TXB_BIND("bakery")
	{
		TXB_ATTR(name);
		TXB_CHILD(cakes,cake);
	}
};

int main()
{
	TiXmlDocument DOC;
	DOC.Parse( xml1);

	bakery bake;
	bake.TXB_fromxmldoc(&DOC);

	TiXmlElement XBAKE("bakery");
	bake.TXB_toxml( &XBAKE);
	XBAKE.Print( stdout, 0);

	cout << endl;
	cout << "The name of the bakery is " << bake.name << endl;
	cout << "There are " << bake.cakes.size() << " cakes" << endl;
	cout << "The first one is " << bake.cakes[0].name << ", ";
	cout << "which has " << bake.cakes[0].fruits.size() << " topping " << bake.cakes[0].fruits[0].name << "." << endl;
	cout << "The second one is " << bake.cakes[1].name << ", ";
	cout << "which has " << bake.cakes[1].fruits.size() << " toppings, including " << bake.cakes[1].fruits[0].name << " and " << bake.cakes[1].fruits[1].name << "." << endl;

	return 1;
}
