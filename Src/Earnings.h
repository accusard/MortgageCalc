//
//  Earnings.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef Earnings_hpp
#define Earnings_hpp

class Earnings {
    
public:
    Earnings();
    explicit Earnings(float regRate);
    
    const float getWeeklyGross() const;
    const float getYearlyGross() const;
    const float getMonthlyGross() const;
    const float getHrPayRate() const;
    
private:
    float hrPayRate;
    float yearlyGross;
    float weeklyGross;
    float monthlyGross;
};

#endif /* Earnings_hpp */
