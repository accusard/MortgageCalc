//
//  MortgageCalculator.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "MortgageCalculator.h"
#include "DataFile.hpp"
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
    makeHashTable(File);
}

MortgageData::MortgageData(const float p, const float d, const int y, const float i) : termYears(y), percentInterest(i) {
    
    update(p, d);
    makeHashTable(File);

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

unordered_map<string, float>& MortgageData::makeHashTable(DataFile& file) {
    
    file.dataHash.insert(make_pair(GET_VAR_NAME(purchasePrice), purchasePrice));
    
//    MAKE_HASH(loanAmount);
//    MAKE_HASH(downpayment);
//    MAKE_HASH(termYears);
//    MAKE_HASH(percentInterest);
//    MAKE_HASH(percentDown);
    
    return file.dataHash;
}
