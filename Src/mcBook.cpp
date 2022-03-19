//
//  mcBook.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "wx/listctrl.h"
#include "mcBook.hpp"
#include "mcData.hpp"

mcBook::mcBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& sz) : wxNotebook(parent, id, pos, sz) {
    mOverview = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
    mReport = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
    mSchedule = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
    AddPage(mOverview, "Overview");
    AddPage(mReport, "Mortgage Report");
    AddPage(mSchedule, "Scheduled Payments");
}

const bool mcBook::update(mcData* data) {
//    cout << "mcBook::update" << endl;
    if(data != nullptr) {
        data->recalculateMortgage();
        wxString loan_str = wxString("Loan Amount: " + std::to_string((long)data->loanAmount));
        wxString int_str = wxString("Interest Percent: " + std::to_string((long)data->percentInterest) + "%");
        wxString term_str = wxString("Terms: " + std::to_string((long)data->termYears) + " years");
        
//        cout << "Monthly Principal & Interest: " << mCalculator::getMonthlyPrincipalAndInterest(loanAmount, termYears, percentInterest) << endl;
//        cout << "Property Taxes: " << mCalculator::getPropertyTax(purchasePrice) << endl;
//        cout << "Homeowners Insurance: " << mCalculator::getHomeOwnersInsurancePremium(purchasePrice) << endl;
//        cout << "Private Mortgage Insurance: " << mCalculator::getPrivateMortgageInsurance(loanAmount) << endl << endl;
//        cout << "Total Mortgage Payments: " << mCalculator::getMonthlyPayments(purchasePrice, loanAmount, termYears, percentInterest) << endl << endl;
        mOverview->ClearAll();
        mReport->ClearAll();
        mSchedule->ClearAll();
        
        mOverview->InsertItem(0, loan_str);
        mOverview->InsertItem(1, int_str);
        mOverview->InsertItem(2, term_str);
//        AddPage(mOverview, "Overview");
        
//        wxListView* mReport = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
        mReport->InsertItem(1, "Here be more dragons!");
//        AddPage(mReport, "Mortgage Report");
        
//        wxListView* mSchedule = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
        mSchedule->InsertItem(1, "Here be great dragons!");
//        AddPage(mSchedule, "Scheduled Payments");
        return true;
    }
    return false;
}
