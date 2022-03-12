//
//  mcApp.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//



#include "mcApp.hpp"
#include "mcMain.hpp"
#include "mcData.hpp"
#include "mcBook.hpp"
#include "mcType.h"
#include <fstream>


wxIMPLEMENT_APP(mcApp);


mcApp::~mcApp() {
    for(auto* i : mAppData) {
        if(i != nullptr) delete i;
    }
}

bool mcApp::OnInit() {
    // init window
    main = new mcMain();
    return true;
}

mcData* mcApp::NewMortgageData(const mcData& oldData) {
    mAppData.push_back(new mcData(oldData));
    return mAppData.back();
}

mcData* mcApp::GetMortgageData(const int index) {
    if(index > -1)
        return mAppData[index];
    else
        return mAppData.back();
}
