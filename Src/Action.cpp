//
//  Action.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include "Menu.h"
#include "Action.hpp"

SequencePrompts::SequencePrompts(MortgageData& d) : dataRef(d) {}

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
   
   dataRef.update();
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
    
    data.update();
    
    cout << endl;
    cout << "Borrower(s): ";
    for(auto b : data.Borrowers) {
        cout << b.getName().l << ", " << b.getName().f << " " << b.getName().m.front() << ".";
        if(b !=  data.Borrowers.back())
            cout << "; ";
    }

    cout << endl;
    cout << "Loan Amount: " << data.amount << " : " << data.interest << "% : " << data.termYears << "y" << endl;
    cout << "Monthly Principal & Interest: " << MortgageCalculator::getMonthlyPrincipalAndInterest(data) << endl;
    cout << "Property Taxes: " << MortgageCalculator::getPropertyTax(data) << endl;
    cout << "Homeowners Insurance: " << MortgageCalculator::getHomeOwnersInsurancePremium(data) << endl;
    cout << "Private Mortgage Insurance: " << MortgageCalculator::getPrivateMortgageInsurance(data) << endl << endl;
    cout << "Total Mortgage Payments: " << MortgageCalculator::getMonthlyPayments(data) << endl << endl;
}

void BorrowerReport::execute() {
    if(data.size() != 0) {
        for(auto b : data) {
            cout << "--- " << b.getName().f << " ---" << endl;
            cout << "Gross Weekly: $" << b.getWeeklyEarnings() << " - ";
            cout << "Gross Monthly: $" << b.getMonthlyEarnings() << " - ";
            cout << "Debts: $" << b.getMonthlyDebts() << "/month" << endl;
            cout << endl;
        }
    }
}

void DTIReport::execute() {
    
    data.update();
    
    float totalMonthlyGross = (data.getTotalYearlyGross() /12);
    float monthlyMortgagePayment = MortgageCalculator::getMonthlyPayments(data);
    float dti = (data.getTotalMonthlyDebts() + monthlyMortgagePayment) / totalMonthlyGross;
    float monthlyIncomeNeeded = ((data.getTotalMonthlyDebts() + monthlyMortgagePayment) / MortgageCalculator::DTI_RATIO);
    float otDays = ((data.getBorrowersPayRates() * 1.5) * 8) + ((data.getBorrowersPayRates() * 2.f) * 2); // based on 10 hr shifts
    float otDaysToCoverMortgage = ((monthlyIncomeNeeded-totalMonthlyGross ) * 12) / otDays;
    float cashAfterDebts = totalMonthlyGross - (data.getTotalMonthlyDebts() + monthlyMortgagePayment);
    
    
    cout << "Debt-To-Income ratio: " << formatToInterest(dti) << "%" << endl;
    if(dti >= MortgageCalculator::DTI_RATIO) {
        float payRateNeeded = ((monthlyIncomeNeeded * 12) / 52) / 40;
        cout << "Payrate $" << data.getBorrowersPayRates() << "/hr " << endl;
        cout << "Additional income to meet " << formatToInterest(MortgageCalculator::DTI_RATIO) << "% DTI: $" << monthlyIncomeNeeded-totalMonthlyGross << "/month" << endl;
        cout << "Overtime days per year required to cover mortgage: " << otDaysToCoverMortgage << endl;
        cout << "Gross remaining after debts $" << cashAfterDebts << "/month" << endl;
        cout << ".. or find a new job that pays $" << payRateNeeded << "/hr" << endl;
    } else {
        cout << "Congratulations! " << endl;
        cout << "Your combined payrates of $" << data.getBorrowersPayRates() << "/hr ";
        cout << "totaling $" << totalMonthlyGross << "/month meets the " << formatToInterest(MortgageCalculator::DTI_RATIO) << "% dti ratio!" << endl;
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



