#include "../tinyxmlbind.h"

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

#include "../tinyxmlbind_partA.h"
struct fruit
{
	string name;
	string text;
	int quantity;
};
struct cake
{
	string name;
	vector<fruit> fruits;
};
struct bakery
{
	string name;
	vector<cake> cakes;
	int unbinded;
};
#include "../tinyxmlbind_partB.h"
STRUCT(fruit)
{
	ATTR( string, name);
	TEXT( string, text);
	ATTR( int, quantity);
};
STRUCT(cake)
{
	ATTR( string, name);
	CHILD( fruit, fruits);
};
STRUCT(bakery)
{
	ATTR( string, name);
	CHILD( cake, cakes);
};
#include "../tinyxmlbind_partC.h"

int main()
{
	TiXmlDocument DOC;
	DOC.Parse( xml1);

	bakery bake;
	TXB_fromxmldoc(&bake, &DOC);

	TiXmlElement XBAKE("bakery");
	TXB_toxml(&bake, &XBAKE);
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
