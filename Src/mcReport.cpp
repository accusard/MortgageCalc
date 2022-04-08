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

FormatDollar::FormatDollar(const float value) {
    formattedString = "$";
    unformatted = value;
    dollar = unformatted;
    fractionDollar = unformatted - dollar;
}

const std::string FormatDollar::toString() {
    stringstream dollarStr, centStr;
    dollarStr << dollar;
    centStr << setprecision(2) << std::fixed << fractionDollar;
    
    unsigned long len = strlen(dollarStr.str().c_str());
    const int offset = len%3;
    
    for(int i = 0; i < len; ++i) {
        if(i%3 == offset && i) {
            formattedString += ',';
        }
        formattedString += dollarStr.str().at(i);
    }
    std::string newcent = centStr.str().erase(0,1);
    formattedString += newcent;
    
    return formattedString;
}

SummaryReport::SummaryReport(mcData& dataRef, wxListView* list, const int columnWidth) {
    dataRef.recalculateMortgage();
    
    // prints out the borrowers
//    std::string head("Borrower(s): ");
//    for(auto b : dataRef.Borrowers) {
//        head + b.getName().l + ", " + b.getName().f + " " + b.getName().m.front() + ".";
//        if(b !=  dataRef.Borrowers.back())
//            head + "; ";
//    }
//    mList.push(head);
    
    const float amount = dataRef.loanAmount;
    const int years = dataRef.termYears;
    const float interest = dataRef.percentInterest;
    const float purchase = dataRef.purchasePrice;
    
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
    
    list->AppendColumn("", wxLIST_FORMAT_LEFT, columnWidth);
    while(!mList.empty()) {
        wxString s = mList.front();
        list->InsertItem(0,s);
        mList.pop();
    }
}

MortgageReport::MortgageReport() {

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
        
        list->InsertItem(i, std::to_string(i));
        list->SetItem(i-1, 1, FormatDollar(monthlyPayment).toString());
        list->SetItem(i-1, 2, FormatDollar(towardPrincipal).toString());
        list->SetItem(i-1, 3, FormatDollar(towardInterest).toString());
        list->SetItem(i-1, 4, FormatDollar(balance).toString());
    }
}

BorrowersReport::BorrowersReport() {
    if(mBorrowers.size() != 0) {
        for(auto b : mBorrowers) {
            cout << "--- " << b.getName().f << " ---" << endl;
            cout << "Gross Weekly: $" << b.getWeeklyEarnings() << " - ";
            cout << "Gross Monthly: $" << b.getMonthlyEarnings() << " - ";
            cout << "Debts: $" << b.getMonthlyDebts() << "/month" << endl;
            cout << endl;
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
    
    
    cout << "Debt-To-Income ratio: " << ToPercent(dti) << "%" << endl;
    if(dti >= mCalculator::DTI_RATIO) {
        float payRateNeeded = ((monthlyIncomeNeeded * 12) / 52) / 40;
        cout << "Payrate $" << dRef.getBorrowersPayRates() << "/hr " << endl;
        cout << "Additional income to meet " << ToPercent(mCalculator::DTI_RATIO) << "% DTI: $" << monthlyIncomeNeeded-totalMonthlyGross << "/month" << endl;
        cout << "Overtime days per year required to cover mortgage: " << otDaysToCoverMortgage << endl;
        cout << "Gross remaining after debts $" << cashAfterDebts << "/month" << endl;
        cout << ".. or find a new job that pays $" << payRateNeeded << "/hr" << endl;
    } else {
        cout << "Congratulations! " << endl;
        cout << "Your combined payrates of $" << dRef.getBorrowersPayRates() << "/hr ";
        cout << "totaling $" << totalMonthlyGross << "/month meets the " << ToPercent(mCalculator::DTI_RATIO) << "% dti ratio!" << endl;
        cout << "Total monthly gross remaining after debts $" << cashAfterDebts << endl;
        
        cout << ".. in which $" << totalMonthlyGross * (mCalculator::DTI_RATIO - dti) << " can comfortably go towards other debts!" << endl;
        cout << ".. with a remainder of $" << totalMonthlyGross * (1.f - mCalculator::DTI_RATIO) << endl;
    }
}
