//
//  mcChildFrame.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcChildFrame_hpp
#define mcChildFrame_hpp

#include "wx/mdi.h"

class mcChildFrame : public wxMDIParentFrame {
public:
    mcChildFrame(wxMDIParentFrame* setFrame);
    ~mcChildFrame() {}
    
private:
    wxStatusBar* mStatusBar = nullptr;
    wxSlider* mSlider = nullptr;
};

#endif /* mcChildFrame_hpp */
