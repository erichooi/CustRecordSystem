#ifndef DIALOG_H
#define DIALOG_H 

#include <iostream>
#include <vector>

void show_dialog(std::string);
void clrscreen();
void sleep();
int quit_loop();
int tokenize(std::string&, std::vector<std::string>&, std::string);

#endif /* ifndef DIALOG_H */
