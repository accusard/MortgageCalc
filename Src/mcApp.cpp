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


mcApp::~mcApp() {
    for(auto* i : mAppData) {
        if(i != nullptr) delete i;
    }
}

bool mcApp::OnInit() {
    // init window
    frame1 = new mcMain();
    return true;
}

mcData* mcApp::NewMortgageData(mcData *oldData) {
    if(oldData != nullptr) {
        delete oldData;
    }
    mAppData.push_back(new mcData());
    return mAppData.back();
}

mcData* mcApp::GetMortgageData(const int index) {
    if(index > -1)
        return mAppData[index];
    else
        return mAppData.back();
}
