#ifndef OFFLINE_ORDER
#define OFFLINE_ORDER
#include "Love.h"

class OfflineOrder
{
private:
	char  m_shop[100];
public:
	OfflineOrder();
	OfflineOrder(char* shop);
	
	char* getShop() { return m_shop; }

	void setShop(char* shop);
};

#endif
