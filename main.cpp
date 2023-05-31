/* Program name: solitaire
* Author: Ben Webb
* Date last updated: 4/12/23
* Purpose:  play windmill game
*/

#include <iostream>
#include "finalHeader.h"
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include "stack.h"
#include "orderedLinkedList.h"
#include "foundationList.h"
#include "hashTable.h"
#include "buildUpFoundation.h"

hashTable<card> makeWindmillDeck(); //makes shuffled 52 card deck minus two kings
int mainMenu();
void pullKingFoundation(stackType<card>& windmillDeck, stackType<card>& discard, foundationList<card>& windmillReserve, stackType<card>& aceFoundation, stackType<card>& winPile, foundationList<stackType<card>>& kingFoundations);
int chooseKingFoundation(foundationList<stackType<card>> &kingFoundations);
void pullWindmill(stackType<card>& windmillDeck, stackType<card>& discard, foundationList<card>& windmillReserve, stackType<card>& aceFoundation, stackType<card>& winPile, foundationList<stackType<card>>& kingFoundations);
void pullDeck(stackType<card>& windmillDeck, stackType<card>& discard, foundationList<card>& windmillReserve, stackType<card>& aceFoundation, stackType<card>& winPile, foundationList<stackType<card>>& kingFoundations);
void pullCenterFoundation(stackType<card>& windmillDeck, stackType<card>& discard, foundationList<card>& windmillReserve, stackType<card>& aceFoundation, stackType<card>& winPile, foundationList<stackType<card>>& kingFoundations);
void pullDiscard(stackType<card>& windmillDeck, stackType<card>& discard, foundationList<card>& windmillReserve, stackType<card>& aceFoundation, stackType<card>& winPile, foundationList<stackType<card>>& kingFoundations);


