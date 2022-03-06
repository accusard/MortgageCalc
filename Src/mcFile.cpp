//
//  mcFile.cpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include <fstream>
#include "mcData.hpp"
#include "mcFile.hpp"
#include "IHashTableInterface.h"


void mcFile::save(const char* filename, mcData& data) {
    data.recalculateMortgage();
    data.makeHashTable(dataHash);
    
    std::cout << ">>saving to " << filename << std::endl;
    std::ofstream ofile(filename, std::ios::out|std::ios::trunc);
    
    if(ofile.is_open()) {
        for(auto map : dataHash) {
            ofile << map.first <<":" << map.second << std::endl;
            std::cout << map.first << " : " << map.second << std::endl;
        }
        ofile.close();
    }
}

const bool mcFile::open(const char* filename, mcData& data) {
    bool bsuccess = false;
    data.makeHashTable(dataHash);
    ifstream ifile(filename, std::ios::in);
    if(ifile.is_open()) {
        std::cout << ">>opening from " << filename << std::endl;
        std::ifstream ifile(filename, std::ios::in);
        
        // read each line 1 by 1 and add to variable
        std::string line;
        const char* stopat = ":";
        while(getline(ifile,line))
            CurrentVarString = read(line, data, stopat);
        
        data.recalculateMortgage();
        std::cout << endl;
    
        bsuccess = true;
    }
    ifile.close();
    return bsuccess;
}

std::string* mcFile::read(const std::string& inLine, mcData& data, const char *stopAt) {
    
    unsigned long stpat = inLine.find(stopAt);
    
    if(CurrentVarString != nullptr)
    {
        delete CurrentVarString;
        CurrentVarString = nullptr;
    }
    
    CurrentVarString = new std::string(inLine.substr(0, stpat));
    float* floatptr = nullptr;
    
    if(*CurrentVarString == GET_VAR_NAME(termYears)) {
        data.termYears = stoi(inLine.substr(stpat+1));
        std::cout << *CurrentVarString << " : " << data.termYears << std::endl;
        return CurrentVarString;
    }
    else if(*CurrentVarString == GET_VAR_NAME(percentDown)) floatptr = &data.percentDown;
    else if(*CurrentVarString == GET_VAR_NAME(percentInterest)) floatptr = &data.percentInterest;
    else if(*CurrentVarString == GET_VAR_NAME(downpayment)) floatptr = &data.downpayment;
    else if(*CurrentVarString == GET_VAR_NAME(loanAmount)) floatptr = &data.loanAmount;
    else if(*CurrentVarString == GET_VAR_NAME(purchasePrice)) floatptr = &data.purchasePrice;
    
    if(floatptr != nullptr) {
        *floatptr = stof(inLine.substr(stpat+1));
    
        // print debug out info to console
        for(auto map : dataHash)
        {
            if((map.first.compare(*CurrentVarString) == 0)) {
                map.second = stof(inLine.substr(stpat+1));
                std::cout << map.first << " : " << map.second << std::endl;
                return CurrentVarString;
            }
        }
    }
    std::cout << *CurrentVarString << " : No data" << std::endl;
    return CurrentVarString;
}
