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
    virtual void execute() {}
};

template<class T>
class mcPrompt : public mcAction {
public:
    mcPrompt(const string& prmpt, T& dataRef) : mInquiry(prmpt), mData(dataRef) {}
    virtual void execute() override {
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
    mcDialogPrompt(wxWindow* parent, const std::string& prompt, T& data) : mcPrompt<T>(prompt, data) {
        QueryToType<T> qry = QueryToType<T>(prompt, data);
        wxNumberEntryDialog* prmttext = new wxNumberEntryDialog(parent, "msg",
                                                                "prmt",
                                                                "cap",
                                                                5000,
                                                                0,
                                                                10000000);
        
//        prmttext->ShowModal();
        prmttext->GetValue();
    }
    
};


#endif /* mcAction_hpp */
