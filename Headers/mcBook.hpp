//
//  mcBook.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcBook_hpp
#define mcBook_hpp

#include "wx/notebook.h"

class mcBook : public wxNotebook {
private:
public:
    mcBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& sz);
    const bool load(struct mcData* data);
};

#endif /* mcBook_hpp */
