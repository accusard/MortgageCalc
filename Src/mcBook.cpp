//
//  mcBook.cpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#include "wx/listctrl.h"
#include "mcBook.hpp"
#include "mcReport.hpp"

mcBook::mcBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& sz) : wxNotebook(parent, id, pos, sz) {
    mOverview = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    mReport = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    mSchedule = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    
    AddPage(mOverview, "Overview");
    AddPage(mReport, "Mortgage Report");
    AddPage(mSchedule, "Scheduled Payments");
}

const bool mcBook::update(mcData* data) {
    if(data != nullptr) {
        mOverview->ClearAll();
        mSchedule->ClearAll();
        mReport->ClearAll();
        
        SummaryReport report = SummaryReport(*data, mOverview, 500);
        AmortizationReport schedule = AmortizationReport();
        
        schedule.format(*data, mSchedule);
        
        mReport->SetLabel("Here be dragons!");
        

        return true;
    }
    return false;
}
