//
//  mcApp.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//



#include "mcApp.hpp"
#include "mcMain.hpp"
#include "mcData.hpp"
#include <fstream>


wxIMPLEMENT_APP(mcApp);


bool mcApp::OnInit() {
    // init window
    frame1 = new mcMain();
    frame1->Show();
    
    return true;
}

mcData* mcApp::NewMortgageData(mcData *oldData) {
    if(oldData != nullptr)
        delete oldData;
    
    return new mcData();
}

