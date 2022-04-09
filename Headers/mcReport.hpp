//
//  mcReport.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcReport_hpp
#define mcReport_hpp

#include <queue>


struct mcData;
class wxListView;


struct ReportList {
    void print(wxListView* target);
    
protected:
    std::queue<std::string> mList;
    
};

class SummaryReport : public ReportList {
public:
    SummaryReport(mcData& dataRef, wxListView* list);
    
};

class MortgageReport : public ReportList {
public:
    MortgageReport(mcData& dref, wxListView* list);
    
private:
    
};

class AmortizationReport {
public:
    AmortizationReport(mcData& dref, wxListView* list);
    ~AmortizationReport() {};
    
private:
    
};

class BorrowersReport : public ReportList {
public:
    BorrowersReport(std::vector<struct Borrower> borrowers, wxListView* list);
    
private:
    std::vector<struct Borrower> mBorrowers;
    
};

class DTIReport : public ReportList {
public:
    DTIReport(mcData& dRef);
};

#endif /* mcReport_hpp */
