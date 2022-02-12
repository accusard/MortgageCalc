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

MortgageData::MortgageData(const float p, const float d, const int y, const float i) : purchasePrice(p), downpayment(d), termYears(y), percentInterest(i) {
    
    update(p, d);
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
    cout << "saving " << filename << endl;
    ofstream ofile(filename, ios::out|ios::binary|ios::trunc);
    
    if(ofile.is_open()) {
        for(auto map : makeHashTable()) {
            ofile << map.first <<":" << map.second << endl;
        }
        ofile.close();
    }
}

void MortgageData::load(const char* filename) {
    cout << "loading " << filename << endl;
    ifstream ifile(filename, ios::in|ios::binary);
    string line;
    if(ifile.is_open()) {
        // read each line 1 by 1 and add to variable
        while(getline(ifile,line))
        {
            unsigned long stopat = line.find(":");
            const string varName = line.substr(0, stopat);
            
            float *myFloatPtr = nullptr;
            
            // ewww
            if(varName == GET_VAR_NAME(percentDown)) myFloatPtr = &percentDown;
            else if(varName == GET_VAR_NAME(percentInterest)) myFloatPtr = &percentInterest;
            else if(varName == GET_VAR_NAME(termYears)) termYears = stoi(line.substr(stopat+1));
            else if(varName == GET_VAR_NAME(downpayments)) myFloatPtr = &downpayment;
            else if(varName == GET_VAR_NAME(loanAmount)) myFloatPtr = &loanAmount;
            else if(varName == GET_VAR_NAME(purchasePrice)) myFloatPtr = &purchasePrice;
            
            if(myFloatPtr != nullptr)
                *myFloatPtr = stof(line.substr(stopat+1));
        }
    }
    ifile.close();
}

void MortgageData::makeHash(const string& str, const float val) {
    dataHash.insert(make_pair(str, val));
}

const unordered_map<string, float>& MortgageData::makeHashTable() {
    makeHash(GET_VAR_NAME(purchasePrice), purchasePrice);
    makeHash(GET_VAR_NAME(loanAmount), loanAmount);
    makeHash(GET_VAR_NAME(downpayment), downpayment);
    makeHash(GET_VAR_NAME(termYears), termYears);
    makeHash(GET_VAR_NAME(percentInterest), percentInterest);
    makeHash(GET_VAR_NAME(percentDown),percentDown);
    return dataHash;
}
