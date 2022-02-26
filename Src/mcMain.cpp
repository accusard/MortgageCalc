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
#include "wx/listctrl.h"
#include "wx/editlbox.h"

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
    // create new mcBook to display the loan
    mcChildFrame *loanFrame = new mcChildFrame(this, wxString("Mortgage Loan ") + std::to_string(GetChildren().size()));
    mcBook *loanBook = new mcBook(loanFrame, wxID_ANY, wxPoint(445, 0), wxSize(830, 695));
    loanBook->load(wxGetApp().NewMortgageData(nullptr));
    mcData mcd;
    
    // create text entry panel
//    wxPanel* panel = new wxPanel(loanFrame, wxID_ANY, wxDefaultPosition, wxSize(320, 685));
//    wxListView* listview = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 685));
//    listview->AppendColumn("");
    
    wxEditableListBox* editbox = new wxEditableListBox(loanFrame, wxID_ANY, "", wxPoint(5, wxDefaultPosition.y), wxSize(440, 685));
    wxArrayString astr;
    
    for(int i = 0; i < mcd.GetDataEntryStrings().size(); i++) {
        wxString s = mcd.GetDataEntryStrings()[i];
//        listview->InsertItem(i,s);
        astr.Add(s);
    }
    
    editbox->SetStrings(astr);
    
    // display
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
