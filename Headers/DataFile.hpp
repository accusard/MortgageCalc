//
//  Borrower.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef DataFile_hpp
#define DataFile_hpp

#define GET_VAR_NAME(var) (#var)
#define MAKE_HASH(name) insert(GET_VAR_NAME(name), name);

#include <iostream>
#include <unordered_map>
#include "IDataFileInterface.h"

struct MortgageData;

const std::string DATA_FILE_NAME = "debugsave.txt";

class DataFile {
private:
//    void insert(const std::string& str, const float val);
    void readFrom(const std::string& line);
    
public:
    // saving and loading file
    std::unordered_map<std::string, float> dataHash;
    void save(const char* filename, std::unordered_map<std::string, float>&(IDataFileInterface::*hashMapPtr)(DataFile&), DataFile& file);
    void load(const char* filename);
    
    
    
};

#endif /* DataFile_hpp */
