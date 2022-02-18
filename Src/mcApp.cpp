//
//  mcApp.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//



#include "mcApp.hpp"
#include "mcMain.hpp"
#include "MortgageCalculator.h"
#include <fstream>

wxIMPLEMENT_APP(mcApp);


bool mcApp::OnInit() {
    
    // init data
    MortgageData mData;
    mcFile file;
    
    if(!file.load(DATA_FILE_NAME.c_str(), mData))
        file.save(DATA_FILE_NAME.c_str(), mData);
    
    // init window
    frame1 = new mcMain();
    frame1->Show();
    
    return true;
}
