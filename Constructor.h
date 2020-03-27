#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

void display_menu();
void begin(ProductRepo& repo);
void addprod(ProductRepo& repo);
void addprod(ProductRepo& repo);
void removeprod(ProductRepo& repo);
void updateprod(ProductRepo& repo);
void displaybyname(ProductRepo& repo);
void choosemodel(ProductRepo& repo);

bool isValidID(int id, ProductRepo& repo);
bool isValidType(int type);
bool isValidDay(date_c date);


#endif