int main(){    
    //we start by creating needed decks
    hashTable<card> baseDeck1 = makeWindmillDeck();
    hashTable<card> baseDeck2 = makeWindmillDeck();

    //initialize needed structures for game
    stackType<card> windmillDeck; //starting deck of 104 cards
    stackType<card> discard;    //discard pile
    foundationList<card> windmillReserve;//8 card "windmill" (reserve)
    stackType<card> aceFoundation;  //center of windmill builds up from ace to king
    stackType<card> winPile;    //stack holds all cards from completed foundations
    foundationList<stackType<card>> kingFoundations;  //list of foundation stacks (starts emtpy and builds down from king to ace)
    for (int i=0; i<4; i++){
        stackType<card> tempFoundation;
        kingFoundations.insert(tempFoundation);
    }    

    /*windmill starts with 104 cards and one ace in the windmill*/
    //build full starting deck and put one ace in reserve
    for (int i=0; i<52; i++){   
        //push all baseDeck cards into deck
        windmillDeck.push(baseDeck1.at(i));
        windmillDeck.push(baseDeck2.at(i));
        if (aceFoundation.isEmptyStack()){/*first ace found while building deck starts aceFoundation*/
            if (windmillDeck.top().getRank() == 0){
                aceFoundation.push(windmillDeck.top());
                windmillDeck.pop();
            }
        }        
    }
    //populate windmill with top 8 cards
    card tempCard(SPADE, 2);
    windmillReserve.insert(tempCard);
    /* for (int i=0; i<8; i++){
        windmillReserve.insert(windmillDeck.top());
        windmillDeck.pop();
    } */

    

    

    /*we are now set up to play windmill*/
    std::cout   << "It's Time to play Windmill!!!\n"
                << "windmill reserve holds 8 cards you may play to any foundation\n"
                << "4 foundations you build from king down to ace as kings are revealed\n"
                << "1 foundation you will start with an ace at the begining of game must build up to king 4 times\n"
                << "you may move any face-up card to any foundation or open windmill space\n\n";

    
    
    
    while(!winPile.isFullStack()){
        //print reserve
        std::cout << "windmill reserve: ";
        if (windmillReserve.isEmptyList())
            std::cout << "FUUUUUCK\n\n\n";
        for (int i=0; i<windmillReserve.getSize(); i++)
            std::cout << windmillReserve.at(i) << ", ";
        //print discard
        std::cout << "\ncurrent discard: ";
        if (!discard.isEmptyStack()){
            std::cout << discard.top() << std::endl;
        }else{        
            std::cout << "none\n";
        }
        //print kingFoundations
        std::cout << "top of king foundations (build down): ";
        if (!kingFoundations.isEmptyList()){
            for (linkedListIterator<stackType<card>> it = kingFoundations.begin(); it != kingFoundations.end(); ++it){
                std::cout << it.operator*().top();
            }
            std::cout << "\n";
        } else {
            std::cout << "none\n";
        }
        //print center foundation
        std::cout << "top of center foundation (builds up): " << aceFoundation.top() << std::endl;

        switch (mainMenu()){
            case 1://pull king foundation
                pullKingFoundation(windmillDeck, discard, windmillReserve, aceFoundation, winPile, kingFoundations);
                break;
            case 2://pull windmill
                pullWindmill(windmillDeck, discard, windmillReserve, aceFoundation, winPile, kingFoundations);
                break;
            case 3://pull deck
                pullDeck(windmillDeck, discard, windmillReserve, aceFoundation, winPile, kingFoundations);
                break;
            case 4://pull ace foundation
                pullCenterFoundation(windmillDeck, discard, windmillReserve, aceFoundation, winPile, kingFoundations);
                break;
            case 5://pull discard
                pullDiscard(windmillDeck, discard, windmillReserve, aceFoundation, winPile, kingFoundations);
                break;
            default:
                std::cout << "Ya done broke it!\n";
        }


    }
    


    /*
    after each play, we check to see if any foundations are full.
    any that are will be dumped into winPile
    */
    if (aceFoundation.getCount() == 13){
        while (!aceFoundation.isEmptyStack()){
            winPile.push(aceFoundation.top());
            aceFoundation.pop();
        }
    }
    if (!kingFoundations.isEmptyList()){
        for (linkedListIterator<stackType<card>> it = kingFoundations.begin(); it != kingFoundations.end(); ++it){
            //std::cout << it.operator*().top();            
        }
    }


 
    

    return 0;
}




/*
this function loads a full deck in order of card value into a hash table
the hash on card objects is always the same, 
so using the random probe effectively shuffles the deck
*/
hashTable<card> makeWindmillDeck()
{
    hashTable<card> tempDeck(52);
    //stackType<card> finalDeck;

    //loops to make deck
    for (int s=0; s<4; s++){   //runs once for each suit
        suit tempSuit;
        switch (s){
            case 0:
                tempSuit = SPADE;
                break;
            case 1:
                tempSuit = CLUB;
                break;
            case 2:
                tempSuit = HEART;
                break;
            case 3:
                tempSuit = DIAMOND;
                break;
            default:
                throw (tempSuit);
        }
        for (int i=0; i<13; i++){    //inner loop runs the 13 ranks into each suit
            //shuffle using random probe where hash is always 0
            card tempCard(tempSuit, i);
            tempDeck.insertRandomProbe(tempCard);
        }
    }
    
    /* for (int i=0; i<52; i++){
        //card foundationKing();
        //if (tempDeck.at(i).getRank() == 13 && foundationCount < 3)
            finalDeck.push(tempDeck.at(i));
    } */
 
    //return finalDeck;
    return tempDeck;
}

int mainMenu()
{
    int choice =0;
    std::cout   << "Enter number of menu option:\n"
                << "1. Pull card from one of the king foundations\n"
                << "2. Pull card from windmill\n"
                << "3. Pull card from deck\n"
                << "4. Pull card from ace foundation\n"
                << "5. Pull last card discarded\n";
    std::cin >> choice;
    while (std::cin.fail() || choice < 1 || choice > 5){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and 5: ";
        std::cin >> choice;
    }

    return choice;
}






