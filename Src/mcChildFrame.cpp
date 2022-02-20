//
//  mcChildFrame.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcChildFrame.hpp"
#include "eventId.h"

mcChildFrame::mcChildFrame(wxMDIParentFrame* setFrame, const wxString& name) : wxMDIChildFrame(setFrame, wxID_ANY, name) {
    mStatusBar = new wxStatusBar(this);
    mSlider = new wxSlider(this, wxID_ANY, 50, 0, 100);
    mToolBar = new wxToolBar(this, wxID_ANY);
    
    btns.push_back(newButton(NEW_LOAN_BTN_ID, "New Loan"));
    btns.push_back(newButton(UPDATE_LOAN_BTN_ID, "Update Loan"));
    btns.push_back(newButton(PRINT_REPORT_BTN_ID, "Print Report"));
}

mcChildFrame::~mcChildFrame() {
    for(auto btn : btns) {
        if(btn != nullptr)
            delete btn;
    }
}

wxButton* mcChildFrame::newButton(const int btnId, const wxString& label) {
    const unsigned int hpos = (int)btns.size()*50 + 10;
    return new wxButton(this, btnId, label, wxPoint(hpos, 10), wxSize(150,50));
}

void mcChildFrame::OnButtonClicked(wxCommandEvent &evt) {
    evt.Skip();
}
