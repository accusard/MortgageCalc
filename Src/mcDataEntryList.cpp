//
//  mcDataEntryList.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcDataEntryList.hpp"
#include "mcApp.hpp"


wxBEGIN_EVENT_TABLE(mcDataEntryList, wxListView)
EVT_LIST_ITEM_SELECTED(wxID_EDIT, mcDataEntryList::OnClicked)
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
        wxString var = prompts[i].getString();
        wxString val = std::to_string(long(prompts[i].getData()));
        InsertItem(i, " " + var);
        SetItem(i, column, val);
    }
}

void mcDataEntryList::OnClicked(wxListEvent& evt) {
    const int itmdx = (int)evt.GetCacheTo();
    mcData* data = wxGetApp().GetMortgageData();
    mcDialogPrompt<float> prmt = data->getFieldEntry(itmdx);
    prmt.show();
    wxString str = std::to_string((long)prmt.getData());
    SetItem(itmdx, 1, str);
}