void pullKingFoundation(stackType<card> &windmillDeck, stackType<card> &discard, foundationList<card> &windmillReserve, stackType<card> &aceFoundation, stackType<card> &winPile, foundationList<stackType<card>> &kingFoundations){
    if (kingFoundations.isEmptyList()){
        std::cout << "you need to start a foundation by placing a king\n" << "enter any character to go back: ";
        char back;
        std::cin>>back;
    } else {
        //int pullCard = pullKingFoundation(kingFoundations);
        //select foundation from which to pull
        std::cout << "select number of chosen card:\n";
        int foundationListNumber = 1;
        for (linkedListIterator<stackType<card>> it = kingFoundations.begin(); it != kingFoundations.end(); ++it){
            std::cout << foundationListNumber << " " << it.operator*().top() << std::endl;
            foundationListNumber++;
        }
        int pullChoice;
        std::cin >> pullChoice;
        while (std::cin.fail() || pullChoice < 1 || pullChoice > foundationListNumber){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "invalid input, please enter a number between 1 and " << foundationListNumber << ": ";
            std::cin >> pullChoice;
        }

        //display pulled card
        std::cout << "Here is the card you pulled: " << kingFoundations.at(pullChoice).top() << std::endl;

        std::cout   << "where would you like to put it?\n"
                    << "1. A King foundation ("; 
        for (linkedListIterator<stackType<card>> it = kingFoundations.begin(); it != kingFoundations.end(); ++it){
            std::cout << it.operator*().top();  
        }          
        std::cout   << ")   \n2. Center (Ace) foundation(showing: " << aceFoundation.top() << ")   \n3. The windmill(has " << windmillReserve.getSize() << " of 8 cards)   \n4. Discard pile   \nyour choice: ";

        //select where to play card
        int playChoice;
        std::cin >> playChoice;
        while (std::cin.fail() || playChoice < 1 || playChoice > 4){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "invalid input, please enter a number between 1 and 4: ";
            std::cin >> playChoice;
        }
        switch(playChoice){
            case 1:/*king foundation*/
                //find valid play
                for (int i=0; i<kingFoundations.getSize(); i++){
                    if (kingFoundations.at(i).top().getRank() == (kingFoundations.at(pullChoice).top().getRank() + 1)){
                        kingFoundations.at(playChoice).push(kingFoundations.at(pullChoice).top());
                        kingFoundations.at(pullChoice).pop();
                        std::cout << "added to valid stack\n";
                    }
                }
                break;
            case 2:/*center foundation*/
                if (aceFoundation.top().getRank() == (kingFoundations.at(pullChoice).top().getRank() - 1)){
                    aceFoundation.push(kingFoundations.at(pullChoice).top());
                    kingFoundations.at(pullChoice).pop();
                }                
                break;
            case 3:/*windmill*/
                if (windmillReserve.getSize() < 8){
                    windmillReserve.insert(kingFoundations.at(pullChoice).top());
                    kingFoundations.at(pullChoice).pop();
                }else{
                    std::cout << "no available play!\n";
                }
                break;
            case 4:/*discard*/
                discard.push(kingFoundations.at(pullChoice).top());
                kingFoundations.at(pullChoice).pop();
                break;
            default:
                break;
        }
    }
    
}





