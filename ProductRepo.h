#ifndef PRODUCTREPO_H
#define PRODUCTREPO_H
#include "Product.h"

class ProductRepo
{
private:
	int c_index;
	int times;
	int multiply;
	
	int u_index;
	int undo_count;
	int undo_times;
	int undo_u_times;

	int r_index;
	int redo_count;
	int redo_times;
	int redo_u_times;
	
	int* undo;
	int* redo;
	Product* productRepo;
	Product* productUndo;
	Product* productRedo;
public:
	ProductRepo();
	
	void addProduct(Product& prod);
	void removeProduct(int id);
	void updateProduct(int id, int type, char *model, char *customer_name, date_c date, OnlineOrder on, OfflineOrder off);

	void displayByName(char *subname);
	void displayByModelAndDate(char* model, date_c sdate);
	void undoIt();
	void redoIt();

	void displayAll();
	void deleteAll();
	int getC_Idex();
	bool checkForID(int id);
	Product* getProductRepo();
};

#endif
