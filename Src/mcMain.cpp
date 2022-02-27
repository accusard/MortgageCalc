//
//  mcMain.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcMain.hpp"
#include "mcApp.hpp"
#include "mcChildFrame.hpp"
#include "mcBook.hpp"
#include "mcData.hpp"
#include "mcType.h"
#include "mcDataEntryList.hpp"

wxBEGIN_EVENT_TABLE(mcMain, wxMDIParentFrame)
EVT_MENU(wxID_NEW, mcMain::OnNewMenu)
EVT_MENU(wxID_OPEN, mcMain::OnOpenMenu)
EVT_MENU(wxID_SAVE, mcMain::OnSaveMenu)
EVT_MENU(wxID_EXIT, mcMain::OnQuitMenu)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Mortgage Calculator", POINT_MAC_BOOK_PRO, wxSize(1280,720)) {
    mMenuBar = new wxMenuBar();
    wxMenu *MenuFile = new wxMenu();
    MenuFile->Append(wxID_NEW, "&New\tCtrl+N");
    MenuFile->Append(wxID_OPEN, "&Open\tCtrl+O");
    MenuFile->Append(wxID_SAVE, "&Save\tCtrl+S");
    MenuFile->Append(wxID_EXIT, "Quit");
    mMenuBar->Append(MenuFile, "File");
    this->SetMenuBar(mMenuBar);
}

mcMain::~mcMain() {}

void mcMain::OnNewMenu(wxCommandEvent& evt) {
    // create frame to hold all children
    mcChildFrame *loanFrm = new mcChildFrame(this, wxString("Mortgage Loan ") + std::to_string(GetChildren().size()));
    
    // create new mcBook to display the loan
    mcBook *loanBk = new mcBook(loanFrm, wxID_ANY, wxPoint(445, 0), wxSize(830, 695));
    loanBk->load(wxGetApp().NewMortgageData(nullptr));
    mcData mcd;
    
    // create text entry list
    mcDataEntryList* lsVw = new mcDataEntryList(loanFrm, wxID_EDIT, wxDefaultPosition, wxSize(400, 685));
    lsVw->AppendColumn("Field", wxLIST_FORMAT_LEFT, 150);
    lsVw->AppendColumn("Value", wxLIST_FORMAT_LEFT, 150);
    
    // set up the sizer for the child frame
    wxBoxSizer* lsVwSzr = new wxBoxSizer(wxHORIZONTAL);
    lsVwSzr->Add(lsVw, 1, wxEXPAND);
    lsVwSzr->Add(loanBk, 1, wxEXPAND);
    loanFrm->SetSizer(lsVwSzr);
    
    for(int i = 0; i < mcd.GetDataEntryStrings().size(); i++) {
        wxString s = mcd.GetDataEntryStrings()[i];
        lsVw->InsertItem(i, s);
        lsVw->SetItem(i, 1, "");
    }

    // display
    loanFrm->Show();
    
    evt.Skip();
}

void mcMain::OnOpenMenu(wxCommandEvent& evt) {
    // do dialog
    wxFileDialog* fDialog = new wxFileDialog(this);
    if(fDialog->ShowModal() == wxID_OK) {
        mcData mData;
        mcFile file;
        wxString selected = fDialog->GetPath();
        file.open(selected.c_str(), mData);
    }
    fDialog->Destroy();
}

void mcMain::OnSaveMenu(wxCommandEvent& evt) {
    mcData mData;
    mcFile file;
    file.save(DATA_FILE_NAME.c_str(), mData);
}

void mcMain::OnQuitMenu(wxCommandEvent& evt) {
    OnSaveMenu(evt);
    Close();
    evt.Skip();
}

