//
//  mcMain.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcMain.hpp"
#include "mcChildFrame.hpp"
#include "mcType.h"
#include "mcData.hpp"
#include "mcApp.hpp"

wxBEGIN_EVENT_TABLE(mcMain, wxMDIParentFrame)
EVT_MENU(wxID_NEW, mcMain::OnNewMenu)
EVT_MENU(wxID_OPEN, mcMain::OnOpenMenu)
EVT_MENU(wxID_SAVE, mcMain::OnSaveMenu)
EVT_MENU(wxID_EXIT, mcMain::OnQuitMenu)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Mortgage Calculator", POINT_MAC_BOOK_PRO, wxSize(1280,720)) {
    textCtlr = new wxTextCtrl(this, wxID_ANY, L"", wxDefaultPosition, wxSize(400,200));
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
    unsigned long s = this->GetChildren().size();
    const wxString name = "Mortgage Loan " + std::to_string(s);
    mcChildFrame *loanFrame = new mcChildFrame(this, name);
    
    // create new data
    mcData* mData = wxGetApp().NewMortgageData(nullptr);
    mcFile file;
    file.save(DATA_FILE_NAME.c_str(), *mData);
    
    loanFrame->Show();
    evt.Skip();
}

void mcMain::OnOpenMenu(wxCommandEvent& evt) {
    // do dialog
    wxFileDialog* fDialog = new wxFileDialog(this);
    if(fDialog->ShowModal() == wxID_OK) {
        mcData mData;
        mcFile file;
        wxString selected = fDialog->GetPath();
        textCtlr->SetValue(selected);
        file.open(selected.c_str(), mData);
    }
    fDialog->Destroy();
}

void mcMain::OnSaveMenu(wxCommandEvent& evt) {
    mcData mData;
    mcFile file;
    file.save(textCtlr->GetValue().c_str(), mData);
}

void mcMain::OnQuitMenu(wxCommandEvent& evt) {
    OnSaveMenu(evt);
    Close();
    evt.Skip();
}
