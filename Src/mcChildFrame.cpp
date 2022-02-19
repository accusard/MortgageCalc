//
//  mcChildFrame.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcChildFrame.hpp"


mcChildFrame::mcChildFrame(wxMDIParentFrame* setFrame) : wxMDIParentFrame(setFrame, wxID_ANY, "New Child Window") {
    mStatusBar = new wxStatusBar(this);
    mSlider = new wxSlider(this, wxID_ANY, 50, 0, 100);
}
