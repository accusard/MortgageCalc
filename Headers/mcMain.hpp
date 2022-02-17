//
//  mcMain.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcMain_hpp
#define mcMain_hpp

#include "wx/wx.h"

const unsigned int NEW_LOAN_BTN_ID = 1000;
const unsigned int UPDATE_LOAN_BTN_ID = 1001;
const unsigned int PRINT_REPORT_BTN_ID = 1002;

class mcMain : public wxFrame {
public:
    mcMain();
    ~mcMain();
    
    wxButton* newButton(const int btnId, const wxString& label);
    
public:
    
    std::vector<wxButton*> btns;
    wxListBox *list = nullptr;
    
    void OnButtonClicked(wxCommandEvent &evt);
    
    wxDECLARE_EVENT_TABLE();
};

#endif /* mcMain_hpp */
