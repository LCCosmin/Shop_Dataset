#ifndef PRODUCT_H
#define PRODUCT_H
#include "Love.h"

class Product
{
private:
	int m_id ;
	int m_type ;
	char m_model[100];
	char m_customer_name[100];
	date_c m_date;

public:
	Product(int id, int type,char *model,char *customer_name, date_c date);

	int getID() { return m_id; }
	int getType() { return m_type; }
	char* getModel() { return m_model; }
	char* getCN() { return m_customer_name; }
	date_c getDate() { return m_date; }

	void setID(int id);
	void setType(int type);
	void setModel(char *model);
	void setCN(char *cn);
	void setDate(date_c date);

	bool isSubString(char *subname);
};
#endif