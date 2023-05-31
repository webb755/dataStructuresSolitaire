//include your header file
#include "finalHeader.h"

////////////////card class definitions/////////////////



card::card(suit cardSuit, int cardRank)
{
    this->cardRank = cardRank;
    this->cardSuit = cardSuit;
}

card::card()
{
    cardRank = 14;
}

card::card(const card &item)
{
    this->cardRank = item.cardRank;
    this->cardSuit = item.cardSuit;
}

int card::getRank()
{
    return cardRank;
}

suit card::getSuit()
{
    return cardSuit;
}

int card::hash()
{
    return 0;
}


bool card::operator>(const card &otherCard)     {    return this->cardRank > otherCard.cardRank;    }
bool card::operator<(const card &otherCard)     {    return this->cardRank < otherCard.cardRank;    }
bool card::operator>=(const card &otherCard)    {    return this->cardRank >= otherCard.cardRank;   }
bool card::operator<=(const card &otherCard)    {    return this->cardRank <= otherCard.cardRank;   }
bool card::operator==(const card &otherCard)    {    return this->cardRank == otherCard.cardRank;   }
bool card::operator!=(const card &otherCard)    {    return this->cardRank != otherCard.cardRank;   }

std::ostream &operator<<(std::ostream &output, const card &c)
{
    std::string suit, rank;
    switch (c.cardSuit){
        case SPADE:
            suit = "♠";
            break;
        case CLUB:
            suit = "♣";
            break;
        case HEART:
            suit = "♥";
            break;
        case DIAMOND:
            suit = "♦";
            break;
        default:
            throw (suit);
    }
    switch (c.cardRank)
    {
    case 0:
        rank = 'A';
        break;
    case 11:
        rank = 'J';
        break;
    case 12:
        rank = 'Q';
        break;
    case 13:
        rank = 'K';
        break;  
    default:
        rank = std::to_string(c.cardRank + 1);
        break;
    }
    output << suit << rank;
    return output;
}
