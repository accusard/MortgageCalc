//
//  mcAction.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcAction_hpp
#define mcAction_hpp
#include "wx/numdlg.h"

struct mcAction {
    mcAction() {}
    virtual ~mcAction() {}
    virtual void show() {}
};

template<class T>
class mcPrompt : public mcAction {
public:
    mcPrompt(const string& prmpt, T& dataRef) : mInquiry(prmpt), mData(dataRef) {}
    virtual void show() override {
        QueryToType<T> q = QueryToType<T>(mInquiry, mData);
        cin >> q;
        cout << "Done." << endl;
    }
    
    const string& getString() const { return mInquiry; }
    const T& getData() const { return mData; }
protected:
    string mInquiry;
    T& mData;
};

template<class T>
class mcDialogPrompt : public mcPrompt<T> {
public:
    mcDialogPrompt(const std::string& prompt, T& data) : mcPrompt<T>(prompt, data) {}
    
    virtual void show() override {
        wxNumberEntryDialog dlg;
        dlg.Create(nullptr, "", this->mInquiry, "Enter New Value", this->mData, 0, 99999999);
        if(dlg.ShowModal() == wxID_OK) this->mData = dlg.GetValue();
        dlg.Destroy();
    }
};


#endif /* mcAction_hpp */
