#ifndef ONLINE_ORDER
#define ONLINE_ORDER
#include "OfflineOrder.h"

class OnlineOrder
{
private:
	char m_website[100];
	char m_deliveryMethod[100];
public:
	OnlineOrder();
	OnlineOrder(char* website, char* deliveryMethod);

	char* getWeb() { return m_website; }
	char* getDM() { return m_deliveryMethod; }

	void setWeb(char* website);
	void setDM(char* deliveryMethod);
};

#endif
