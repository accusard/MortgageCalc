//
//  Menu.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Menu.h"
#include "Action.hpp"

//Menu::Menu(const string& n) : name(n), headings(""), userInput("") {}

Menu::Menu(const string& n) : name(n) {
    
}

Menu::~Menu() {}

void Menu::setHeadings(const string &setHeading) {
    headings = setHeading;
}

const char Menu::readInput() {
    getline(cin, userInput);
    return inputFront();
}

const char Menu::inputFront() {
    return tolower(userInput.front());
}

void Menu::showHeadings() const {
    cout << endl << endl << headings << endl << endl;
}

Menu* Menu::addSubMenu(shared_ptr<Menu> add) {
    subMenus.push_back(add);
    return add.get();
}

void Menu::clearInput() {
    userInput = '\0';
}

void Menu::select(const char subMenu) {
    for(auto i : subMenus) {
        const char c = tolower(i->name.front());
        if(c == subMenu) {
            i->run();
            i->clearInput();
        }
    }
}

const unsigned long Menu::listSubMenus() {
    for(vector<shared_ptr<Menu>>::iterator it = subMenus.begin(); it != subMenus.end(); it++) {
        const char fChar = toupper(it->get()->name.front());
        const string rString = it->get()->name.substr(1, it->get()->name.size());
        cout << "(" << fChar << ")" << rString << endl;
    }
    cout << endl << "- ";
    return subMenus.size();
}

void Menu::bindAction(shared_ptr<Action> bindingAction) {
    sequence.push_back(bindingAction);
}

void Menu::run() {
    cout << "--- " << name << " ---";
    showHeadings();
    if(listSubMenus() != 0)
        select(readInput());
    
    if(sequence.size() != 0) {
        for(auto a : sequence)
            a->execute();
    }
}

void Menu::end() {
    cout << endl;
}
    


