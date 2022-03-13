//
//  mcType.h
//  MortgageCalc
//
//  (c) Vanny Sou on 2021-2022
//

#ifndef mcType_h
#define mcType_h

const wxPoint DEFAULT_POS_MBP = wxPoint(0,38);
const int DEFAULT_VSIZE_LOAN_WIN = 685;
const int DEFAULT_COLUMN_WIDTH = 150;
const uint MAX_DOLLAR_AMOUNT = 2000000;

const int mcID_SLIDER               = wxID_HIGHEST + 100;
const int mcID_EDITABLE_LIST        = wxID_HIGHEST + 1;
const int mcID_MORTGAGE_LOANBOOK    = wxID_HIGHEST + 2;


struct MaxSet {
    uint mValue;
    long mMaxValue;
};

#endif /* mcType_h */
