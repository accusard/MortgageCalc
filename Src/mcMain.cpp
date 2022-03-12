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
EVT_LIST_ITEM_DESELECTED(mcID_EDITABLE_LIST, mcMain::OnFieldChanged)
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
        mcChildFrame *newWin = Create("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, mgdata);
        newWin->Show();
    }
}

mcMain::~mcMain() {}

void mcMain::OnNewMenu(wxCommandEvent& evt) {
    mcData newdata;
    mcChildFrame *mrgLnWin = Create("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().NewMortgageData(newdata));
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
            Create("Mortgage Loan", DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().NewMortgageData(mData))->Show();
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

mcChildFrame* mcMain::Create(const wxString& name, const int verticalsize,  const int columnwidth, mcData* loan) {
    mcChildFrame *loanFrm = new mcChildFrame(this, wxString(name) + " " + std::to_string(GetChildren().size()));
    wxGetApp().SetTopWindow(loanFrm);
    
    // create new mcBook to display the loan
    mDataBook = new mcBook(loanFrm, mcID_MORTGAGE_LOANBOOK, wxPoint(445, 0), wxSize(830, verticalsize));
    
    if(mDataBook->update(loan)) {
        // create data entry list panel
        mDataList = new mcDataEntryList(loanFrm, mcID_EDITABLE_LIST, wxDefaultPosition, wxSize(400, verticalsize), columnwidth, loan);
        
        // set up the sizer for the child frame
        wxBoxSizer* lsVwSzr = new wxBoxSizer(wxHORIZONTAL);
        lsVwSzr->Add(mDataList, 1, wxEXPAND);
        lsVwSzr->Add(mDataBook, 1, wxEXPAND);
        loanFrm->SetSizer(lsVwSzr);
    }
    return loanFrm;
}

wxSlider* mcMain::Create(wxWindow *parent, wxWindowID id, int current, int minimum, uint maximum) {
    wxSlider* sldr = new wxSlider(parent, id, current, minimum, maximum, wxPoint(50, 30),
                                    wxSize(140, -1), wxSL_HORIZONTAL);
              Connect(mcID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(mcMain::OnScroll));
    
    
    return sldr;
}

void mcMain::SizeFrame(wxWindow* frame, vector<wxControl*>& controls, const wxOrientation orient, const wxStretch stretch) {
    wxBoxSizer* szr = new wxBoxSizer(orient);
    for(wxControl* ctlr : controls)
    {
        szr->Add(ctlr, 1, stretch);
        szr->Add(ctlr, 1, stretch);
    }
    frame->SetSizer(szr);
}

void mcMain::OnFieldChanged(wxListEvent& evt) {
    mDataList->update(wxGetApp().GetMortgageData());
    mDataBook->update(wxGetApp().GetMortgageData());
    std::cout << ">>Field Changed" << std::endl;
}
