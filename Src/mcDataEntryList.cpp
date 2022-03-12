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
    bindFields(loan->getFieldEntries(), 1);
}

void mcDataEntryList::bindFields(const std::vector<mcDialogPrompt<float>>& prompts, const int column) {
    for(int i = 0; i < prompts.size(); i++) {
        // bind the data to field
        wxString var = prompts[i].getString();
        wxString val = std::to_string(long(prompts[i].getData()));
        InsertItem(i, " " + var);
        SetItem(i, column, val);
    }
}

const bool mcDataEntryList::update(mcData* data) {
    cout << "mcDataEntryList::update" << endl;
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
