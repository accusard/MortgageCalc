//
//  mcReport.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcReport_hpp
#define mcReport_hpp

class wxListView;

struct Report {
public:
    const std::string& get() const { return mFormattedReport; }
    
protected:
    std::string mFormattedReport = "";
    
};

class MortgageReport : public Report {
public:
    MortgageReport(struct mcData& dRef);
    
    
private:
    
};

class AmortizationReport {
public:
    AmortizationReport() {}
    void format(mcData& dref, wxListView* list);
    
    ~AmortizationReport() {};
    
private:
    
};

#endif /* mcReport_hpp */
