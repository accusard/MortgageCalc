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
    ~mcChildFrame() {}
    
private:
    wxStatusBar* mStatusBar = nullptr;
    wxSlider* mSlider = nullptr;
};

#endif /* mcChildFrame_hpp */
