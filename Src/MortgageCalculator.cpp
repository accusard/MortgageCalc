//
//  MortgageCalculator.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "MortgageCalculator.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

const float ToPercent(const float decimal)
{
   return decimal / 0.01f;
}

const float toMonthlyInterestRate(const float annualInterest) {
    float interestRate = annualInterest * 0.01f / 12;
    return interestRate;
}

MortgageData::MortgageData() : purchasePrice(400000.f), loanAmount(0.f), downpayment(40000.f),
termYears(30.f), percentInterest(4.f), percentDown(0.f) {
    recalculateMortgage();
    makeHashTable();
}

MortgageData::MortgageData(const float p, const float d, const int y, const float i) : termYears(y), percentInterest(i) {
    
    update(p, d);
    makeHashTable();

}

void MortgageData::recalculateMortgage() {
    percentDown = downpayment / purchasePrice;
    loanAmount = purchasePrice - downpayment;
}

void MortgageData::update(float price, float down) {
    purchasePrice = price;
    downpayment = down;
    recalculateMortgage();
}

const float MortgageData::getWeeklyGross(const Borrower& b) const {
    return b.getWeeklyEarnings();
}

const float MortgageData::getYearlyGross(const Borrower& b) const {
    return b.getYearlyEarnings();
}

const float MortgageData::getTotalYearlyGross() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getYearlyEarnings();
        }
    }
    return total;
}

const float MortgageData::getTotalMonthlyDebts() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getMonthlyDebts();
        }
    }
    return total;
}

const float MortgageData::getBorrowersPayRates() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getHourlyRate();
        }
    }
    return total;
}

void MortgageData::save(const char* filename) {
    cout << "saving " << filename << endl << endl;
    ofstream ofile(filename, ios::out|ios::trunc);
    
    if(ofile.is_open()) {
        for(auto map : makeHashTable()) {
            ofile << map.first <<":" << map.second << endl;
        }
        ofile.close();
    }
}

void MortgageData::load(const char* filename) {
    cout << "loading " << filename << endl << endl;
    ifstream ifile(filename, ios::in);
    
    if(ifile.is_open()) {
        // read each line 1 by 1 and add to variable
        string line;
        while(getline(ifile,line))
        {
            readFrom(line);
        }
        ifile.close();
    }
}

void MortgageData::setPurchasePrice(const float price) {
    update(price, downpayment);
}

void MortgageData::setDownpayment(const float down) {
    update(purchasePrice, down);
}

void MortgageData::setTerms(const int years) {
    termYears = years;
}

void MortgageData::setInterest(const float percent) {
    percentInterest = percent;
}

void MortgageData::insert(const string& str, const float val) {
    dataHash.insert(make_pair(str, val));
}

const unordered_map<string, float>& MortgageData::makeHashTable() {
    MAKE_HASH(purchasePrice);
    MAKE_HASH(loanAmount);
    MAKE_HASH(downpayment);
    MAKE_HASH(termYears);
    MAKE_HASH(percentInterest);
    MAKE_HASH(percentDown);
    
    return dataHash;
}

void MortgageData::readFrom(const string& inLine) {
    
    unsigned long stopat = inLine.find(":");
    const string& varname = inLine.substr(0, stopat);
    
    for(auto map : dataHash)
    {
        if((map.first.compare(varname) == 0)) {
            map.second = stof(inLine.substr(stopat+1));
            return;
        }


    }
}