void pullWindmill(stackType<card> &windmillDeck, stackType<card> &discard, foundationList<card> &windmillReserve, stackType<card> &aceFoundation, stackType<card> &winPile, foundationList<stackType<card>> &kingFoundations){
    //choose card to pull
    std::cout << "select number above chosen card to pull: \n" << "1   2   3   4   5   6   7   8\n";
    for (int i=0; i<windmillReserve.getSize(); i++)
        std::cout << windmillReserve.at(i) << "  ";
        
    std::cout << "\n";

    int pullChoice;
    std::cin >> pullChoice;
    while (std::cin.fail() || pullChoice < 1 || pullChoice > windmillReserve.getSize()){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and " << windmillReserve.getSize() << ": ";
        std::cin >> pullChoice;
    }


    /* std::cout   << "where would you like to put it?\n"
                << "1. A King foundation     2. Center (Ace) foundation     3. The windmill     4. Discard pile     your choice: "; */
                //display pulled card
    std::cout << "Here is the card you pulled: " << kingFoundations.at(pullChoice).top() << std::endl;
    std::cout   << "where would you like to put it?\n"
                << "1. A King foundation ("; 
    for (linkedListIterator<stackType<card>> it = kingFoundations.begin(); it != kingFoundations.end(); ++it){
        std::cout << it.operator*().top();  
    }          
    std::cout   << ")   \n2. Center (Ace) foundation(showing: " << aceFoundation.top() << ")   \n3. The windmill(has " << windmillReserve.getSize() << " of 8 cards)   \n4. Discard pile   \nyour choice: ";
 
    //select where to play card
    int playChoice;
    std::cin >> playChoice;
    while (std::cin.fail() || playChoice < 1 || playChoice > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and 4: ";
        std::cin >> playChoice;
    }
    switch(playChoice){
        case 1:{/*king foundation*/
            int valid = 0;
            if (kingFoundations.at(valid).top().getRank() == (windmillReserve.at(pullChoice).getRank() + 1)){
                kingFoundations.at(playChoice).push(windmillReserve.at(pullChoice));
                windmillReserve.deleteNode(windmillReserve.at(pullChoice));
            }else{
                std::cout << "no available play\n";
            }
        }                
            break;
        case 2:{/*center foundation*/
            if (aceFoundation.top().getRank() == (windmillReserve.at(pullChoice).getRank() - 1)){
                aceFoundation.push(windmillReserve.at(pullChoice));
                windmillReserve.deleteNode(windmillReserve.at(pullChoice));
            }else{
                std::cout << "invalid play\n";
            }            
            break;
        }
        case 3:{/*windmill*/
            if (windmillReserve.getSize() < 8){
                windmillReserve.insert(windmillReserve.at(pullChoice));
                windmillReserve.deleteNode(windmillReserve.at(pullChoice));
            }else{
                std::cout << "no available play!\n";
            }
            break;
        }
        case 4:{/*discard*/
            discard.push(windmillReserve.at(pullChoice));
            windmillReserve.deleteNode(windmillReserve.at(pullChoice));
            break;
        }
        default: break;
    }
    
}




void pullDeck(stackType<card> &windmillDeck, stackType<card> &discard, foundationList<card> &windmillReserve, stackType<card> &aceFoundation, stackType<card> &winPile, foundationList<stackType<card>> &kingFoundations){
    //pull card
    card pulledCard(windmillDeck.top().getSuit(), windmillDeck.top().getRank());
    windmillDeck.pop();

    //select where to play card
    std::cout   << "where would you like to put it?\n"
                << "1. A King foundation     2. Center (Ace) foundation     3. The windmill     4. Discard pile     your choice: ";
    int playChoice;
    std::cin >> playChoice;
    while (std::cin.fail() || playChoice < 1 || playChoice > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and 4: ";
        std::cin >> playChoice;
    }
    switch(playChoice){
        case 1:{/*king foundation*/
            int valid = 0;
            if (kingFoundations.at(valid).top().getRank() == (pulledCard.getRank() + 1)){
                kingFoundations.at(playChoice).push(pulledCard);
            }else{
                std::cout << "not available play!  Putting in discard\n";
                discard.push(pulledCard);
            }
        }                
            break;
        case 2:{/*center foundation*/
            if (aceFoundation.top().getRank() == (pulledCard.getRank() - 1)){
                aceFoundation.push(pulledCard);
            }else{
                std::cout << "not available play!  Putting in discard\n";
                discard.push(pulledCard);
            }            
            break;
        }
        case 3:{/*windmill*/
            if (windmillReserve.getSize() < 8){
                windmillReserve.insert(pulledCard);
            }else{
                std::cout << "no available play!\n";
                discard.push(pulledCard);
            }
            break;
        }
        case 4:{/*discard*/
            discard.push(pulledCard);
            break;
        }
        default:
            discard.push(pulledCard);
            break;
    }
}





