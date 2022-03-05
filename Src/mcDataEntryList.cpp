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
    if(loan) CreateEditbleFields(loan->getEditableEntries(), 1);
}

void mcDataEntryList::CreateEditbleFields(const std::vector<mcPrompt<float>>& editables, const int column) {
    for(int i = 0; i < editables.size(); i++) {
        wxString var = editables[i].getString();
        wxString val = std::to_string(long(editables[i].getData()));
        InsertItem(i, " " + var);
        SetItem(i, column, val);
    }
}

void mcDataEntryList::OnClicked(wxListEvent& evt) {
    long itemdx = evt.GetCacheTo();
    mcData* data = wxGetApp().GetMortgageData();
    mcPrompt<float> prmt = data->getEditableEntries()[itemdx];
    prmt.execute();
    wxString str = std::to_string((long)prmt.getData());
    SetItem(itemdx, 1, str);
}
