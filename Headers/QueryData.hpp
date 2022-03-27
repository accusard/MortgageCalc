//
//  QueryData.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef QueryData_hpp
#define QueryData_hpp

#include <iostream>
#include "Borrower.h"

using namespace std;

class QueryToString {
public:
    QueryToString(const string& txt) : prTxt(txt) {}
    virtual ~QueryToString() {}
    virtual void commandPrompt() {
        cout << prTxt;
    }
    
protected:
    const string prTxt;

};

template<class T>
class QueryToType  {
public:
    QueryToType(const string& txt, T& ref) : prTxt(txt), dataRef(ref) {}
    
    istream& commandPrompt() {
        cout << "Edit->" << prTxt << ": ";
        cin >> dataRef;
        return cin;
    }
    
    const string& get() const { return prTxt;}
    T& getDataRef () const {return dataRef;}
    
    friend istream& operator>>(istream& in, QueryToType<T>& q);
    
protected:
    const string prTxt;
    T& dataRef;
};

template<class T>
class QueryToVector : public QueryToString {
public:
    QueryToVector(const string& txt, vector<T>& vref) : QueryToString(txt), vectorRef(vref) {}
    
    virtual void commandPrompt() {
        T data;
        cout << QueryToString::prTxt;
        cin >> data;
        while(!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << QueryToString::prTxt;
            cin >> data;
        }
        vectorRef.push_back(data);
    }
    
private:
    vector<T>& vectorRef;
};

#endif /* QueryData_hpp */
