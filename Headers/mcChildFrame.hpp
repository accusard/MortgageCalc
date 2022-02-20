//
//  mcChildFrame.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcChildFrame_hpp
#define mcChildFrame_hpp

#include "wx/mdi.h"

class mcChildFrame : public wxMDIChildFrame {
public:
    mcChildFrame(wxMDIParentFrame* setFrame, const wxString& name);
    ~mcChildFrame();
    
    wxButton* newButton(const int btnId, const wxString& label);
    
private:
    
    void OnButtonClicked(wxCommandEvent &evt);
    std::vector<wxButton*> btns;
    
    wxStatusBar* mStatusBar = nullptr;
    wxSlider* mSlider = nullptr;
    wxToolBar* mToolBar = nullptr;
//    wxDECLARE_EVENT_TABLE();
};

#endif /* mcChildFrame_hpp */
