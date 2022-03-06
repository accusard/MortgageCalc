//
//  mcData.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcData_hpp
#define mcData_hpp

#define GET_VAR_NAME(var) (#var)
#define MAKE_HASH(name) hash.insert_or_assign(GET_VAR_NAME(name),name)


#include "IHashTableInterface.h"
#include "FieldEntriesInterface.h"
#include "QueryData.hpp"
#include "mcAction.hpp"

struct mcData : public IHashTableInterface, public IFieldEntriesInterface<mcDialogPrompt<float>> {
    mcData();
    virtual ~mcData() {}
    mcData(const float purchse, const float down, const int years, const float interestPerc);
    
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
    std::vector<Borrower> Borrowers;
    
    virtual void makeHashTable(std::unordered_map<std::string, float>& hash) override;
    virtual std::vector<mcDialogPrompt<float>> getFieldEntries() override;
    mcDialogPrompt<float> getFieldEntry(const int index);
    
    
};

#endif /* mcData_hpp */
