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

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, DEFAULT_WINDOW_NAME, DEFAULT_POS_MBP, wxSize(1280,720)) {
    mMenuBar = new wxMenuBar();
    wxMenu *MenuFile = new wxMenu();
    MenuFile->Append(wxID_NEW, "&New\tCtrl+N");
//    MenuFile->Append(wxID_OPEN, "&Open\tCtrl+O");
    MenuFile->Append(wxID_SAVE, "&Save\tCtrl+S");
    MenuFile->Append(wxID_EXIT, "Quit");
    mMenuBar->Append(MenuFile, "File");
    this->SetMenuBar(mMenuBar);
    
    mcFile datfile;
    mcData data;
    if(datfile.open(DATA_FILE_NAME.c_str(), data)) {
        mcData* mgdata = wxGetApp().NewMortgageData(data);
        wxMDIChildFrame *frm = Create(DEFAULT_WINDOW_NAME, DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, mgdata);
        frm->Show();
    }
}

mcMain::~mcMain() {}

void mcMain::OnNewMenu(wxCommandEvent& evt) {
    mcData newdata;

    wxMDIChildFrame *newWin = Create("New " + DEFAULT_WINDOW_NAME, DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().NewMortgageData(newdata));
    newWin->Show();
    
    evt.Skip();
}

void mcMain::OnOpenMenu(wxCommandEvent& evt) {
    // do dialog
    wxFileDialog* fDialog = new wxFileDialog(this,"","","",".bin Files (*.bin)|*.bin", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(fDialog->ShowModal() == wxID_OK) {
        mcData mData;
        mcFile file;

        if(file.open(fDialog->GetPath().c_str(), mData)) {
            Create(DEFAULT_WINDOW_NAME, DEFAULT_VSIZE_LOAN_WIN, DEFAULT_COLUMN_WIDTH, wxGetApp().GetMortgageData())->Show();
        }
    }
    fDialog->Destroy();
}

void mcMain::OnSaveMenu(wxCommandEvent& evt) {
    if(wxWindow* activeWin = GetActiveChild()) {
        mcFile file;
        file.save(DATA_FILE_NAME.c_str(), *wxGetApp().GetMortgageData());
        activeWin->SetLabel(DEFAULT_WINDOW_NAME);
    }
}

void mcMain::OnQuitMenu(wxCommandEvent& evt) {
    OnSaveMenu(evt);
    Close();
    evt.Skip();
}

wxMDIChildFrame* mcMain::Create(const wxString& name, const int verticalsize,  const int columnwidth, mcData* loan) {
    if(wxWindow* active = GetActiveChild()) {
        active->Close();
        
    }
    mcChildFrame *frm = new mcChildFrame(this, name, verticalsize, columnwidth, loan);
    wxGetApp().SetTopWindow(frm);
    return frm;
}
