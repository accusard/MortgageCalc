//
//  mcAction.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcAction_hpp
#define mcAction_hpp
#include "wx/numdlg.h"
#include "mcType.h"

struct mcAction {
    mcAction() {}
    virtual ~mcAction() {}
    virtual void show() {}
};

template<class T>
class mcPrompt : public mcAction {
public:
    mcPrompt(const string& prmpt, T& dataRef, const uint max_value) : mInquiry(prmpt), mData(dataRef), maxValue(max_value) {}
    virtual void show() override {
        QueryToType<T> q = QueryToType<T>(mInquiry, mData);
        cin >> q;
        cout << "Done." << endl;
    }
    
    const string& getString() const { return mInquiry; }
    T& getData() const { return mData; }
    const uint getMax() const { return maxValue; }
protected:
    string mInquiry;
    T& mData;
    uint maxValue;
};

template<class T>
class mcDialogPrompt : public mcPrompt<T> {
public:
    mcDialogPrompt(const std::string& prompt, T& data, const uint max_value = MAX_DOLLAR_AMOUNT) : mcPrompt<T>(prompt, data, max_value) {}
    
    virtual void show() override {
        wxNumberEntryDialog dlg;
        dlg.Create(nullptr, "", this->mInquiry, "Enter New Value", this->mData, 0, this->maxValue);
        if(dlg.ShowModal() == wxID_OK) this->mData = dlg.GetValue();
        dlg.Destroy();
    }
};


#endif /* mcAction_hpp */
