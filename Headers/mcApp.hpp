//
//  mcApp.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcApp_hpp
#define mcApp_hpp

#include "wx/wx.h"

class mcApp : public wxApp {
    
private:
    class mcMain* frame1 = nullptr;
    
public:
    mcApp() {}
    ~mcApp() {}
    
    virtual bool OnInit();
};

#endif /* mcApp_hpp */
