//
//  IDataFileInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef IDataFileInterface_h
#define IDataFileInterface_h

#include "mcFile.hpp"


class IDataFileInterface {
public:
    
    virtual void makeHashTable(std::unordered_map<std::string, float> &hash) = 0;
};

#endif /* IDataFileInterface_h */


