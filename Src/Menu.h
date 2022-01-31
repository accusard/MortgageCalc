//
//  Menu.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Menu_h
#define Menu_h

#include <iostream>
#include <vector>

using namespace std;
struct Action;

class Menu {
protected:

public:
    Menu(const string& n);
    ~Menu();
    
    void setHeadings(const string& heading);
    void showHeadings() const;
    void bindAction(shared_ptr<Action> bindingAction);
    const unsigned long listSubMenus();
    
    void run();
    void end();
    void select(const char subMenu);
    const char readInput();
    const char inputFront();
    const string& getLastUserInput() const {return userInput;}
    Menu* addSubMenu(shared_ptr<Menu> add);
    void clearInput();
    
    string name;
    string headings;
    string userInput;
    
private:
    shared_ptr<Action> action;
    vector<shared_ptr<Action>> sequence;
    vector<shared_ptr<Menu>> subMenus;
};

#endif /* Menu_h */
