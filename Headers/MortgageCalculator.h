//
//  MortgageCalculator.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef MortgageCalculator_h
#define MortgageCalculator_h
#include <string>
#include <vector>
#include <cmath>
#include "QueryData.hpp"
#include "Borrower.h"

using namespace std;

const float formatToInterest(const float i);

const float toMonthlyInterestRate(const float interest);

struct MortgageData {
    MortgageData(const float purchse, const float down, const int years, const float interest);
    
    void update();
    const float getWeeklyGross(const Borrower& b) const;
    const float getYearlyGross(const Borrower& b) const;
    const float getTotalYearlyGross() const;
    const float getTotalMonthlyDebts() const;
    const float getBorrowersPayRates() const;
    
    // the home's purchase price
    float purchase;
    
    float downpayment;
    
    int termYears;
    
    float interest;
    
    float downPercentage;
    
    // the loan amount
    float amount;
    
    vector<Borrower> Borrowers;
};

struct MortgageCalculator {
    static constexpr float PROPERTY_TAX_RATE = 0.00105714f;
    static constexpr float HOMEOWNER_INSURANCE_TAX_RATE = 0.000333343f;
    static constexpr float PMI_TAX_RATE = 0.000625f;
    static constexpr float DTI_RATIO = 0.43f;
    
    static const float getMonthlyPrincipalAndInterest(const MortgageData& loan) {
        float interestRate = getMonthlyInterestRate(loan.interest);
        float powFormula = pow((1+interestRate), (loan.termYears*12));
        return (loan.amount * interestRate * powFormula) / (powFormula - 1);
        
    }
    
    static const float getMonthlyInterestRate(const float i) {
        return toMonthlyInterestRate(i);
    }
    
    static const float getPropertyTax(const MortgageData& loan) {
        return loan.purchase * PROPERTY_TAX_RATE;
    }
    
    static const float getHomeOwnersInsurancePremium(const MortgageData& loan) {
        return loan.purchase * HOMEOWNER_INSURANCE_TAX_RATE;
    }
    
    static const float getPrivateMortgageInsurance(const MortgageData& loan) {
        return loan.amount * PMI_TAX_RATE;
    }
    
    static const float getMonthlyPayments(const MortgageData& loan) {
        float monthlyPrincipalAndInterest = getMonthlyPrincipalAndInterest(loan);
        float propertyTax = getPropertyTax(loan);
        float homeOwnersInsurance = getHomeOwnersInsurancePremium(loan);
        float privateMortgageInsurance = getPrivateMortgageInsurance(loan);
        float monthlyPayments = monthlyPrincipalAndInterest + propertyTax + homeOwnersInsurance + privateMortgageInsurance;
        
        return  monthlyPayments;
    }
    
public:
    // helper functions to get the rate based on given tax/premium data
    static const float calcPropertyTaxRate(const float purchase, const float tax = 370.f) {
        return tax / purchase;
    }
    
    static const float calcHomeOwnersInsuranceRate(const float purchase, const float premium = 116.67f) {
        return premium / purchase;
    }
    
    static const float calcPrivateMortgageInsuranceRate(const float loan, const float premium = 94.5f) {
        return premium / loan;
    }
};

#endif /* MortgageCalculator_h */
