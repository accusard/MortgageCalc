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
    
}

const bool mcBook::load(mcData* data) {
    if(data != nullptr) {
        wxListView* ovrview = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
        wxString loan_str = wxString("Loan Amount: " + std::to_string((long)data->loanAmount));
        wxString int_str = wxString("Interest Percent: " + std::to_string((long)data->percentInterest) + "%");
        wxString term_str = wxString("Terms: " + std::to_string((long)data->termYears) + " years");
        
//        cout << "Monthly Principal & Interest: " << mCalculator::getMonthlyPrincipalAndInterest(loanAmount, termYears, percentInterest) << endl;
//        cout << "Property Taxes: " << mCalculator::getPropertyTax(purchasePrice) << endl;
//        cout << "Homeowners Insurance: " << mCalculator::getHomeOwnersInsurancePremium(purchasePrice) << endl;
//        cout << "Private Mortgage Insurance: " << mCalculator::getPrivateMortgageInsurance(loanAmount) << endl << endl;
//        cout << "Total Mortgage Payments: " << mCalculator::getMonthlyPayments(purchasePrice, loanAmount, termYears, percentInterest) << endl << endl;
        
        ovrview->InsertItem(0, loan_str);
        ovrview->InsertItem(1, int_str);
        ovrview->InsertItem(2, term_str);
        AddPage(ovrview, "Overview");
        
        wxListView* mrtgrpt = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
        mrtgrpt->InsertItem(1, "Here be more dragons!");
        AddPage(mrtgrpt, "Mortgage Report");
        
        wxListView* sch = new wxListView(this, wxID_ANY, wxDefaultPosition, GetSize(), wxLC_LIST);
        sch->InsertItem(1, "Here be great dragons!");
        AddPage(sch, "Scheduled Payments");
        return true;
    }
    return false;
}

//void mcBook::bind(
