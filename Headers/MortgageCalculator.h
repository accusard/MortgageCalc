//
//  MortgageCalculator.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef MortgageCalculator_h
#define MortgageCalculator_h

#define GET_VAR_NAME(var) (#var)
#define MAKE_HASH(name) hash.insert_or_assign(GET_VAR_NAME(name),name)

#include <cmath>
#include <unordered_map>
#include "mcFile.hpp"
#include "IDataFileInterface.h"
#include "QueryData.hpp"
#include "Borrower.h"

using namespace std;

const float ToPercent(const float decimal);
const float toMonthlyInterestRate(const float interestPerc);

struct MortgageData : public IDataFileInterface {
    MortgageData();
    virtual ~MortgageData() {}
    MortgageData(const float purchse, const float down, const int years, const float interestPerc);
    
    void recalculateMortgage();
    void update(float homePrice, float downPayment);
    
    const float getWeeklyGross(const Borrower& b) const;
    const float getYearlyGross(const Borrower& b) const;
    const float getTotalYearlyGross() const;
    const float getTotalMonthlyDebts() const;
    const float getBorrowersPayRates() const;
    
    void setPurchasePrice(const float price);
    void setDownpayment(const float down);
    void setTerms(const int years);
    void setInterest(const float percent);
    
    // the home's purchase price
    float purchasePrice;
    // the loan amount
    float loanAmount;
    
public:
    float downpayment;
    float termYears;
    float percentInterest;
    float percentDown;
    vector<Borrower> Borrowers;
    
    virtual void makeHashTable(std::unordered_map<std::string, float>& hash) override;
    
    
    
};

struct MortgageCalculator {
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

#endif /* MortgageCalculator_h */