void pullCenterFoundation(stackType<card> &windmillDeck, stackType<card> &discard, foundationList<card> &windmillReserve, stackType<card> &aceFoundation, stackType<card> &winPile, foundationList<stackType<card>> &kingFoundations){
    //pull card from aceFoundation
    card pulledCard(aceFoundation.top().getSuit(), aceFoundation.top().getRank());
    aceFoundation.pop();

    //select where to play card
    std::cout   << "where would you like to put it?\n"
                << "1. A King foundation     2. Center (Ace) foundation     3. The windmill     4. Discard pile     your choice: ";
    int playChoice;
    std::cin >> playChoice;
    while (std::cin.fail() || playChoice < 1 || playChoice > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and 4: ";
        std::cin >> playChoice;
    }
    switch(playChoice){
        case 1:{/*king foundation*/
            int valid = 0;
            if (kingFoundations.at(valid).top().getRank() == (pulledCard.getRank() + 1)){
                kingFoundations.at(playChoice).push(pulledCard);
            }else{
                std::cout << "not available play!  Putting in discard\n";
                discard.push(pulledCard);
            }
        }                
            break;
        case 2:{/*center foundation*/
            if (aceFoundation.top().getRank() == (pulledCard.getRank() - 1)){
                aceFoundation.push(pulledCard);
            }else{
                std::cout << "not available play!  Putting in discard\n";
                discard.push(pulledCard);
            }            
            break;
        }
        case 3:{/*windmill*/
            if (windmillReserve.getSize() < 8){
                windmillReserve.insert(pulledCard);
            }else{
                std::cout << "no available play!  Putting in discard\n";
                discard.push(pulledCard);
            }
            break;
        }
        case 4:{/*discard*/
            discard.push(pulledCard);
            break;
        }
        default: 
            discard.push(pulledCard);
            break;
    }
}

void pullDiscard(stackType<card> &windmillDeck, stackType<card> &discard, foundationList<card> &windmillReserve, stackType<card> &aceFoundation, stackType<card> &winPile, foundationList<stackType<card>> &kingFoundations){
    //pull card
    card pulledCard(discard.top().getSuit(), discard.top().getRank());
    discard.pop();

    //select where to play card
    std::cout   << "where would you like to put it?\n"
                << "1. A King foundation     2. Center (Ace) foundation     3. The windmill     4. Discard pile     your choice: ";
    int playChoice;
    std::cin >> playChoice;
    while (std::cin.fail() || playChoice < 1 || playChoice > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "invalid input, please enter a number between 1 and 4: ";
        std::cin >> playChoice;
    }
    switch(playChoice){
        case 1:{/*king foundation*/
            int valid = 0;
            if (kingFoundations.at(valid).top().getRank() == (pulledCard.getRank() + 1)){
                kingFoundations.at(playChoice).push(pulledCard);
            }else{
                std::cout << "not available play!  Putting back in discard\n";
                discard.push(pulledCard);
            }
        }                
            break;
        case 2:{/*center foundation*/
            if (aceFoundation.top().getRank() == (pulledCard.getRank() - 1)){
                aceFoundation.push(pulledCard);
            }else{
                std::cout << "invalid play\n";
            }            
            break;
        }
        case 3:{/*windmill*/
            if (windmillReserve.getSize() < 8){
                windmillReserve.insert(pulledCard);
            }else{
                std::cout << "no available play!  Putting back in discard\n";
                discard.push(pulledCard);
            }
            break;
        }
        case 4:{/*discard*/
            discard.push(pulledCard);
            break;
        }
        default: 
            discard.push(pulledCard);
            break;
    }
}
