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
    
    class mcChildFrame* Create(const wxString& name, const int vSize, const int columnwidth, struct mcData* loan);
    wxSlider* Create(wxWindow *parent, wxWindowID id, int cur, int min, uint max);
    
private:
    wxMenuBar *mMenuBar = nullptr;
    class mcDataEntryList* mDataList = nullptr;
    class mcBook* mDataBook = nullptr;
    
    void SizeFrame(wxWindow* frame, std::vector<wxControl*>& controls, const wxOrientation orient, const wxStretch stretch);
    
    void OnNewMenu(wxCommandEvent& evt);
    void OnOpenMenu(wxCommandEvent& evt);
    void OnSaveMenu(wxCommandEvent& evt);
    void OnQuitMenu(wxCommandEvent& evt);
    void OnFieldChanged(class wxListEvent& evt);
    void OnScroll(wxScrollEvent& evt);
    wxDECLARE_EVENT_TABLE();
};

#endif /* mcMain_hpp */
