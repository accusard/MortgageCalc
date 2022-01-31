//
//  Action.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Action_hpp
#define Action_hpp

#include "MortgageCalculator.h"

class Menu;

using namespace std;



struct Action {
    Action() {}
    virtual ~Action() {}
    virtual void execute() {}
};

class Report {
public:
    Report(MortgageData& dRef) : data(dRef) {}
    
protected:
    MortgageData& data;
};


class MortgageReport : public Report, public Action {
public:
    MortgageReport(MortgageData& dRef) : Report(dRef) {}
    virtual void execute() override;
    
private:
    
};


class BorrowerReport : public Action {
public:
    BorrowerReport(vector<Borrower>& b) : data(b) {}
    virtual void execute() override;
    
private:
    vector<Borrower>& data;
};


class DTIReport : public Report, public Action {
public:
    DTIReport(MortgageData& dref) : Report(dref) {}
    virtual void execute() override;
    
private:
    
};


class SequencePrompts : public Report, public Action {
    
public:
    SequencePrompts(MortgageData& d);
    
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
