//
//  mcFile.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcFile_hpp
#define mcFile_hpp

#include <iostream>
#include <unordered_map>

struct MortgageData;

const std::string DATA_FILE_NAME = "data.bin";

class mcFile {
private:
    void read(const std::string& inLine, MortgageData& data);
    
public:
    // saving and loading file
    std::unordered_map<std::string, float> dataHash;
    void save(const char* filename, MortgageData& data);
    const bool load(const char* filename, MortgageData& data);
    
    
    
};

#endif /* mcFile_hpp */
