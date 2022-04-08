//
//  Currency.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Currency_hpp
#define Currency_hpp

class FormatDollar  {
public:
    FormatDollar(const float val);
    const std::string toString();
    
protected:
    std::string formattedString;
    int dollar;
    float fractionDollar;
    float unformatted;
    
};

#endif /* Currency_hpp */
