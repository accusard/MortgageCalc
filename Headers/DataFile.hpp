//
//  Borrower.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef DataFile_hpp
#define DataFile_hpp

#define GET_VAR_NAME(var) (#var)
#define MAKE_HASH(name) dataHash.insert_or_assign(GET_VAR_NAME(name),name)

#include <iostream>
#include <unordered_map>

struct MortgageData;

const std::string DATA_FILE_NAME = "debugsave.txt";

class DataFile {
private:
    void readFrom(const std::string& inLine, MortgageData& data);
    
public:
    // saving and loading file
    std::unordered_map<std::string, float> dataHash;
    void save(const char* filename, MortgageData& data);
    void load(const char* filename, MortgageData& data);
    
    
    
};

#endif /* DataFile_hpp */
