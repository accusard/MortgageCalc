//
//  IDataFileInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef IDataFileInterface_h
#define IDataFileInterface_h

#include "DataFile.hpp"


class IDataFileInterface {
public:
    
    virtual const std::unordered_map<std::string, float>& makeHashTable() = 0;
};

#endif /* IDataFileInterface_h */


