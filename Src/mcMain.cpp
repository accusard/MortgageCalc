//
//  mcMain.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcMain.hpp"
#include "Action.hpp"
#include "eventId.h"

wxBEGIN_EVENT_TABLE(mcMain, wxMDIParentFrame)
    EVT_BUTTON(NEW_LOAN_BTN_ID, mcMain::OnButtonClicked)
    EVT_BUTTON(UPDATE_LOAN_BTN_ID, mcMain::OnButtonClicked)
    EVT_BUTTON(PRINT_REPORT_BTN_ID, mcMain::OnButtonClicked)
//    EVT_MENU(MnuEventID::NEW, mcMain::OnNewMenu)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Mortgage Calculator", wxPoint(50,50), wxSize(640,480)) {
    
    btns.push_back(newButton(NEW_LOAN_BTN_ID, "New Loan"));
    btns.push_back(newButton(UPDATE_LOAN_BTN_ID, "Update Loan"));
    btns.push_back(newButton(PRINT_REPORT_BTN_ID, "Print Report"));
    
    mList = new wxListBox(this, wxID_ANY, wxPoint(200,10), wxSize(300,300));
    
    mToolbar = new wxToolBar(this, wxID_ANY);
    
    mMenuBar = new wxMenuBar();
    this->SetMenuBar(mMenuBar);
    
    wxMenu* MenuFile = new wxMenu();
    MenuFile->Append(NEW, "New");
    MenuFile->Append(OPEN, "Open");
    MenuFile->Append(SAVE, "Save");
    
    mMenuBar->Append(MenuFile, "File");
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
            mList->AppendString("Create a new loan");
            mcData loan;
            SequencePrompts loanPrompts(loan);
            
            loanPrompts.addQuery("Enter the purchase price of the home - ", loan.purchasePrice);
            loanPrompts.addQuery("Enter the downpayment for this home - ", loan.downpayment);
            loanPrompts.addQuery("Enter the number of term in years - ", loan.termYears);
            
            break;
        }
        case UPDATE_LOAN_BTN_ID:
            mList->AppendString("Update an existing loan");
            break;
            
        case PRINT_REPORT_BTN_ID:
            mList->AppendString("Which report?");
            break;
    }
    
    evt.Skip();
}

void mcMain::OnNewMenu(wxCommand& evt) {
    
}

void mcMain::OnOpenMenu(wxCommand& evt) {
    
}

void mcMain::OnSaveMenu(wxCommand& evt) {
    
}


