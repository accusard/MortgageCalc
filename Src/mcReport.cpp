//
//  mcReport.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcReport.hpp"
#include "mcData.hpp"
#include "mCalculator.h"
#include "wx/listctrl.h"
#include <iostream>
#include <sstream>
#include <iomanip>

MortgageReport::MortgageReport(mcData& dRef) {
    dRef.recalculateMortgage();
    mFormattedReport = "Borrower(s): ";
    for(auto b : dRef.Borrowers) {
        mFormattedReport + b.getName().l + ", " + b.getName().f + " " + b.getName().m.front() + ".";
        if(b !=  dRef.Borrowers.back())
            mFormattedReport + "; ";
    }
    const float amount = dRef.loanAmount;
    const int years = dRef.termYears;
    const float interest = dRef.percentInterest;
    const float purchase = dRef.purchasePrice;
    
    mFormattedReport += "\n";
    mFormattedReport += "Loan Amount: " + std::to_string(amount) + " : " + std::to_string(interest) + "% : " + std::to_string(years) + "y" + "\n";
    mFormattedReport += "Monthly Principal & Interest: " + std::to_string(mCalculator::getMonthlyPrincipalAndInterest(amount, years, interest)) + "\n";
    mFormattedReport += "Property Taxes: " + std::to_string(mCalculator::getPropertyTax(purchase)) + "\n";
    mFormattedReport += "Homeowners Insurance: " + std::to_string(mCalculator::getHomeOwnersInsurancePremium(purchase)) + "\n";
    mFormattedReport += "Private Mortgage Insurance: " + std::to_string(mCalculator::getPrivateMortgageInsurance(amount)) + "\n" + "\n";
    mFormattedReport += "Total Mortgage Payments: " + std::to_string(mCalculator::getMonthlyPayments(purchase, amount, years, interest)) + "\n" + "\n";

}

void AmortizationReport::format(mcData& dref, wxListView* list) {
    
    list->AppendColumn(" ");
    list->AppendColumn("Payment");
    list->AppendColumn("Principal");
    list->AppendColumn("Interest");
    list->AppendColumn("Balance", wxLIST_FORMAT_LEFT, 100);
    
    const int months = dref.termYears * 12;
    float balance = dref.loanAmount;
    float monthlyPayment = mCalculator::getMonthlyPrincipalAndInterest(dref.loanAmount, dref.termYears, dref.percentInterest);
    float integral;
    const float remainingPayFaction = modf(monthlyPayment, &integral);
    monthlyPayment -= remainingPayFaction;
    
    for(int i = 1; i <= months; i++) {
        float towardInterest = balance * toMonthlyInterestRate(dref.percentInterest);
        float towardPrincipal = mCalculator::getMonthlyPrincipalAndInterest(dref.loanAmount, dref.termYears, dref.percentInterest) - towardInterest - remainingPayFaction;
        balance -=  towardPrincipal;
        
        if(i == months) {
            towardPrincipal += balance;
            monthlyPayment = towardPrincipal + towardInterest;
            balance = 0.f;
        }
        
        std::stringstream s1,s2,s3,s4;
        list->InsertItem(i, std::to_string(i));
        
        s1 << "$" << setprecision(2) << std::fixed << monthlyPayment;
        list->SetItem(i-1, 1, s1.str());
        
        s2 << "$" << setprecision(2) << std::fixed << towardPrincipal;
        list->SetItem(i-1, 2, s2.str());
        
        s3 << "$" << setprecision(2) << std::fixed << towardInterest;
        list->SetItem(i-1, 3, s3.str());
        
        s4 << "$" << setprecision(2) << std::fixed << balance;
        list->SetItem(i-1, 4, s4.str());
    }
}


