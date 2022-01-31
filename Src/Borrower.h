//
//  Borrower.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Borrower_hpp
#define Borrower_hpp

#include <iostream>
#include "Earnings.h"

class Earnings;
struct MortgageData;
using namespace std;

struct Name {
    Name();
    string f, m, l;
    const bool operator!=(const Name& other) const;
    friend istream& operator>>(istream& cin, Name& fullName);
};

struct Borrower {
    Borrower();
    Borrower(const Name& n);
    void calcEarnings(float regRate);
    
    const Name& getName() const;
    const float getWeeklyEarnings() const;
    const float getYearlyEarnings() const;
    const float getMonthlyEarnings() const;
    const float getMonthlyDebts() const;
    const float getHourlyRate() const;
    void setMonthlyDebts(const float set);
    
    friend istream& operator>>(istream &cin, Borrower& b);
    const bool operator!=(const Borrower& other);
    
private:
    Name name;
    Earnings earnings;
    float monthlyDebts;
};

#endif /* Borrower_hpp */
