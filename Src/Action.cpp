//
//  Action.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Menu.h"
#include "Action.hpp"

SequencePrompts::SequencePrompts(MortgageData& d) : MortgageData(d) {}

void SequencePrompts::addQuery(const string &prompt, float &data) {
    inquiriesFloat.push_back(QueryToType<float>(prompt, data));
}

void SequencePrompts::addQuery(const string &prompt, int &data) {
    inquriesInt.push_back(QueryToType<int>(prompt, data));
}

void SequencePrompts::addQuery(const string &prompt, vector<Borrower>& vRef) {
    inquiriesBorrower.push_back(QueryToVector<Borrower>(prompt, vRef));
}

void SequencePrompts::execute() {
    for(int i = 0; i < inquiriesFloat.size(); i++)
        cin >> inquiriesFloat[i];
    
   for(int i = 0; i < inquriesInt.size(); i++)
        cin >> inquriesInt[i];
    
   for(int i = 0; i < inquiriesBorrower.size(); i++)
        inquiriesBorrower[i].prompt();
   
   recalculateMortgage();
}

Loop::Loop(Menu* menu, void(Menu::*loopPtr)(), const char exit) : loop(loopPtr), stop(exit) {
    menuPtr = menu;
}

void Loop::execute() {
    while(menuPtr->inputFront() != stop) {
        (menuPtr->*loop)();
    }
}

void MortgageReport::execute() {
    
    recalculateMortgage();
    
    cout << endl;
    cout << "Borrower(s): ";
    for(auto b : Borrowers) {
        cout << b.getName().l << ", " << b.getName().f << " " << b.getName().m.front() << ".";
        if(b !=  Borrowers.back())
            cout << "; ";
    }

    cout << endl;
    cout << "Loan Amount: " << loanAmount << " : " << percentInterest << "% : " << termYears << "y" << endl;
    cout << "Monthly Principal & Interest: " << MortgageCalculator::getMonthlyPrincipalAndInterest(loanAmount, termYears, percentInterest) << endl;
    cout << "Property Taxes: " << MortgageCalculator::getPropertyTax(purchasePrice) << endl;
    cout << "Homeowners Insurance: " << MortgageCalculator::getHomeOwnersInsurancePremium(purchasePrice) << endl;
    cout << "Private Mortgage Insurance: " << MortgageCalculator::getPrivateMortgageInsurance(loanAmount) << endl << endl;
    cout << "Total Mortgage Payments: " << MortgageCalculator::getMonthlyPayments(purchasePrice, loanAmount, termYears, percentInterest) << endl << endl;
}

void AmortizationReport::execute() {
    
    int totalPayments = termYears * 12;
    float remainingBalance = loanAmount;
    float monthlyPayment = MortgageCalculator::getMonthlyPrincipalAndInterest(loanAmount, termYears, percentInterest);
    
    cout << "Payment : Principal : Interest : Balance\n";
    for(int i = 1; i <= totalPayments; i++) {
        float interestPaid = remainingBalance * toMonthlyInterestRate(percentInterest);
        float principalPaid = MortgageCalculator::getMonthlyPrincipalAndInterest(loanAmount, termYears, percentInterest) - interestPaid;
        remainingBalance -=  principalPaid;
        
        if(i == totalPayments && remainingBalance < 0) {
            principalPaid += remainingBalance;
            monthlyPayment = principalPaid + interestPaid;
//            remainingBalance = 0.f;
        }
        
        cout << i << " : ";
        cout << monthlyPayment << " : ";
        cout << principalPaid << " : ";
        cout << interestPaid << " : ";
        cout << remainingBalance << endl;
    }
}

void BorrowerReport::execute() {
    if(borrowers.size() != 0) {
        for(auto b : borrowers) {
            cout << "--- " << b.getName().f << " ---" << endl;
            cout << "Gross Weekly: $" << b.getWeeklyEarnings() << " - ";
            cout << "Gross Monthly: $" << b.getMonthlyEarnings() << " - ";
            cout << "Debts: $" << b.getMonthlyDebts() << "/month" << endl;
            cout << endl;
        }
    }
}

void DTIReport::execute() {
    
    recalculateMortgage();
    
    float totalMonthlyGross = (getTotalYearlyGross() /12);
    float monthlyMortgagePayment = MortgageCalculator::getMonthlyPayments(purchasePrice, loanAmount, termYears, percentInterest);
    float dti = (getTotalMonthlyDebts() + monthlyMortgagePayment) / totalMonthlyGross;
    float monthlyIncomeNeeded = ((getTotalMonthlyDebts() + monthlyMortgagePayment) / MortgageCalculator::DTI_RATIO);
    float otDays = ((getBorrowersPayRates() * 1.5) * 8) + ((getBorrowersPayRates() * 2.f) * 2); // based on 10 hr shifts
    float otDaysToCoverMortgage = ((monthlyIncomeNeeded-totalMonthlyGross ) * 12) / otDays;
    float cashAfterDebts = totalMonthlyGross - (getTotalMonthlyDebts() + monthlyMortgagePayment);
    
    
    cout << "Debt-To-Income ratio: " << ToPercent(dti) << "%" << endl;
    if(dti >= MortgageCalculator::DTI_RATIO) {
        float payRateNeeded = ((monthlyIncomeNeeded * 12) / 52) / 40;
        cout << "Payrate $" << getBorrowersPayRates() << "/hr " << endl;
        cout << "Additional income to meet " << ToPercent(MortgageCalculator::DTI_RATIO) << "% DTI: $" << monthlyIncomeNeeded-totalMonthlyGross << "/month" << endl;
        cout << "Overtime days per year required to cover mortgage: " << otDaysToCoverMortgage << endl;
        cout << "Gross remaining after debts $" << cashAfterDebts << "/month" << endl;
        cout << ".. or find a new job that pays $" << payRateNeeded << "/hr" << endl;
    } else {
        cout << "Congratulations! " << endl;
        cout << "Your combined payrates of $" << getBorrowersPayRates() << "/hr ";
        cout << "totaling $" << totalMonthlyGross << "/month meets the " << ToPercent(MortgageCalculator::DTI_RATIO) << "% dti ratio!" << endl;
        cout << "Total monthly gross remaining after debts $" << cashAfterDebts << endl;
        
        cout << ".. in which $" << totalMonthlyGross * (MortgageCalculator::DTI_RATIO - dti) << " can comfortably go towards other debts!" << endl;
        cout << ".. with a remainder of $" << totalMonthlyGross * (1.f - MortgageCalculator::DTI_RATIO) << endl;
    }
    
    cout << endl;
}

void Exit::execute() {
    cout << endl << "quitting.." << endl;
    exit(0);
}



