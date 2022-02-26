//
//  mcChildFrame.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcChildFrame.hpp"
#include "mcType.h"


mcChildFrame::mcChildFrame(wxMDIParentFrame* parent, const wxString& name) : wxMDIChildFrame(parent, wxID_ANY, name, POINT_MAC_BOOK_PRO, wxSize(1280,720)) {
    
}

mcChildFrame::~mcChildFrame() {}
