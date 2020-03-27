#include "Product.h"

Product::Product(int id,int type,char *model,char *customer_name,date_c date)
{
	this->m_id = id;
	this->m_type = type;
	strcpy_s(this->m_model, model);
	strcpy_s(this->m_customer_name, customer_name);
	setDate(date);
}

void Product::setID(const int id)
{
	m_id = id;
}

void Product::setCN(char *cn)
{
	strcpy_s(this->m_customer_name, cn);
}

void Product::setDate(const date_c date)
{
	this->m_date.zi = date.zi;
	this->m_date.luna = date.luna;
	this->m_date.an = date.an;
}

void Product::setModel(char *model)
{
	strcpy_s(this->m_model,model);
}

void Product::setType(const int type)
{
	m_type = type;
}

bool Product::isSubString(char *subname)
{
	unsigned int p = 0;
	
	for(unsigned int i = 0; i < strlen(this->m_customer_name) && p < strlen(subname); ++i)
	{
		if (this->m_customer_name[i] == subname[p])
			p++;
		else
			p = 0;
	}
	if (p != 0)
		return true;
	return false;
}
