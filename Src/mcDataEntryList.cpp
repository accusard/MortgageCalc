//
//  mcDataEntryList.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcDataEntryList.hpp"


wxBEGIN_EVENT_TABLE(mcDataEntryList, wxListView)
EVT_LIST_ITEM_SELECTED(wxID_EDIT, mcDataEntryList::OnClicked)
wxEND_EVENT_TABLE()


//mcDataEntryList::mcDataEntryList(wxWindow* parent,
//                                 const wxSize& size,
//                                 std::vector<SinglePrompt<float>> editableEntry) : mcDataEntryList(parent, wxID_EDIT, wxDefaultPosition, size) {
//    
//}

mcDataEntryList::mcDataEntryList(wxWindow *parent,
                                 wxWindowID winid,
                                 const wxPoint& pos,
                                 const wxSize& size) : wxListView(parent, winid, pos, size) {}

void mcDataEntryList::OnClicked(wxListEvent& evt) {
    // placeholder
    std::cout << "Edit: " << evt.GetCacheTo() << std::endl;
}
