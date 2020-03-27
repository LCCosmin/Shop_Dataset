#include "utils.h"

ProductRepo::ProductRepo()
{
	this->c_index = -1;
	this->times = 1;
	this->multiply = 10;
	
	this->u_index = -1;
	this->undo_count = -1;
	this->undo_times = 1;
	this->undo_u_times = 1;

	this->r_index = -1;
	this->redo_count = -1;
	this->redo_times = 1;
	this->redo_u_times = 1;

	this->undo = (int*)malloc(undo_times * multiply * sizeof(int));
	this->redo = (int*)malloc(redo_times * multiply * sizeof(int));
	
	this->productRepo = (Product*)malloc(times * multiply * sizeof(Product));
	this->productUndo = (Product*)malloc(undo_u_times * multiply * sizeof(Product));
	this->productRedo = (Product*)malloc(redo_u_times * multiply * sizeof(Product));
}


void ProductRepo::addProduct(Product& prod)
{
	c_index++;
	if (c_index == times * multiply)
	{
		times++;
		productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
		if (productRepo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}
	productRepo[c_index].setDate(prod.getDate());
	productRepo[c_index].setModel(prod.getModel());
	productRepo[c_index].setCN(prod.getCN());
	productRepo[c_index].setID(prod.getID());
	productRepo[c_index].setType(prod.getType());

	undo_count++;
	if (undo_count == undo_times * multiply)
	{
		undo_times++;
		undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
		if (undo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}
	undo[undo_count] = 1;
}

void ProductRepo::removeProduct(int id)
{
	int test = 0;
	int i;
	
	for (i = 0; i <= c_index && test != 1; ++i)
	{
		if (productRepo[i].getID() == id)
			test = 1;
	}
	//undo stuff

	undo_count++;
	u_index++;
	if (undo_count == undo_times * multiply)
	{
		undo_times++;
		undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
		if (undo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}

	if (u_index == undo_u_times * multiply)
	{
		undo_u_times++;
		productUndo = (Product*)realloc(productUndo, undo_u_times * multiply * sizeof(Product));
		if (productUndo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}

	undo[undo_count] = 2;
	i--;
	
	productUndo[u_index].setDate(productRepo[i].getDate());
	productUndo[u_index].setModel(productRepo[i].getModel());
	productUndo[u_index].setCN(productRepo[i].getCN());
	productUndo[u_index].setID(productRepo[i].getID());
	productUndo[u_index].setType(productRepo[i].getType());
	
	//undo stuff done

	//delete stuff
	for (; i < c_index; ++i)
	{
		productRepo[i] = productRepo[i + 1];
	}
	
	c_index--;
	if (c_index == (times - 1) * multiply)
	{
		times--;
		productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
		if (productRepo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}
	//delete stuff done
}

void ProductRepo::updateProduct(int id, int type, char *model, char *customer_name, date_c date)
{
	int test = 0;


	//undo stuff

	undo_count++;
	u_index++;
	if (undo_count == undo_times * multiply)
	{
		undo_times++;
		undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
		if (undo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}

	if (u_index == undo_u_times * multiply)
	{
		undo_u_times++;
		productUndo = (Product*)realloc(productUndo, undo_u_times * multiply * sizeof(Product));
		if (productUndo == nullptr)
		{
			cerr << "Bad allocation happened, program closed :( ";
			exit(1);
		}
	}

	undo[undo_count] = 3;

	int k;
	for (k = 0; k <= c_index && test != 1; ++k)
	{
		if (productRepo[k].getID() == id)
			test = 1;
	}

	k--;
	productUndo[u_index].setDate(productRepo[k].getDate());
	productUndo[u_index].setModel(productRepo[k].getModel());
	productUndo[u_index].setCN(productRepo[k].getCN());
	productUndo[u_index].setID(productRepo[k].getID());
	productUndo[u_index].setType(productRepo[k].getType());

	//undo stuff done

	test = 0;
	
	//update stuff
	for (auto i = 0; i <= c_index && test == 0; ++i)
	{
		if (productRepo[i].getID() == id)
		{
			productRepo[i].setDate(date);
			productRepo[i].setCN(customer_name);
			productRepo[i].setModel(model);
			productRepo[i].setType(type);
			test = 1;
		}
	}
}

void ProductRepo::displayByName(char* subname)
{
	
	vector <Product> prods;
	if (subname == "")
	{
		for (auto i = 0; i <= c_index; ++i)
			try
			{
				prods.push_back(productRepo[i]);
			}
			catch (const bad_alloc & ba)
			{
				cerr << "Bad allocation happened. Program closed :( ." << ba.what() << '\n';
				exit(1);
			}
	}
	else{
		for (auto i = 0; i <= c_index; ++i)
		{
			if (productRepo[i].isSubString(subname) == true)
			{
				try
				{
					prods.push_back(productRepo[i]);
				}
				catch (const bad_alloc & ba)
				{
					cerr << "Bad allocation happened. Program closed :( ." << ba.what() << '\n';
					exit(1);
				}
			}
		}
	}
	if (prods.size() != 0) {
		for (unsigned int i = 0; i < (prods.size() - 1); ++i)
			for (auto j = i + 1; j < prods.size(); ++j)
				if (mycmp(prods[i].getModel(), prods[j].getModel()))
					swap(prods[i], prods[j]);

		cout << string(100, '\n');
		for (unsigned int i = 0; i < prods.size(); ++i)
		{
			cout << "ORDER #" << i + 1;
			cout << "\nName of the customer: " << prods[i].getCN();
			cout << "\nThe wanted type: " << getType(prods[i].getType());
			cout << "\nThe wanted model: " << prods[i].getModel();
			cout << "\nThe due date: " << prods[i].getDate().zi << " / " << prods[i].getDate().luna << " / " << prods[i].getDate().an << endl << endl;
		}
		cout << "\n\nPlease hit ENTER to continue.";
		cin.ignore();
		cout << string(100, '\n');
	}
	else
	{
		cout << "\n\nNo orders meet the requirments, please hit ENTER to continue.";
		cin.ignore();
		cout << string(100, '\n');
	}
}

void ProductRepo::displayByModelAndDate(char* model, date_c sdate)
{
	int j = 0;
	int test = 0;

	cout << string(100, '\n');
	for(auto i = 0; i <= c_index; ++i)
	{
		if ((isInDate(productRepo[i].getDate(), sdate) == true) && strcmp(productRepo[i].getModel(), model) == 0)
		{
			j++;
			test = 1;
			cout << "\nORDER #" << j;
			cout << "\nName of the customer: " << productRepo[i].getCN();
			cout << "\nThe wanted type: " << getType(productRepo[i].getType());
			cout << "\nThe wanted model: " << productRepo[i].getModel();
			cout << "\nThe due date: " << productRepo[i].getDate().zi << " / " << productRepo[i].getDate().luna << " / " << productRepo[i].getDate().an << endl;
		}
	}
	if (test == 0)
	{
		cout << "There are no products that meet the entered filters, please hit ENTER to go back to the menu.\n";
		cin.ignore();
		cout << string(100, '\n');
	}
	else
	{
		cout << "\n\nPlease hit ENTER to return to the menu.";
		cin.ignore();
		cout << string(100, '\n');
	}
}

void ProductRepo::displayAll()
{
	if (c_index == -1)
	{
		cout << "\n\nThere are no order at this moment, please hit ENTER to continue.";
		cin.ignore();
		cout << string(100, '\n');
	}
	else
	{
		for (auto i = 0; i <= c_index; ++i)
		{
			cout << "\n\nORDER #" << i + 1;
			cout << "\nName of the customer: " << productRepo[i].getCN();
			cout << "\nThe wanted type: " << getType(productRepo[i].getType());
			cout << "\nThe wanted model: " << productRepo[i].getModel();
			cout << "\nThe due date: " << productRepo[i].getDate().zi << " / " << productRepo[i].getDate().luna << " / " << productRepo[i].getDate().an << endl;
		}
		cout << "\n\nPlease hit ENTER to continue.";
		cin.ignore();
		cout << string(100, '\n');
	}
}

void ProductRepo::deleteAll()
{
	productRepo = (Product*)realloc(productRepo, 1);
	if (productRepo == nullptr)
	{
		cerr << "Bad allocation happened, program closed :( ";
		exit(1);
	}
	c_index = -1;
	cout << "\n\nAll products have been deleted, hit ENTER to continue.";
	cin.ignore();
	cout << string(100, '\n');
	times = 1;
}

int ProductRepo::getC_Idex()
{
	return c_index;
}

bool ProductRepo::checkForID(int id)
{
	int test = 0;
	for (int i = 0; i <= c_index && test == 0; ++i)
	{
		if (productRepo[i].getID() == id)
			test = 1;
	}
	if (test == 1)
		return true;
	return false;
}

Product* ProductRepo::getProductRepo()
{
	return productRepo;
}

void ProductRepo::undoIt()
{
	if (undo_count != -1) {
		switch (undo[undo_count])
		{
		case 1:
			undo_count--;
			redo_count++;
			r_index++;
			redo[redo_count] = 1;
			if (redo_count == redo_times * multiply)
			{
				redo_times++;
				redo = (int*)realloc(redo, redo_times * multiply * sizeof(int));
				if (redo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (r_index == redo_u_times * multiply)
			{
				redo_u_times++;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			productRedo[r_index].setDate(productRepo[c_index].getDate());
			productRedo[r_index].setModel(productRepo[c_index].getModel());
			productRedo[r_index].setCN(productRepo[c_index].getCN());
			productRedo[r_index].setID(productRepo[c_index].getID());
			productRedo[r_index].setType(productRepo[c_index].getType());
			c_index--;
			if (c_index == ((times * multiply) - (times - 1) * multiply))
			{
				times--;
				productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
				if (productRepo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			cout << string(100, '\n');
			cout << "Operation undid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		case 2:
			undo_count--;
			redo_count++;
			r_index++;
			redo[redo_count] = 2;
			if (redo_count == redo_times * multiply)
			{
				redo_times++;
				redo = (int*)realloc(redo, redo_times * multiply * sizeof(int));
				if (redo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (r_index == redo_u_times * multiply)
			{
				redo_u_times++;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			c_index++;
			if (c_index == times * multiply)
			{
				times++;
				productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
				if (productRepo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			productRepo[c_index].setDate(productUndo[u_index].getDate());
			productRepo[c_index].setModel(productUndo[u_index].getModel());
			productRepo[c_index].setCN(productUndo[u_index].getCN());
			productRepo[c_index].setID(productUndo[u_index].getID());
			productRepo[c_index].setType(productUndo[u_index].getType());


			u_index--;
			if (u_index == undo_u_times * multiply)
			{
				undo_u_times++;
				productUndo = (Product*)realloc(productUndo, undo_u_times * multiply * sizeof(Product));
				if (productUndo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			cout << string(100, '\n');
			cout << "Operation undid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		case 3:
			undo_count--;
			redo_count++;
			r_index++;
			redo[redo_count] = 3;
			if (redo_count == redo_times * multiply)
			{
				redo_times++;
				redo = (int*)realloc(redo, redo_times * multiply * sizeof(int));
				if (redo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (r_index == redo_u_times * multiply)
			{
				redo_u_times++;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			int test = 0;

			for(int i = 0; i <= c_index && test == 0; ++i)
			{
				if (productRepo[i].getID() == productUndo[u_index].getID())
					test = i;
			}
			
			productRedo[r_index].setDate(productRepo[test].getDate());
			productRedo[r_index].setModel(productRepo[test].getModel());
			productRedo[r_index].setCN(productRepo[test].getCN());
			productRedo[r_index].setID(productRepo[test].getID());
			productRedo[r_index].setType(productRepo[test].getType());

			productRepo[test].setDate(productUndo[u_index].getDate());
			productRepo[test].setModel(productUndo[u_index].getModel());
			productRepo[test].setCN(productUndo[u_index].getCN());
			productRepo[test].setID(productUndo[u_index].getID());
			productRepo[test].setType(productUndo[u_index].getType());
			cout << string(100, '\n');
			cout << "Operation undid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		}
	}
	else
	{
		cout << string(100, '\n');
		cout << "There are no undo operations available, please hit ENTER to return to the menu";
		cin.ignore();
	}
}

void ProductRepo::redoIt()
{
	if (redo_count != -1) {

		switch (redo[redo_count])
		{
		case 1:
			redo_count--;
			undo_count++;
			undo[undo_count] = 1;
			if (undo_count == undo_times * multiply)
			{
				undo_times++;
				undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
				if (undo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			c_index++;
			if (c_index == times * multiply)
			{
				times++;
				productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
				if (productRepo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			productRepo[c_index].setDate(productRedo[r_index].getDate());
			productRepo[c_index].setModel(productRedo[r_index].getModel());
			productRepo[c_index].setCN(productRedo[r_index].getCN());
			productRepo[c_index].setID(productRedo[r_index].getID());
			productRepo[c_index].setType(productRedo[r_index].getType());

			r_index--;
			if (r_index == ((redo_u_times * multiply) - (redo_u_times - 1) * multiply))
			{
				redo_u_times--;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			cout << string(100, '\n');
			cout << "Operation redid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		case 2:
			redo_count--;
			undo_count++;
			u_index++;
			undo[undo_count] = 2;


			if (redo_count == ((redo_times * multiply) - (redo_times - 1) * multiply))
			{
				redo_times--;
				redo = (int*)realloc(redo, redo_times * multiply * sizeof(int));
				if (redo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (u_index == undo_u_times * multiply)
			{
				undo_u_times++;
				productUndo = (Product*)realloc(productUndo, undo_u_times * multiply * sizeof(Product));
				if (productUndo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (undo_count == undo_times * multiply)
			{
				undo_times++;
				undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
				if (undo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}


			productUndo[u_index].setDate(productRedo[r_index].getDate());
			productUndo[u_index].setModel(productRedo[r_index].getModel());
			productUndo[u_index].setCN(productRedo[r_index].getCN());
			productUndo[u_index].setID(productRedo[r_index].getID());
			productUndo[u_index].setType(productRedo[r_index].getType());

			c_index--;
			if (c_index == ((times * multiply) - (times - 1) * multiply))
			{
				times--;
				productRepo = (Product*)realloc(productRepo, times * multiply * sizeof(Product));
				if (productRepo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			r_index--;
			if (r_index == ((redo_u_times * multiply) - (redo_u_times - 1) * multiply))
			{
				redo_u_times--;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			cout << string(100, '\n');
			cout << "Operation redid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		case 3:
			redo_count--;
			undo_count++;
			u_index++;
			undo[undo_count] = 3;
			if (undo_count == undo_times * multiply)
			{
				undo_times++;
				undo = (int*)realloc(undo, undo_times * multiply * sizeof(int));
				if (redo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}
			if (u_index == redo_u_times * multiply)
			{
				redo_u_times++;
				productRedo = (Product*)realloc(productRedo, redo_u_times * multiply * sizeof(Product));
				if (productRedo == nullptr)
				{
					cerr << "Bad allocation happened, program closed :( ";
					exit(1);
				}
			}

			int test = 0;

			for (int i = 0; i <= c_index && test == 0; ++i)
			{
				if (productRepo[i].getID() == productUndo[u_index].getID())
					test = i;
			}

			productUndo[u_index].setDate(productRepo[test].getDate());
			productUndo[u_index].setModel(productRepo[test].getModel());
			productUndo[u_index].setCN(productRepo[test].getCN());
			productUndo[u_index].setID(productRepo[test].getID());
			productUndo[u_index].setType(productRepo[test].getType());

			productRepo[test].setDate(productRedo[r_index].getDate());
			productRepo[test].setModel(productRedo[r_index].getModel());
			productRepo[test].setCN(productRedo[r_index].getCN());
			productRepo[test].setID(productRedo[r_index].getID());
			productRepo[test].setType(productRedo[r_index].getType());

			cout << string(100, '\n');
			cout << "Operation redid with succes! Hit ENTER to return to the menu";
			cin.ignore();
			break;
		}
	}
	else
	{
		cout << string(100, '\n');
		cout << "There are no redo operations available, please hit ENTER to return to the menu";
		cin.ignore();
	}
}
