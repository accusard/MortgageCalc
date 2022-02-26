//
//  IHashTableInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef IHashTableInterface_h
#define IHashTableInterface_h

#include "mcFile.hpp"


class IHashTableInterface {
public:
    
    virtual void makeHashTable(std::unordered_map<std::string, float> &hash) = 0;
};

#endif /* IHashTableInterface_h */


