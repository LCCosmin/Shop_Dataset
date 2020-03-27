#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

#ifndef  LOVE_H
#define LOVE_H

typedef struct
{
	int an;
	int luna;
	int zi;
}date_c;

void greetings();
void display_menu();
string getType(int type);


#endif
