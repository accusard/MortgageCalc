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
public:
    mcApp() {}
    ~mcApp() {}
    
    virtual bool OnInit();
};

#endif /* mcApp_hpp */
