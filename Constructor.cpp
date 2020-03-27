#include "utils.h"

bool isValidID(int id, ProductRepo &repo)
{
	if (id <= 0)
		return false;
	for (auto i = 0 ; i <= repo.getC_Idex(); ++i)
	{
		if (repo.getProductRepo()[i].getID() == id)
			return false;
	}
	return true;
}

bool isValidType(int type)
{
	return (type >= 1 && type <= 3);
}

bool isValidDay(date_c date)
{
	if (date.zi < 1)
		return false;
	if (date.an % 4 && date.luna == 2 && date.zi == 29)
		return true;
	if (date.an % 4 != 0 && date.luna == 2 && date.zi < 29)
		return true;
	if ((date.luna == 1 || date.luna == 3 || date.luna == 5 || date.luna == 7
		|| date.luna == 8 || date.luna == 10) && date.zi < 32)
		return true;
	if (date.zi < 31)
		return true;
	return false;
}

void addprod(ProductRepo& repo)
{
	int id;
	int type;
	char model_s[100];
	char customer_name_s[100];
	
	date_c date;
	//CHECK ID
	do
	{
		cout << string(100, '\n');
		cout << "Insert the ID of the order(0,n^32):\n";
		cin >> id;
		cin.get();
		if (!isValidID(id, repo))
		{
			cout << string(100, '\n');
			cout << "\nInvalid order ID, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while (!isValidID(id, repo));
	//CHECK TYPE
	do
	{
		cout << string(100, '\n');
		cout << "Here is a list of all types:";
		cout << "\n1.NECKLACE";
		cout << "\n2.EARRING";
		cout << "\n3.EARING";
		cout << "\nEnter a number between 1 - 3 that will represent the type:\n";
		cin >> type;
		cin.get();
		if (!isValidType(type))
		{
			cout << string(100, '\n');
			cout << "\nInvalid order type, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while (!isValidType(type));
	//GET MODEL
	cout << string(100, '\n');
	cout << "Please enter the model name:\n";
	cin.getline(model_s, 100, '\n');

	//GET CUSTOMER_NAME
	cout << string(100, '\n');
	cout << "Please enter the customer name:\n";

	cin.getline(customer_name_s, 100, '\n');

	//CHECK DATE
	//YEAR
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due year:\n";
		cin >> date.an;
		cin.get();
		if (date.an < 0 )
		{
			cout << "\nInvalid due year, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while ((date.an < 0));

	//MONTH
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due month:\n";
		cin >> date.luna;
		cin.get();
		if (date.luna < 1 || date.luna > 12)
		{
			cout << "\nInvalid due month, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while ((date.luna < 1 || date.luna > 12));
	//DAY
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due day:\n";
		cin >> date.zi;
		cin.get();
		if(!isValidDay(date))
		{
			cout << "\nInvalid due day, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while (!isValidDay(date));
	cout << string(100, '\n');
	
	Product product(id,type, model_s, customer_name_s, date);
	repo.addProduct(product);

	cout << "\n\nProduct added succesfully !\n\n";
	cout << "\n\nPlease hit ENTER to continue.";
	cin.ignore();
	cout << string(100, '\n');
}


void updateprod(ProductRepo &repo)
{
	int id = -1;
	int test;

	do
	{
		test = 0;
		cout << string(100, '\n');
		cout << "Insert the ID of the order that you are looking for to update or 0 to close this feature:\n";
		cin >> id;
		cin.get();
		if (repo.checkForID(id) == true) 
			test = 1;
		else if (id == 0)
		{
			cout << string(100, '\n');
			test = 1;
		}
		else
		{
			cout << string(100, '\n');
			cout << "The inserted ID does not exist, please hit ENTER KEY to continue.\n";
			cin.ignore();
		}
	} while (test != 1);
	if (id != 0) {
		cout << string(100, '\n');
		int type;
		char model_s[100];
		char customer_name_s[100];

		date_c date;
		//CHECK TYPE
		do
		{
			cout << string(100, '\n');
			cout << "Here is a list of all types:";
			cout << "\n1.NECKLACE";
			cout << "\n2.EARRING";
			cout << "\n3.EARING";
			cout << "\nEnter a number between 1 - 3 that will represent the type:\n";
			cin >> type;
			if (!isValidType(type))
			{
				cout << "\nInvalid order type, hit THE ENTER KEY in order to continue";
				cin.ignore();
			}
		} while (!isValidType(type));
		//GET MODEL
		cout << string(100, '\n');
		cout << "Please enter the model name:\n";
		cin.get();
		cin.getline(model_s, 100, '\n');

		//GET CUSTOMER_NAME
		cout << string(100, '\n');
		cout << "Please enter the customer name:\n";

		cin.getline(customer_name_s, 100, '\n');

		//CHECK DATE
		//YEAR
		do
		{
			cout << string(100, '\n');
			cout << "Please enter the due year:\n";
			cin >> date.an;
			if (date.an < 0)
			{
				cin.get();
				cout << "\nInvalid due year, hit THE ENTER KEY in order to continue";
				cin.ignore();
			}
		} while ((date.an < 0));
		//MONTH
		do
		{
			cout << string(100, '\n');
			cout << "Please enter the due month:\n";
			cin >> date.luna;
			if (date.luna < 1 || date.luna > 12)
			{
				cout << "\nInvalid due month, hit THE ENTER KEY in order to continue";
				cin.ignore();
			}
		} while ((date.luna < 1 || date.luna > 12));
		//DAY
		do
		{
			cout << string(100, '\n');
			cout << "Please enter the due day:\n";
			cin >> date.zi;
			if (!isValidDay(date))
			{
				cout << "\nInvalid due day, hit THE ENTER KEY in order to continue";
				cin.ignore();
			}
		} while (!isValidDay(date));
		cout << string(100, '\n');
		cin.get();
		repo.updateProduct(id, type, model_s, customer_name_s, date);

		cout << "\n\nProduct updated succesfully !\n\n";
		cout << "\n\nPlease hit ENTER to continue.";
		cin.ignore();
		cout << string(100, '\n');
	}
}

void display_menu()
{
	cout << "Here is the list of all of the actions that you can do: ";
	cout << "\n1.Add an order.";
	cout << "\n2.Remove an order";
	cout << "\n3.Update an order";
	cout << "\n4.Display all orders.";
	cout << "\n5.Delete all orders.";
	cout << "\n6.Display orders by name.";
	cout << "\n7.Display orders by model and starting from a specific date";
	cout << "\n8.Undo last operation";
	cout << "\n9.Redo last operation";
	cout << "\n0.Exit program";
}

void removeprod(ProductRepo &repo)
{
	int id;
	int test;
	
	do
	{
		test = 0;
		cout << string(100, '\n');
		cout << "Insert the ID of the order that you are looking for to delete or 0 to close this feature:\n";
		cin >> id;
		cin.get();
		if (repo.checkForID(id) == true) {
			repo.removeProduct(id);
			test = 1;
			cout << "\n\nProduct removed succesfully !\n\n";
			cout << "\n\nPlease hit ENTER to continue.";
			cin.ignore();
			cout << string(100, '\n');
		}
		else if(id == 0)
			test = 1;
		else
		{
			cout << string(100, '\n');
			cout << "The inserted ID does not exist, please hit ENTER KEY to continue.\n";
			cin.ignore();
		}
	} while (test != 1);
}

void displaybyname(ProductRepo& repo)
{
	char substring[100];
	
	cout << string(100, '\n');
	cout << "Insert the substring that you want this feature to use:\n";
	cin.getline(substring,100,'\n');
	repo.displayByName(substring);
}

void choosemodel(ProductRepo& repo)
{
	char model_s[100];
	date_c date;

	cout << string(100, '\n');
	cout << "Insert the substring that you want this feature to use:\n";
	cin.getline(model_s, 100, '\n');

	//CHECK DATE
		//YEAR
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due year:\n";
		cin >> date.an;
		if (date.an < 0)
		{
			cin.get();
			cout << "\nInvalid due year, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while ((date.an < 0));
	//MONTH
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due month:\n";
		cin >> date.luna;
		if (date.luna < 1 || date.luna > 12)
		{
			cout << "\nInvalid due month, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while ((date.luna < 1 || date.luna > 12));
	//DAY
	do
	{
		cout << string(100, '\n');
		cout << "Please enter the due day:\n";
		cin >> date.zi;
		cin.get();
		if (!isValidDay(date))
		{
			cout << "\nInvalid due day, hit THE ENTER KEY in order to continue";
			cin.ignore();
		}
	} while (!isValidDay(date));

	repo.displayByModelAndDate(model_s, date);
}

void begin(ProductRepo &repo)
{
	
	char action;
	do {
		display_menu();
		cout << "\n\nInsert the number of the action that you want to do: ";
		cin.get(action);
		cin.get();
		cout << string(100, '\n');
		switch (action)
		{
		case '1':
			addprod(repo);
			break;
		case '2':
			removeprod(repo);
			break;
		case '3':
			updateprod(repo);
			break;
		case '4':
			repo.displayAll();
			break;
		case '5':
			repo.deleteAll();
			break;
		case '6':
			displaybyname(repo);
			break;
		case '7':
			choosemodel(repo);
			break;
		case '8':
			repo.undoIt();
			break;
		case '9':
			repo.redoIt();
			break;
		case '0':
			cout << "Program closing down, hit ENTER to exit ...";
			cin.ignore();
			break;
		default:
			cout << "\nYou have inserted a wrong action . Please hit THE ENTER KEY to continue";
			cin.get();
			cin.ignore();
		}
	} while (action != '0');
}