#include "OfflineOrder.h"

OfflineOrder::OfflineOrder()
{
	strcpy_s(this->m_shop, "UNDEFINED");
}


OfflineOrder::OfflineOrder(char* shop)
{
	strcpy_s(this->m_shop, shop);
}

void OfflineOrder::setShop(char* shop)
{
	strcpy_s(this->m_shop, shop);
}

