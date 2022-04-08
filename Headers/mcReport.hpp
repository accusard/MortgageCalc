//
//  mcReport.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcReport_hpp
#define mcReport_hpp

#include <queue>
#include <iostream>
#include <sstream>
#include <iomanip>

struct mcData;
class wxListView;

class FormatDollar  {
public:
    FormatDollar(const float val);
    const std::string toString();
    
protected:
    std::string formattedString;
    int dollar;
    float fractionDollar;
    float unformatted;
    
};

struct ReportList {
    const std::queue<std::string> get() const {return mList;}
    
protected:
    std::queue<std::string> mList;
    
};

class SummaryReport : public ReportList {
public:
    SummaryReport(mcData& dataRef, wxListView* list, const int columnWidth);
    
};

class MortgageReport : public ReportList {
public:
    MortgageReport();
    
    
private:
    
};

class AmortizationReport {
public:
    AmortizationReport() {}
    void format(mcData& dref, wxListView* list);
    
    ~AmortizationReport() {};
    
private:
    
};

class BorrowersReport : public ReportList {
public:
    BorrowersReport();
    
private:
    std::vector<struct Borrower> mBorrowers;
    
};

class DTIReport {
public:
    DTIReport(mcData& dRef);
};

#endif /* mcReport_hpp */
