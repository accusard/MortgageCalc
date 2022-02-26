//
//  mcChildFrame.hpp
//  dynamic
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcChildFrame_hpp
#define mcChildFrame_hpp

#include "wx/mdi.h"




class mcChildFrame : public wxMDIChildFrame {
public:
    mcChildFrame(wxMDIParentFrame* parent, const wxString& name);
    ~mcChildFrame();
    
    
private:
    

};

#endif /* mcChildFrame_hpp */
