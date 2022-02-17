//
//  mcApp.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//



#include "mcApp.hpp"
#include "MortgageCalculator.h"
#include "mcMain.hpp"
#include <fstream>

wxIMPLEMENT_APP(mcApp);


bool mcApp::OnInit() {
    
    // init data
    MortgageData mData;
    
    ifstream ifile(DATA_FILE_NAME, ios::in);
    
    if(ifile.is_open()) {
        mData.File.load(DATA_FILE_NAME.c_str(), mData);
        ifile.close();
    }
    else {
        // save a default data
        mData.File.save(DATA_FILE_NAME.c_str(), mData);
    }
    
    // init window
    frame1 = new mcMain();
    frame1->Show();
    
    return true;
}
