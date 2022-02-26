//
//  IDataInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef IDataInterface_h
#define IDataInterface_h

class IDataInterface {
public:
    virtual const std::vector<std::string> GetDataEntryStrings() = 0;
};

#endif /* IDataInterface_h */
