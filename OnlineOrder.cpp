#include "OnlineOrder.h"

OnlineOrder::OnlineOrder()
{
	strcpy_s(this->m_website, "UNDEFINED");
	strcpy_s(this->m_deliveryMethod, "UNDEFINED");
}

OnlineOrder::OnlineOrder(char* website, char* deliveryMethod)
{
	strcpy_s(this->m_website, website);
	strcpy_s(this->m_deliveryMethod, deliveryMethod);
}

void OnlineOrder::setDM(char* deliveryMethod)
{
	strcpy_s(this->m_deliveryMethod, deliveryMethod);
}

void OnlineOrder::setWeb(char* website)
{
	strcpy_s(this->m_website, website);
}
