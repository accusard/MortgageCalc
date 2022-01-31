//
//  QueryData.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef QueryData_hpp
#define QueryData_hpp

#include <iostream>
using namespace std;

template<class T>
class QueryORIGINAL {
public:
    QueryORIGINAL(const string& txt) : prTxt(txt) {}
    virtual ~QueryORIGINAL() {}
    virtual void prompt() {
        cout << prTxt;
    }
    
protected:
    const string prTxt;

};


template<class T>
class QueryToType  {
public:
    QueryToType(const string& txt, T& ref) : prTxt(txt), dataRef(ref) {}
    
    istream& prompt() {
        cout << prTxt << " - ";
        cin >> dataRef;
        return cin;
    }
    
    const string& getText() const { return prTxt;}
    T& getDataRef () const {return dataRef;}
    
    friend istream& operator>>(istream& in, QueryToType<T>& q);
    
protected:
    const string prTxt;
    T& dataRef;
};

template<class T>
class QueryToVector : public QueryORIGINAL<T> {
public:
    QueryToVector(const string& txt, vector<T>& vref) : QueryORIGINAL<T>(txt), vectorRef(vref) {}
    
    virtual void prompt() {
        T data;
        cout << QueryORIGINAL<T>::prTxt;
        cin >> data;
        while(!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << QueryORIGINAL<T>::prTxt;
            cin >> data;
        }
        vectorRef.push_back(data);
    }
    
private:
    vector<T>& vectorRef;
};

//template<class T>
//class QueryToVector : public QueryORIGINAL<T> {
//public:
//    QueryToVector(const string& txt, vector<T>& vref) : QueryORIGINAL<T>(txt), vectorRef(vref) {}
//
//    istream& prompt() {
//        T data;
//        cout << QueryORIGINAL<T>::prTxt;
//        cin >> data;
//        vectorRef.push_back(data);
//        return cin;
//    }
//
//    friend istream& operator>>(istream& in, QueryToVector<T>& q);
//
//private:
//    vector<T>& vectorRef;
//};

#endif /* QueryData_hpp */