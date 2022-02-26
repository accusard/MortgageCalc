//
//  mcBook.cpp
//  dynamic
//
//  Created by Vanny Sou on 2/26/22.
//

#include "mcBook.hpp"
#include "mcData.hpp"

mcBook::mcBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& sz) : wxNotebook(parent, id, pos, sz) {
    // create the notebook for loan details
    wxListBox *overview = new wxListBox(this, wxID_ANY);
    wxListBox *report = new wxListBox(this, wxID_ANY);
    wxListBox *schedule = new wxListBox(this, wxID_ANY);
    this->AddPage(overview, "Overview");
    this->AddPage(report, "Mortgage Report");
    this->AddPage(schedule, "Scheduled Payments");
}

const bool mcBook::load(mcData* data) {
    if(data != nullptr) {
        
        return true;
    }
    return false;
}

//void mcBook::bind(
