//
//  DataFile.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include <fstream>
#include "MortgageCalculator.h"
#include "DataFile.hpp"
#include "IDataFileInterface.h"


void DataFile::save(const char* filename, MortgageData& data) {
    data.recalculateMortgage();
    std::cout << "saving to " << filename << std::endl <<std:: endl;
    std::ofstream ofile(filename, std::ios::out|std::ios::trunc);
    
    if(ofile.is_open()) {
        for(auto map : data.makeHashTable()) {
            ofile << map.first <<":" << map.second << std::endl;
//            cout << map.first << " : " << map.second << std::endl;
        }
        ofile.close();
    }
}

void DataFile::load(const char* filename, MortgageData& data) {
    std::cout << "loading from " << filename << std::endl << std::endl;
    std::ifstream ifile(filename, std::ios::in);
    
    if(ifile.is_open()) {
        // read each line 1 by 1 and add to variable
        std::string line;
        while(getline(ifile,line))
            read(line, data);
        ifile.close();
    }
    data.recalculateMortgage();
    cout << endl;
}

void DataFile::read(const std::string& inLine, MortgageData& data) {
    
    unsigned long stopat = inLine.find(":");
    const std::string& varname = inLine.substr(0, stopat);
    float* floatptr = nullptr;
    
    if(varname == GET_VAR_NAME(termYears)) { data.termYears = stoi(inLine.substr(stopat+1)); return; }
    else if(varname == GET_VAR_NAME(percentDown)) floatptr = &data.percentDown;
    else if(varname == GET_VAR_NAME(percentInterest)) floatptr = &data.percentInterest;
    else if(varname == GET_VAR_NAME(downpayments)) floatptr = &data.downpayment;
    else if(varname == GET_VAR_NAME(loanAmount)) floatptr = &data.loanAmount;
    else if(varname == GET_VAR_NAME(purchasePrice)) floatptr = &data.purchasePrice;

    if(floatptr != nullptr)
        *floatptr = stof(inLine.substr(stopat+1));

    // print out info to console
    for(auto map : dataHash)
    {
        if((map.first.compare(varname) == 0)) {
            map.second = stof(inLine.substr(stopat+1));
//            cout << map.first << " : " << map.second << endl;
            return;
        }


    }
}
