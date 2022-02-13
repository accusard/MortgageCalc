//
//  Borrower.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#include <fstream>
#include "DataFile.hpp"
#include "IDataFileInterface.h"


void DataFile::save(const char* filename, std::unordered_map<std::string, float>&(IDataFileInterface::*hashMapPtr)(DataFile&), DataFile& file) {
    std::cout << "saving " << filename << std::endl <<std:: endl;
    std::ofstream ofile(filename, std::ios::out|std::ios::trunc);
    
    if(ofile.is_open()) {
        for(auto map : *hashMapPtr(file)) {
            ofile << map.first <<":" << map.second << std::endl;
        }
        ofile.close();
    }
}

void DataFile::load(const char* filename) {
    std::cout << "loading " << filename << std::endl << std::endl;
    std::ifstream ifile(filename, std::ios::in);
    
    if(ifile.is_open()) {
        // read each line 1 by 1 and add to variable
        std::string line;
        while(getline(ifile,line))
        {
            readFrom(line);
        }
        ifile.close();
    }
}

//void DataFile::insert(const std::string& str, const float val) {
//    dataHash.insert(make_pair(str, val));
//}

void DataFile::readFrom(const std::string& inLine) {
    
    unsigned long stopat = inLine.find(":");
    const std::string& varname = inLine.substr(0, stopat);
    
    for(auto map : dataHash)
    {
        if((map.first.compare(varname) == 0)) {
            map.second = stof(inLine.substr(stopat+1));
            return;
        }


    }
}
