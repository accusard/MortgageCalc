//
//  mcData.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcData.hpp"
#include "Borrower.h"

mcData::mcData() : purchasePrice(400000.f), loanAmount(0.f), downpayment(40000.f),
termYears(30.f), percentInterest(4.f), percentDown(0.f) {
    recalculateMortgage();
}

mcData::mcData(const float p, const float d, const int y, const float i) : termYears(y), percentInterest(i) {
    update(p, d);
}

void mcData::recalculateMortgage() {
    percentDown = downpayment / purchasePrice;
    loanAmount = purchasePrice - downpayment;
}

void mcData::update(float price, float down) {
    purchasePrice = price;
    downpayment = down;
    recalculateMortgage();
}

const float mcData::getWeeklyGross(const Borrower& b) const {
    return b.getWeeklyEarnings();
}

const float mcData::getYearlyGross(const Borrower& b) const {
    return b.getYearlyEarnings();
}

const float mcData::getTotalYearlyGross() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getYearlyEarnings();
        }
    }
    return total;
}

const float mcData::getTotalMonthlyDebts() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getMonthlyDebts();
        }
    }
    return total;
}

const float mcData::getBorrowersPayRates() const{
    float total{0};
    if(Borrowers.size() != 0) {
        for(auto b : Borrowers) {
            total += b.getHourlyRate();
        }
    }
    return total;
}

void mcData::setPurchasePrice(const float price) {
    update(price, downpayment);
}

void mcData::setDownpayment(const float down) {
    update(purchasePrice, down);
}

void mcData::setTerms(const int years) {
    termYears = years;
    recalculateMortgage();
}

void mcData::setInterest(const float percent) {
    percentInterest = percent;
    recalculateMortgage();
}

void mcData::makeHashTable(std::unordered_map<std::string, float>& hash) {
    MAKE_HASH(purchasePrice);
    MAKE_HASH(loanAmount);
    MAKE_HASH(downpayment);
    MAKE_HASH(termYears);
    MAKE_HASH(percentInterest);
    MAKE_HASH(percentDown);
}

vector<mcDialogPrompt<float>> mcData::getFieldEntries() {
    vector<mcDialogPrompt<float>> entrylist;
    entrylist.push_back(mcDialogPrompt<float>("Purchase Price", purchasePrice, MAX_DOLLAR_AMOUNT));
    entrylist.push_back(mcDialogPrompt<float>("Interest", percentInterest, 100));
    entrylist.push_back(mcDialogPrompt<float>("Downpayment", downpayment, MAX_DOLLAR_AMOUNT));
    entrylist.push_back(mcDialogPrompt<float>("Years", termYears, 45));
    return entrylist;
}

mcDialogPrompt<float> mcData::getFieldEntry(const int index) {
    return getFieldEntries()[index];
}
