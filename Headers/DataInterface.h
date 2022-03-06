//
//  DataInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef DataInterface_h
#define DataInterface_h

template<class T>
class IDataInterface {
public:
    virtual const bool update(T* data) = 0;
};

#endif /* DataInterface_h */
