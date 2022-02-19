//
//  mCalculator.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef MortgageCalculator_h
#define MortgageCalculator_h

//#include <cmath>
//#include <unordered_map>
//#include "mcFile.hpp"
//#include "IDataFileInterface.h"
//#include "QueryData.hpp"
//#include "Borrower.h"

const float ToPercent(const float decimal) { return decimal / 0.01f; }
const float toMonthlyInterestRate(const float interestPerc) {
    float interestRate = interestPerc * 0.01f / 12;
    return interestRate;
}

struct mCalculator {
    static constexpr float PROPERTY_TAX_RATE = 0.00105714f;
    static constexpr float HOMEOWNER_INSURANCE_TAX_RATE = 0.000333343f;
    static constexpr float PMI_TAX_RATE = 0.000625f;
    static constexpr float DTI_RATIO = 0.43f;
    
    static const float getMonthlyPrincipalAndInterest(const float loanAmount, const int loanTermYears, const float interestPercent) {
        float interestRate = getMonthlyInterestRate(interestPercent);
        float powFormula = pow((1+interestRate), (loanTermYears * 12));
        return (loanAmount * interestRate * powFormula) / (powFormula - 1);
        
    }
    
    static const float getMonthlyInterestRate(const float i) {
        return toMonthlyInterestRate(i);
    }
    
    static const float getPropertyTax(const float purchasePrice) {
        return purchasePrice * PROPERTY_TAX_RATE;
    }
    
    static const float getHomeOwnersInsurancePremium(const float purchasePrice) {
        return purchasePrice * HOMEOWNER_INSURANCE_TAX_RATE;
    }
    
    static const float getPrivateMortgageInsurance(const float loanAmt) {
        return loanAmt * PMI_TAX_RATE;
    }
    
    static const float getMonthlyPayments(const float purchasePrice, const float loanAmount, const int loanTermYears, const float interestPercent) {
        float monthlyPrincipalAndInterest = getMonthlyPrincipalAndInterest(loanAmount, loanTermYears, interestPercent);
        float propertyTax = getPropertyTax(purchasePrice);
        float homeOwnersInsurance = getHomeOwnersInsurancePremium(purchasePrice);
        float privateMortgageInsurance = getPrivateMortgageInsurance(loanAmount);
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

#endif /* mCalculator_h */
