//
//  mcBook.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcBook_hpp
#define mcBook_hpp

#include "wx/notebook.h"
#include "DataInterface.h"

struct mcData;
class wxListView;

class mcBook : public wxNotebook, public IDataInterface<mcData> {

public:
    mcBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& sz);
    virtual const bool update(struct mcData* data) override;
    
private:
    wxListView* mOverview = nullptr;
    wxListView* mReport = nullptr;
    wxListView* mSchedule = nullptr;
};

#endif /* mcBook_hpp */
