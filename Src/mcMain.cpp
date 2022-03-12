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
#include "mcSlider.hpp"

wxBEGIN_EVENT_TABLE(mcMain, wxMDIParentFrame)
EVT_MENU(wxID_NEW, mcMain::OnNewMenu)
EVT_MENU(wxID_OPEN, mcMain::OnOpenMenu)
EVT_MENU(wxID_SAVE, mcMain::OnSaveMenu)
EVT_MENU(wxID_EXIT, mcMain::OnQuitMenu)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Mortgage Calculator", DEFAULT_POS_MBP, wxSize(1280,720)) {
    mMenuBar = new wxMenuBar();
    wxMenu *MenuFile = new wxMenu();
    MenuFile->Append(wxID_NEW, "&New\tCtrl+N");
    MenuFile->Append(wxID_OPEN, "&Open\tCtrl+O");
    MenuFile->Append(wxID_SAVE, "&Save\tCtrl+S");
    MenuFile->Append(wxID_EXIT, "Quit");
    mMenuBar->Append(MenuFile, "File");
    this->SetMenuBar(mMenuBar);
    
//    const int colmw = 150;
    mcFile datfile;
    mcData data;
    if(datfile.open(DATA_FILE_NAME.c_str(), data)) {
        mcData* mgdata = wxGetApp().NewMortgageData(data);
        mcChildFrame *newWin = createMortgageLoanWindow("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, mgdata);
        newWin->Show();
    }
}

mcMain::~mcMain() {}

void mcMain::OnNewMenu(wxCommandEvent& evt) {
//    const int colmw = DEFAULT_COLUMN_WIDTH;
    mcData newdata;
    mcChildFrame *mrgLnWin = createMortgageLoanWindow("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().NewMortgageData(newdata));
    mrgLnWin->Show();
    
    evt.Skip();
}

void mcMain::OnOpenMenu(wxCommandEvent& evt) {
    // do dialog
    wxFileDialog* fDialog = new wxFileDialog(this);
    if(fDialog->ShowModal() == wxID_OK) {
        mcData mData;
        mcFile file;

        if(file.open(fDialog->GetPath().c_str(), mData)) {
            createMortgageLoanWindow("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().NewMortgageData(mData))->Show();
        }
    }
    fDialog->Destroy();
}

void mcMain::OnSaveMenu(wxCommandEvent& evt) {
    mcFile file;
    file.save(DATA_FILE_NAME.c_str(), *wxGetApp().GetMortgageData());
}

void mcMain::OnQuitMenu(wxCommandEvent& evt) {
    OnSaveMenu(evt);
    Close();
    evt.Skip();
}

void mcMain::OnScroll(wxScrollEvent& evt) {
    
}

mcChildFrame* mcMain::createMortgageLoanWindow(const wxString& name, const int verticalsize,  const int columnwidth, mcData* loan) {
    mcChildFrame *loanFrm = new mcChildFrame(this, wxString(name) + " " + std::to_string(GetChildren().size()));
    wxGetApp().SetTopWindow(loanFrm);
    
    // create new mcBook to display the loan
    mcBook *bk = new mcBook(loanFrm, mcID_MORTGAGE_LOANBOOK, wxPoint(445, 0), wxSize(830, verticalsize));
    wxGetApp().GetLoanBook = bk;
    
    if(bk->update(loan)) {
        // create data entry list panel
        mcDataEntryList* lsVw = new mcDataEntryList(loanFrm, mcID_EDITABLE_LIST, wxDefaultPosition, wxSize(400, verticalsize), columnwidth, loan);
        wxGetApp().GetEntryList = lsVw;
        
        // create sliders
        slider = new wxSlider(loanFrm, mcID_SLIDER, 0, 0, 140, wxPoint(50, 30),
                              wxSize(140, -1), wxSL_HORIZONTAL);
        Connect(mcID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(mcMain::OnScroll));
        
        // set up the sizer for the child frame
        wxBoxSizer* lsVwSzr = new wxBoxSizer(wxHORIZONTAL);
        lsVwSzr->Add(lsVw, 1, wxEXPAND);
        lsVwSzr->Add(bk, 1, wxEXPAND);
        
        loanFrm->SetSizer(lsVwSzr);
    }
    return loanFrm;
}
