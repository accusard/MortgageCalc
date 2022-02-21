//
//  mcChildFrame.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "mcChildFrame.hpp"
#include "mcType.h"
#include "wx/notebook.h"

mcChildFrame::mcChildFrame(wxMDIParentFrame* parent, const wxString& name) : wxMDIChildFrame(parent, wxID_ANY, name, POINT_MAC_BOOK_PRO, wxSize(1280,720)) {
    wxNotebook *book = new wxNotebook(this, wxID_ANY);
    
    wxListBox *overview = new wxListBox(book, wxID_ANY);
    wxListBox *report = new wxListBox(book, wxID_ANY);
    wxListBox *schedule = new wxListBox(book, wxID_ANY);
    
    book->AddPage(overview, "Overview");
    book->AddPage(report, "Mortgage Report");
    book->AddPage(schedule, "Scheduled Payments");
}

mcChildFrame::~mcChildFrame() {}


