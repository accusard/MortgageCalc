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

class mcMain : public wxMDIParentFrame {
public:
    mcMain();
    ~mcMain();
    
private:
    void OnNewMenu(wxCommandEvent& evt);
    void OnOpenMenu(wxCommandEvent& evt);
    void OnSaveMenu(wxCommandEvent& evt);
    void OnQuitMenu(wxCommandEvent& evt);
    
    wxMenuBar *mMenuBar = nullptr;
    wxTextCtrl *textCtlr = nullptr;
    
    wxDECLARE_EVENT_TABLE();
};

#endif /* mcMain_hpp */
