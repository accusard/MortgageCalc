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
    frame1 = new mcMain();
    return true;
}

mcData* mcApp::NewMortgageData(const mcData& oldData) {
//    if(oldData != nullptr) {
        mAppData.push_back(new mcData(oldData));
//    }
//    mAppData.push_back(new mcData());
    return mAppData.back();
}

mcData* mcApp::GetMortgageData(const int index) {
    if(index > -1)
        return mAppData[index];
    else
        return mAppData.back();
}

//mcBook* mcApp::GetLoanBook() const {
//    mcBook* bk = nullptr;
//    if(GetTopWindow())
//        bk = (mcBook*)(wxGetApp().GetTopWindow()->FindWindow(mcID_MORTGAGE_LOANBOOK));
//    return bk;
//}
