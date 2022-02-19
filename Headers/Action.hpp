//
//  Action.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Action_hpp
#define Action_hpp

#include <map>
#include "mcData.hpp"
#include "Borrower.h"
#include "QueryData.hpp"

class Menu;

using namespace std;

struct Action {
    Action() {}
    virtual ~Action() {}
    virtual void execute() {}
};

class MortgageReport : public mcData, public Action {
public:
    MortgageReport(mcData& dRef) : mcData(dRef) {}
    virtual void execute() override;
    
private:
    
};

class AmortizationReport : public mcData, public Action {
public:
    AmortizationReport(mcData& ref) : mcData(ref) {}
    virtual void execute() override;
    
    // separate calculations from print output
    // void amortize();
    // void printout();
private:
    // change dataHash to use a struct for second pair
    map<int, float> dataHash;
};

class BorrowerReport : public Action {
public:
    BorrowerReport(vector<Borrower>& b) : borrowers(b) {}
    virtual void execute() override;
    
private:
    vector<Borrower>& borrowers;
};


class DTIReport : public mcData, public Action {
public:
    DTIReport(mcData& dref) : mcData(dref) {}
    virtual void execute() override;
    
private:
    
};


class SequencePrompts : public mcData, public Action {
    
public:
    SequencePrompts(mcData& d);
    
    void addQuery(const string &prompt, float &data);
    void addQuery(const string &prompt, int &data);
    void addQuery(const string &prompt, vector<Borrower>& vRef);
    
    virtual void execute();
    
private:
    vector<QueryToType<float>> inquiriesFloat;
    vector<QueryToType<int>> inquriesInt;
    vector<QueryToVector<Borrower>> inquiriesBorrower;
};


template<class T>
class SinglePrompt : public Action {
public:
    SinglePrompt(const string& prmpt, T& dataRef) : inquiry(prmpt), data(dataRef) {}
    virtual void execute() {
        QueryToType<T> q = QueryToType<T>(inquiry, data);
        cin >> q;
    }
private:
    string inquiry;
    T& data;
};


class Loop : public Action {
public:
    Loop(Menu* menu, void(Menu::*loopPtr)(), const char exit);
    virtual void execute();
    
private:
    void(Menu::*loop)();
    Menu* menuPtr;
    char stop;
};


struct Exit : public Action {
    virtual void execute() override;
};


#endif /* Action_hpp */
