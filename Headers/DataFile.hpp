//
//  Borrower.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef DataFile_hpp
#define DataFile_hpp

#include <unordered_map>

class DataFile {
    std::unordered_map<char*, char*> dataHash;
    
public:
    void write();
    const DataFile& read();

    void newInt(const char* id, const int val);
    void newFloat(const char* id, const float val);
    
    
};

#endif /* DataFile_hpp */
