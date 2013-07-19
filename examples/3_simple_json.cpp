#include "../tinybind.h"
//compile by g++ ../tinybind.cpp 3_simple_json.cpp -o 3_simple_json

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "../tinybind_struct.h"
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
#include "../tinybind_json.h"
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
#include "../tinybind_clean.h"

int main()
{
	cJSON* json=cJSON_FromFile("3_sample.json");

	bakery bake;
	TXB_fromjson( &bake, json->child);

	cJSON* out = cJSON_CreateObject();
	TXB_tojson( &bake, cJSON_CreateNode(out,"bakery"));
	cJSON_Print( out, stdout);

	cJSON_Delete(json);
	cJSON_Delete(out);

	cout << endl;
	cout << "The name of the bakery is " << bake.name << endl;
	cout << "There are " << bake.cakes.size() << " cakes" << endl;
	cout << "The first one is " << bake.cakes[0].name << ", ";
	cout << "which has " << bake.cakes[0].fruits.size() << " topping " << bake.cakes[0].fruits[0].name << "." << endl;
	cout << "The second one is " << bake.cakes[1].name << ", ";
	cout << "which has " << bake.cakes[1].fruits.size() << " toppings, including " << bake.cakes[1].fruits[0].name << " and " << bake.cakes[1].fruits[1].name << "." << endl;

	return 1;
}
