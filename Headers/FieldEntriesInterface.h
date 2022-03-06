//
//  FieldEntriesInterface.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef FieldEntriesInterface_h
#define FieldEntriesInterface_h


template<class T>
class IFieldEntriesInterface {
public:
    virtual std::vector<T> getFieldEntries() = 0;
};

#endif /* FieldEntriesInterface_h */
