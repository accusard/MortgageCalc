//
//  Currency.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Currency.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

FormatDollar::FormatDollar(const float value) {
    formattedString = "$";
    unformatted = value;
    dollar = unformatted;
    fractionDollar = unformatted - dollar;
}

const std::string FormatDollar::toString() {
    std::stringstream dollarStr, centStr;
    dollarStr << dollar;
    centStr << std::setprecision(2) << std::fixed << fractionDollar;
    
    unsigned long len = strlen(dollarStr.str().c_str());
    const int offset = len%3;
    
    for(int i = 0; i < len; ++i) {
        if(i%3 == offset && i) {
            formattedString += ',';
        }
        formattedString += dollarStr.str().at(i);
    }
    std::string newcent = centStr.str().erase(0,1);
    formattedString += newcent;
    
    return formattedString;
}
