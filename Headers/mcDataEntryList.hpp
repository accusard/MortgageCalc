//
//  mcDataEntryList.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcDataEntryList_hpp
#define mcDataEntryList_hpp

#include "wx/listctrl.h"


class mcDataEntryList : public wxListView {
public:
//    mcDataEntryList(wxWindow* parent, const wxSize& size, std::vector<SinglePrompt<float>> editableEntry);
    mcDataEntryList(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize);
    
    void OnClicked(wxListEvent& evt);
    wxDECLARE_EVENT_TABLE();
};

#endif /* mcDataEntryList_hpp */
