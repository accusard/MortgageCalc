//
//  IDataInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef IDataInterface_h
#define IDataInterface_h


template<class T>
class IDataInterface {
public:
    virtual std::vector<T> getFieldEntries() = 0;
};

#endif /* IDataInterface_h */
