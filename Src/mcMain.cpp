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
EVT_MENU(NEW, mcMain::OnNewMenu)
EVT_MENU(OPEN, mcMain::OnOpenMenu)
EVT_MENU(SAVE, mcMain::OnSaveMenu)
EVT_MENU(wxID_EXIT, mcMain::OnQuitMenu)
wxEND_EVENT_TABLE()

mcMain::mcMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Mortgage Calculator", wxPoint(50,50), wxSize(640,480)) {
    mMenuBar = new wxMenuBar();
    wxMenu* MenuFile = new wxMenu();
    MenuFile->Append(NEW, "&New\tCtrl+N");
    MenuFile->Append(OPEN, "&Open\tCtrl+O");
    MenuFile->Append(SAVE, "&Save\tCtrl+S");
    MenuFile->Append(wxID_EXIT, "Quit");
    
    mMenuBar->Append(MenuFile, "File");
    this->SetMenuBar(mMenuBar);
}

mcMain::~mcMain() {}

void mcMain::OnNewMenu(wxCommandEvent& evt) {
    
}

void mcMain::OnOpenMenu(wxCommandEvent& evt) {
    
}

void mcMain::OnSaveMenu(wxCommandEvent& evt) {
    
}

void mcMain::OnQuitMenu(wxCommandEvent& evt) {
    OnSaveMenu(evt);
    Close();
}
