//
//  Earnings.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Earnings.h"

Earnings::Earnings() : hrPayRate(0.f), yearlyGross(0), weeklyGross(0), monthlyGross(0) {}

Earnings::Earnings(float regRate) : hrPayRate(regRate) {

    weeklyGross = regRate * 40;
    yearlyGross = weeklyGross * 52;
    monthlyGross = yearlyGross /12;
    
}

const float Earnings::getWeeklyGross() const {
    return weeklyGross;
    
}
const float Earnings::getYearlyGross() const {
    return yearlyGross;
    
}
const float Earnings::getMonthlyGross() const {
    return monthlyGross;
    
}
const float Earnings::getHrPayRate() const {
    return hrPayRate;
}
