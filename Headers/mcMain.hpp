//
//  mcMain.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcMain_hpp
#define mcMain_hpp

#include "wx/wx.h"
#include "wx/mdi.h"

class wxCommand;

class mcMain : public wxMDIParentFrame {
public:
    mcMain();
    ~mcMain();
    
    wxButton* newButton(const int btnId, const wxString& label);
    
private:
    wxDECLARE_EVENT_TABLE();
    void OnButtonClicked(wxCommandEvent &evt);
    void OnNewMenu(wxCommand& evt);
    void OnOpenMenu(wxCommand& evt);
    void OnSaveMenu(wxCommand& evt);
    
    std::vector<wxButton*> btns;
    wxListBox *mList = nullptr;
    wxToolBar *mToolbar = nullptr;
    wxMenuBar *mMenuBar = nullptr;
};

#endif /* mcMain_hpp */
