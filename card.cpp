#include "card.h"
#include "gridlayout.h"

Card::Card()
{
    row = (numberOfCards / 6) + 1;  // first row consists of 2 QLabels and a QPushbutton
    column = numberOfCards % 6;

    { // randomly assign an animal name to the nameOfCard
        srand((unsigned) time(NULL));
        int rand_index = rand() % (30 - numberOfCards);
        nameOfCard = animalNames[rand_index];
        animalNames.removeAt(rand_index);
        numberOfCards++;
    }

    { // configure the card's initial situation.
        modeOfCard = HIDDEN;
        cardButton = new QPushButton("?", this);
        connect(cardButton, SIGNAL(clicked()), this, SLOT(clickSlot()));
        cardButton->resize(90, 90);
    }

}

QString Card::getName(){
    return nameOfCard;
}

Card::Modes Card::getCardMode(){
    return modeOfCard;
}

// mode changes manipulate the text on the buttons
void Card::setCardMode(Card::Modes card_mode){
    modeOfCard = card_mode;
    if(modeOfCard == HIDDEN){
        cardButton->setText("?");
    }else if(modeOfCard == SELECTED){
        cardButton->setText(nameOfCard);
    }else if(modeOfCard == FOUND){
        cardButton->setText("");
    }
}

// if a button is clicked, emit a signal only if it is hidden. otherwise, do nothing.
void Card::clickSlot(){
    if(modeOfCard == HIDDEN){
        emit chosenSignal(row, column);
    }
}

// it is static member. it helps us to determine the coordinates of each card on the grid.
int Card::numberOfCards = 0;

// when a card object is created, random animal names are selected from this list.
QStringList Card::animalNames = {
    "Dog", "Dog",
    "Cat", "Cat",
    "Elephant", "Elephant",
    "Lion", "Lion",
    "Tiger", "Tiger",
    "Monkey", "Monkey",
    "Giraffe", "Giraffe",
    "Zebra", "Zebra",
    "Kangaroo", "Kangaroo",
    "Bear", "Bear",
    "Horse", "Horse",
    "Rabbit", "Rabbit",
    "Dolphin", "Dolphin",
    "Penguin", "Penguin",
    "Eagle", "Eagle"
};

