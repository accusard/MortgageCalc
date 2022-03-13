//
//  mcDataEntryList.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcDataEntryList.hpp"
#include "mcApp.hpp"
#include "mcBook.hpp"
#include "mcType.h"

wxBEGIN_EVENT_TABLE(mcDataEntryList, wxListView)
EVT_LIST_ITEM_SELECTED(mcID_EDITABLE_LIST, mcDataEntryList::OnClicked)
wxEND_EVENT_TABLE()

mcDataEntryList::mcDataEntryList(wxWindow *parent,
                                 wxWindowID winid,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 const int columnwidth,
                                 mcData* loan) : wxListView(parent, winid, pos, size) {
    AppendColumn("Field", wxLIST_FORMAT_LEFT, columnwidth);
    AppendColumn("Value", wxLIST_FORMAT_LEFT, columnwidth);
}

void mcDataEntryList::bindFields(const std::vector<mcDialogPrompt<float>>& prompts, const int column) {
    for(int i = 0; i < prompts.size(); i++) {
        bindFields(prompts[i], i,  column);
    }
}

void mcDataEntryList::bindFields(const mcDialogPrompt<float>& prompt, const int row, const int column) {
    // bind the data to field
//    ClearAll();
    wxString var = prompt.getString();
    wxString val = std::to_string(long(prompt.getData()));
    InsertItem(row, " " + var);
    SetItem(row, column, val);
}

const bool mcDataEntryList::update(mcData* data) {
    std::vector<mcDialogPrompt<float>> prompts = data->getFieldEntries();
    wxString val = "";
    for(int i = 0; i < prompts.size(); i++) {
        val = std::to_string(long(prompts[i].getData()));
        SetItem(i, 1, val);
    }
    return true;
}

void mcDataEntryList::OnClicked(wxListEvent& evt) {
    const int itmdx = (int)evt.GetCacheTo();
    mcData* data = wxGetApp().GetMortgageData();
    mcDialogPrompt<float> prmt = data->getFieldEntry(itmdx);
    prmt.show();
    wxString str = std::to_string((long)prmt.getData());
    SetItem(itmdx, 1, str);
    Select(itmdx,false);
    
    evt.SetClientData(data);
    evt.Skip();
}
