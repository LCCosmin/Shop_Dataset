#ifndef PRODUCT_H
#define PRODUCT_H
#include "OnlineOrder.h"

class Product
{
private:
	int m_id ;
	int m_type ;
	char m_model[100];
	char m_customer_name[100];
	date_c m_date;
	OnlineOrder m_on;
	OfflineOrder m_off;

public:
	Product(int id, int type,char *model,char *customer_name, date_c date, OnlineOrder on, OfflineOrder off);

	int getID() { return m_id; }
	int getType() { return m_type; }
	char* getModel() { return m_model; }
	char* getCN() { return m_customer_name; }
	date_c getDate() { return m_date; }
	OnlineOrder getOO() { return m_on; }
	OfflineOrder getOFO() { return m_off; }

	void setID(int id);
	void setType(int type);
	void setModel(char *model);
	void setCN(char *cn);
	void setDate(date_c date);
	void setOO(OnlineOrder on);
	void setOFO(OfflineOrder off);

	bool isSubString(char *subname);
};
#endif