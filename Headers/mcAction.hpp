//
//  mcAction.hpp
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcAction_hpp
#define mcAction_hpp

struct mcAction {
    mcAction() {}
    virtual ~mcAction() {}
    virtual void execute() {}
};

template<class T>
class mcPrompt : public mcAction {
public:
    mcPrompt(const string& prmpt, T& dataRef) : inquiry(prmpt), data(dataRef) {}
    virtual void execute() override{
        QueryToType<T> q = QueryToType<T>(inquiry, data);
        cin >> q;
    }
    
    const string& getString() const { return inquiry; }
    
private:
    string inquiry;
    T& data;
};

#endif /* mcAction_hpp */
