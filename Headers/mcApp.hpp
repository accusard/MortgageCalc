//
//  mcApp.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcApp_hpp
#define mcApp_hpp

#include "wx/wx.h"
struct mcData;

class mcApp : public wxApp {
    
private:
    std::vector<mcData*> mAppData;
    class mcMain* frame1 = nullptr;
    
public:
    mcApp() {}
    ~mcApp();
    
    virtual bool OnInit();
    mcData* NewMortgageData(mcData* oldData);
    mcData* GetMortgageData(const int index = -1);
};

DECLARE_APP(mcApp);

#endif /* mcApp_hpp */
