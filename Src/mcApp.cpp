//
//  mcApp.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//



#include "mcApp.hpp"
#include "MortgageCalculator.h"
#include "Menu.h"
#include "Action.hpp"
#include <fstream>

wxIMPLEMENT_APP(mcApp);


bool mcApp::OnInit() {
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

    Menu main("Main Menu");
    shared_ptr<Action> action = make_shared<AmortizationReport>(mData);
    
    main.bindAction(action);
    main.run();
    
    mData.File.save(DATA_FILE_NAME.c_str(), mData);
    
    return true;
}
