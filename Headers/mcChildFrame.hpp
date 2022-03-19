//
//  mcChildFrame.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcChildFrame_hpp
#define mcChildFrame_hpp

#include "wx/mdi.h"

class mcChildFrame : public wxMDIChildFrame {
private:
        class mcDataEntryList* mDataList = nullptr;
        class mcBook* mDataBook = nullptr;
        std::vector<wxSlider*> mSliders;
    
public:
    mcChildFrame(wxMDIParentFrame* parent, const wxString& name, const int verticalsize,  const int columnwidth, struct mcData* loan);
    ~mcChildFrame();

    wxSlider* MakeSlider(wxWindow *parent, wxWindowID id, const wxPoint& pos, int current, int minimum, uint maximum);
    
    class mcDataEntryList* GetList() { return mDataList; }
    class mcBook* GetBook() { return mDataBook; }
    
    void OnFieldChanged(class wxListEvent& evt);
    void OnScroll(wxScrollEvent& evt);
    wxDECLARE_EVENT_TABLE();


};

#endif /* mcChildFrame_hpp */
