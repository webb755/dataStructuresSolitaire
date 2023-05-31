/* Program name: finalHeader
* Author: Ben Webb
* Date last updated: 4/12/23
* Purpose: 
*/

#ifndef FPEN_H
#define FPEN_H
//#ifndef FINALHEADER_H
//#define FINALHEADER_H

#include<string>
#include <stdexcept>
#include <map>
#include <iostream>

enum suit {SPADE, CLUB, HEART, DIAMOND};

///////////////card class object to describe each card///////////////////
/*
program will start by creating 52 of these 
using the create deck() function 
such that they match cards in a deck for each needed deck 
*/
class card{
    private:
        int cardRank;
        suit cardSuit;

    public:
        card(suit, int);
        card();
        card(const card&);
        int getRank();
        suit getSuit();
        int hash();
        bool operator >(const card&);
        bool operator <(const card&);
        bool operator >=(const card&);
        bool operator <=(const card&);
        bool operator ==(const card&);
        bool operator !=(const card&);
        friend std::ostream& operator<<(std::ostream&, const card&);
};










#endif