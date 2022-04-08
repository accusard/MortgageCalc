//
//  mcReport.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcReport.hpp"
#include "mcData.hpp"
#include "mCalculator.h"
#include "Currency.hpp"
#include "wx/listctrl.h"
#include <iostream>
#include <sstream>
#include <iomanip>


void ReportList::print(wxListView* target) {
    while(!mList.empty()) {
        wxString s = mList.front();
        target->InsertItem(0,s);
        mList.pop();
    }
}

SummaryReport::SummaryReport(mcData& dataRef, wxListView* list) {
    dataRef.recalculateMortgage();
    
    // prints out the borrowers
    if(!dataRef.Borrowers.empty()) {
        std::string head("Borrower(s): ");
        for(auto b : dataRef.Borrowers) {
            head + b.getName().l + ", " + b.getName().f + " " + b.getName().m.front() + ".";
            if(b !=  dataRef.Borrowers.back())
                head + "; ";
        }
        mList.push(head);
    }
    
    const float amount = dataRef.loanAmount;
    const int years = dataRef.termYears;
    const float interest = dataRef.percentInterest;
    const float purchase = dataRef.purchasePrice;
    const int colWidth = 500;
    stringstream intStr;
    intStr << setprecision(2) << std::fixed << dataRef.percentInterest;
    
    mList.push("\n");
    mList.push("Loan Amount: " + FormatDollar(amount).toString() + " at " + intStr.str() + "% for " + std::to_string(years) + " years" + "\n");
    mList.push("\n");
    mList.push("  Monthly Principal & Interest: " + FormatDollar(mCalculator::getMonthlyPrincipalAndInterest(amount, years, interest)).toString() + "\n");
    mList.push("  Property Taxes: " + FormatDollar(mCalculator::getPropertyTax(purchase)).toString() + "\n");
    mList.push("  Homeowners Insurance: " + FormatDollar(mCalculator::getHomeOwnersInsurancePremium(purchase)).toString() + "\n");
    mList.push("  Private Mortgage Insurance: " + FormatDollar(mCalculator::getPrivateMortgageInsurance(amount)).toString() + "\n" + "\n");
    mList.push("Total Monthly Payments: " + FormatDollar(mCalculator::getMonthlyPayments(purchase, amount, years, interest)).toString() + "\n" + "\n");
    
    list->AppendColumn("", wxLIST_FORMAT_LEFT, colWidth);
    
    print(list);
}

MortgageReport::MortgageReport(mcData& dref, wxListView* list) {
    list->AppendColumn("", wxLIST_FORMAT_LEFT, 500);
    if(!dref.Borrowers.empty()) {
        dref.Borrowers.clear();
    }
    Borrower b1 = Borrower(Name("Vanny"));
    b1.calcEarnings(18.30f);
    b1.setMonthlyDebts(150.f);
    dref.Borrowers.push_back(b1);
    
    Borrower b2 = Borrower(Name("Charann"));
    b2.calcEarnings(19.f);
    b2.setMonthlyDebts(250.f);
    dref.Borrowers.push_back(b2);
    
    DTIReport dtiReport = DTIReport(dref);
    dtiReport.print(list);
    
    SummaryReport(dref, list);
    BorrowersReport bReport = BorrowersReport(dref.Borrowers);
    bReport.print(list);

}

AmortizationReport::AmortizationReport(mcData& dref, wxListView* list) {
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
        
        list->InsertItem(i, std::to_string(i));
        list->SetItem(i-1, 1, FormatDollar(monthlyPayment).toString());
        list->SetItem(i-1, 2, FormatDollar(towardPrincipal).toString());
        list->SetItem(i-1, 3, FormatDollar(towardInterest).toString());
        list->SetItem(i-1, 4, FormatDollar(balance).toString());
    }
}

BorrowersReport::BorrowersReport(std::vector<struct Borrower> borrowers) : mBorrowers(borrowers){
    if(borrowers.size() != 0) {
        for(auto b : mBorrowers) {
            mList.push("\n");
            mList.push("Debts: " + FormatDollar(b.getMonthlyDebts()).toString() + "/month" + "\n");
            mList.push("Gross Monthly: " + FormatDollar(b.getMonthlyEarnings()).toString());
            mList.push("Gross Weekly: " + FormatDollar(b.getWeeklyEarnings()).toString());
            mList.push("Hourly Rate: " + FormatDollar(b.getHourlyRate()).toString());
            mList.push("--- " + b.getName().f + " ---" + "\n");
        }
    }
}

DTIReport::DTIReport(mcData& dRef) {
    dRef.recalculateMortgage();
    
    float totalMonthlyGross = (dRef.getTotalYearlyGross() /12);
    float monthlyMortgagePayment = mCalculator::getMonthlyPayments(dRef.purchasePrice, dRef.loanAmount, dRef.termYears, dRef.percentInterest);
    float dti = (dRef.getTotalMonthlyDebts() + monthlyMortgagePayment) / totalMonthlyGross;
    float monthlyIncomeNeeded = ((dRef.getTotalMonthlyDebts() + monthlyMortgagePayment) / mCalculator::DTI_RATIO);
    float otDays = ((dRef.getBorrowersPayRates() * 1.5) * 8) + ((dRef.getBorrowersPayRates() * 2.f) * 2); // based on 10 hr shifts
    float otDaysToCoverMortgage = ((monthlyIncomeNeeded-totalMonthlyGross ) * 12) / otDays;
    float cashAfterDebts = totalMonthlyGross - (dRef.getTotalMonthlyDebts() + monthlyMortgagePayment);
    stringstream sdti, sdtiCur;
    sdti << setprecision(2) << std::fixed << ToPercent(mCalculator::DTI_RATIO);
    sdtiCur << setprecision(2) << std::fixed << ToPercent(dti);
    
    if(dti >= mCalculator::DTI_RATIO) {
        float payRateNeeded = ((monthlyIncomeNeeded * 12) / 52) / 40;
        mList.push(".. or find a new job that pays " + FormatDollar(payRateNeeded).toString() + "/hr" + "\n");
        mList.push("Gross remaining after debts " + FormatDollar(cashAfterDebts).toString() + "/month" + "\n");
        mList.push("Overtime days per year required to cover mortgage: " + std::to_string(otDaysToCoverMortgage) + "\n");
        mList.push("Additional income to meet " + sdti.str() + "% DTI: " + FormatDollar(monthlyIncomeNeeded-totalMonthlyGross).toString() + "/month" + "\n");
        mList.push("Payrate " + FormatDollar(dRef.getBorrowersPayRates()).toString() + "/hr " + "\n");
    } else {
        mList.push(".. with a remainder of " + FormatDollar(totalMonthlyGross * (1.f - mCalculator::DTI_RATIO)).toString() + "\n");
        mList.push(".. in which " + FormatDollar(totalMonthlyGross * (mCalculator::DTI_RATIO - dti)).toString() + " can comfortably go towards other debts!" + "\n");
        mList.push("Total monthly gross remaining after debts " + FormatDollar(cashAfterDebts).toString() + "\n");
        mList.push("totaling " + FormatDollar(totalMonthlyGross).toString() + "/month meets the " + sdti.str() + "% dti ratio!" + "\n");
        mList.push("Your combined payrates of " + FormatDollar(dRef.getBorrowersPayRates()).toString() + "/hr ");
        mList.push("Congratulations! ");
    }
    mList.push("Debt-To-Income ratio: " + sdtiCur.str() + "%" + "\n");
}
