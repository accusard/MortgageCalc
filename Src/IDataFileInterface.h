//
//  IDataFileInterface.h
//  MortgageCalc
//
//  Created by Vanny Sou on 2/13/22.
//

#ifndef IDataFileInterface_h
#define IDataFileInterface_h

#include "DataFile.hpp"


class IDataFileInterface {
public:
    virtual std::unordered_map<std::string, float>& makeHashTable(class DataFile& file) = 0;
};

#endif /* IDataFileInterface_h */


