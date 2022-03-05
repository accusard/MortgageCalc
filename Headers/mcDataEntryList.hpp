//
//  mcDataEntryList.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcDataEntryList_hpp
#define mcDataEntryList_hpp

#include "wx/listctrl.h"
#include "mcData.hpp"

class mcDataEntryList : public wxListView {
public:
    mcDataEntryList(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    const int columnwidth = 150,
                    mcData* loan = nullptr);
    
    void bindFields(const std::vector<mcDialogPrompt<float>>& prompts, const int column);
    void OnClicked(wxListEvent& evt);
    wxDECLARE_EVENT_TABLE();
    
private:
    
};

#endif /* mcDataEntryList_hpp */
