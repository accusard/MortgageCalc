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
    
    class wxMDIChildFrame* Create(const wxString& name, const int vSize, const int columnwidth, struct mcData* loan);
    
private:
    wxMenuBar *mMenuBar = nullptr;
    
    void OnNewMenu(wxCommandEvent& evt);
    void OnOpenMenu(wxCommandEvent& evt);
    void OnSaveMenu(wxCommandEvent& evt);
    void OnQuitMenu(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();
};

#endif /* mcMain_hpp */
