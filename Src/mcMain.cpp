//
//  mcMain.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcMain.hpp"
#include "Action.hpp"


wxBEGIN_EVENT_TABLE(mcMain, wxFrame)
    EVT_BUTTON(NEW_LOAN_BTN_ID, mcMain::OnButtonClicked)
    EVT_BUTTON(UPDATE_LOAN_BTN_ID, mcMain::OnButtonClicked)
    EVT_BUTTON(PRINT_REPORT_BTN_ID, mcMain::OnButtonClicked)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxFrame(nullptr, wxID_ANY, "Mortgage Calculator", wxPoint(50,50), wxSize(640,480)) {
    
    btns.push_back(newButton(NEW_LOAN_BTN_ID, "New Loan"));
    btns.push_back(newButton(UPDATE_LOAN_BTN_ID, "Update Loan"));
    btns.push_back(newButton(PRINT_REPORT_BTN_ID, "Print Report"));
    
    list = new wxListBox(this, wxID_ANY, wxPoint(200,10), wxSize(300,300));
    // wxMenu: create menu list
}

mcMain::~mcMain() {
    for(auto btn : btns) {
        if(btn != nullptr)
            delete btn;
    }
}

wxButton* mcMain::newButton(const int btnId, const wxString& label) {
    const unsigned int vpos = (int)btns.size()*50 + 10;
    return new wxButton(this, btnId, label, wxPoint(10, vpos), wxSize(150,50));
}

void mcMain::OnButtonClicked(wxCommandEvent &evt) {
    int btnId = evt.GetId();
    
    switch (btnId) {
        case NEW_LOAN_BTN_ID:
        {
            list->AppendString("Create a new loan");
            MortgageData loan;
            SequencePrompts loanPrompts(loan);
            
            loanPrompts.addQuery("Enter the purchase price of the home - ", loan.purchasePrice);
            loanPrompts.addQuery("Enter the downpayment for this home - ", loan.downpayment);
            loanPrompts.addQuery("Enter the number of term in years - ", loan.termYears);
            
            break;
        }
        case UPDATE_LOAN_BTN_ID:
            list->AppendString("Update an existing loan");
            break;
            
        case PRINT_REPORT_BTN_ID:
            list->AppendString("Which report?");
            break;
    }
    
//    evt.Skip();
}

