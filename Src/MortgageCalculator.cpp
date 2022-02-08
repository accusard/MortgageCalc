//
//  MortgageCalculator.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "MortgageCalculator.h"
#include <iostream>

const float ToPercent(const float decimal)
{
   return decimal / 0.01f;
}

const float toMonthlyInterestRate(const float annualInterest) {
    float interestRate = annualInterest * 0.01f / 12;
    return interestRate;
}

MortgageData::MortgageData(const float p, const float d, const int y, const float i) : purchasePrice(p), downpayment(d), termYears(y), percentInterest(i) {
    
    update();
}

void MortgageData::update() {
    percentDown = downpayment / purchasePrice;
    loanAmount = purchasePrice - downpayment;
}

const float MortgageData::getWeeklyGross(const Borrower& b) const{
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


