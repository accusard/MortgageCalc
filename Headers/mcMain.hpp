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
    
    class mcChildFrame* createMortgageLoanWindow(const wxString& name, const int vSize, struct mcData* loan);
    
private:
    void OnNewMenu(wxCommandEvent& evt);
    void OnOpenMenu(wxCommandEvent& evt);
    void OnSaveMenu(wxCommandEvent& evt);
    void OnQuitMenu(wxCommandEvent& evt);
    
    wxMenuBar *mMenuBar = nullptr;
    
    wxDECLARE_EVENT_TABLE();
};

#endif /* mcMain_hpp */
