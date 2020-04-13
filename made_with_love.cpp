#include "utils.h"

void greetings()
{
	cout << "PROBLEM#5\n";
	cout << "Made With Love\n\n";
	cout << "Day of the creation: 17 / 03 / 2020\n";
	cout << "Day of the last edit: 31/ 03 / 2020\n";
	cout << "Subpoints done: 4 / 4.\n";
	cout << "Solved by: Leonte Cosmin\n";
	cout << "Group: 812/2\n\n";
	cout << "\n\nTotal LINES OF CODE wrote : 1590\n";
	

	cout << "\n\n\nIn order to proceed, please hit THE ENTER KEY !";
	cin.ignore();
	cout << string(100, '\n');
}

int main()
{
	greetings();
	
	ProductRepo repo; 
	begin(repo);
	return 0;
}