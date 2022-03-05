//
//  Borrower.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Borrower.h"
#include "QueryData.hpp"



istream& operator>>(istream &cin, Borrower& b) {
    Name n;
    cin >> n;
    
    float rate, mdebts;
    vector<pair<string, float&> > fdata;
    fdata.push_back(pair<string, float&>("Enter the borrower's hourly rate", rate));
    fdata.push_back(pair<string, float&>("Enter monthly debt obligations", mdebts));
    
    for(auto d : fdata) {
        QueryToType<float> q = QueryToType<float>(d.first, d.second);
        cin >> q;
    }
    
    b = Borrower(n);
    b.calcEarnings(rate);
    b.setMonthlyDebts(mdebts);
    
    return cin;
    
}

istream& operator>>(istream& cin, Name& name) {
    string fulln;
    cout << "Enter the full name of the borrower - ";
    getline(cin, fulln);
    
    size_t sp1 = fulln.find(" ");
    size_t sp2 = fulln.find(" ", sp1+1);

    name.f = fulln.substr(0, sp1);
    if(sp2 != string::npos) {
        name.m = fulln.substr(sp1+1, (sp2-sp1)-1);
        name.l = fulln.substr(sp2+1, fulln.size());
    }
    else
        name.l = fulln.substr(sp1+1, fulln.size());
    
    return cin;
}

istream& operator>>(istream& cin, QueryToType<float>& q) {
    while(!q.commandPrompt().good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return cin;
}

istream& operator>>(istream& cin, QueryToType<int>& q) {
    while(!q.commandPrompt().good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return cin;
}

//istream& operator>>(istream& cin, QueryToVector<float>& q) {
//    while(!q.prompt().good()) {
//        cin.clear();
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    }
//    return cin;
//}

Name::Name() : f(), m(), l() {}

const Name& Borrower::getName() const {
    return name;
}

const bool Name::operator!=(const Name& other) const {
    string ln = this->f + this->m + this->l;
    string rn = other.f + other.m + other.l;
    
    return ln != rn;
}

Borrower::Borrower() : name(Name()), monthlyDebts(0.f) {}

Borrower::Borrower(const Name& n) : name(n), monthlyDebts(0.f) {}

void Borrower::calcEarnings(float regRate) {
    earnings = Earnings(regRate);
}

const float Borrower::getMonthlyDebts() const{
    return monthlyDebts;
}

void Borrower::setMonthlyDebts(const float set) {
    monthlyDebts = set;
}

const float Borrower::getWeeklyEarnings() const {
    return earnings.getWeeklyGross();
}

const float Borrower::getYearlyEarnings() const {
    return earnings.getYearlyGross();
}

const float Borrower::getMonthlyEarnings() const {
    return earnings.getMonthlyGross();
}

const float Borrower::getHourlyRate() const {
    return earnings.getHrPayRate();
}

const bool Borrower::operator!=(const Borrower& other) {
    return this->getName() != other.getName();
}
