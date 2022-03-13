//
//  mcChildFrame.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcChildFrame.hpp"
#include "mcDataEntryList.hpp"
#include "mcBook.hpp"
#include "mcApp.hpp"
#include "mcType.h"

wxBEGIN_EVENT_TABLE(mcChildFrame, wxMDIChildFrame)
EVT_LIST_ITEM_DESELECTED(mcID_EDITABLE_LIST, mcChildFrame::OnFieldChanged)
wxEND_EVENT_TABLE()

mcChildFrame::mcChildFrame(wxMDIParentFrame* parent, const wxString& name, const int verticalsize,  const int columnwidth, mcData* loan) : wxMDIChildFrame(parent, wxID_ANY, name, DEFAULT_POS_MBP, wxSize(1280,720)) {
    // create new mcBook to display the loan
    mDataBook = new mcBook(this, mcID_MORTGAGE_LOANBOOK, wxPoint(445, 0), wxSize(830, verticalsize));
    
    if(mDataBook->update(loan)) {
        // create data entry list panel
        mDataList = new mcDataEntryList(this, mcID_EDITABLE_LIST, wxDefaultPosition, wxSize(400, verticalsize), columnwidth, loan);
        
        // set up the sizer for the child frame
        wxBoxSizer* lsVwSzr = new wxBoxSizer(wxHORIZONTAL);
        lsVwSzr->Add(mDataList, 1, wxEXPAND);
        lsVwSzr->Add(mDataBook, 1, wxEXPAND);
        SetSizer(lsVwSzr);
    }
    std::vector<mcDialogPrompt<float>> prompts = loan->getFieldEntries();
    for(int i = 0; i < prompts.size(); i++) {
        mDataList->bindFields(prompts[i], i, 1);
        
        wxPoint pos = wxPoint(columnwidth*2, (i+1) * GetFont().GetPixelSize().y);
        wxSlider* sld = Create(this, mcID_SLIDER+i, pos, prompts[i].getData(), 0, prompts[i].getMax());
        
        mSliders.push_back(sld);
    }
}

mcChildFrame::~mcChildFrame() {}

wxSlider* mcChildFrame::Create(wxWindow *parent, wxWindowID id, const wxPoint& pos, int current, int minimum, uint maximum) {
    wxSlider* sldr = new wxSlider(parent, id, current, minimum, maximum,
                                  pos, wxSize(140, -1), wxSL_HORIZONTAL);
    
    Connect(id, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(mcChildFrame::OnScroll));
    return sldr;
}

void mcChildFrame::OnFieldChanged(wxListEvent& evt) {
    mDataList->update(wxGetApp().GetMortgageData());
    mDataBook->update(wxGetApp().GetMortgageData());
}

void mcChildFrame::OnScroll(wxScrollEvent& evt) {
    mcData* dat = wxGetApp().GetMortgageData();
    const int id = evt.GetId() - mcID_SLIDER;
    dat->getFieldEntry(id).getData() = mSliders[id]->GetValue();
    wxListEvent non;
    OnFieldChanged(non);
}
