#ifndef PRODUCT_H
#define PRODUCT_H
#include "Love.h"
#endif

bool isInDate(date_c date1, date_c date2)
{
	if (date1.an >= date2.an && date1.luna >= date2.luna && date1.zi >= date2.zi)
		return true;
	return false;
}

bool mycmp(char* a, char* b)
{
	return  a > b;
}

string getType(int type)
{
	switch (type)
	{
		case 1:
			return "necklace ";
		case 2:
			return "earring ";
		case 3:
			return "earing";
		default:
			return "Invalid type";
	}
}