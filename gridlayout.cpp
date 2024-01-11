#include "gridlayout.h"
#include "card.h"
#include <QGridLayout>
#include <QWidget>
#include <QTest>
#include <QLabel>
#include <QMessageBox>

GridLayout::GridLayout()
{
    numberOfTries = 0;
    score = 0;

    gridLayout = new QGridLayout;
    setLayout(gridLayout);
    scoreLabel = new QLabel("Score: 0");
    triesLabel = new QLabel("No. of Tries Remaining: 50");
    newGameButton = new QPushButton("New Game");
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameSlot()));

    // place the two QLabels and a QPushButton on the first row of the grid, each stretching two columns
    gridLayout->addWidget(scoreLabel, 0, 0, 1, 2);
    gridLayout->addWidget(triesLabel, 0, 2, 1, 2);
    gridLayout->addWidget(newGameButton, 0, 4, 1, 2);

    // first row consists of QLabels and a QPushbutton. Cards start from the second row
    for(int i=1; i<6; i++){
        for(int j=0; j<6; j++){
            Card *card = new Card();
            gridLayout->addWidget(card, i, j);
            connect(card, SIGNAL(chosenSignal(int,int)), this, SLOT(cardChosen(int,int)));
        }
    }
}

void GridLayout::cardChosen(int row, int column){
    // if two cards are selected, wait one or half a second.
    if(twoCardsSelected){
        return;
    }

    QMessageBox msgBox;
    if(numberOfTries == 50){

        msgBox.setText("You lost! Your score: " + QString::number(score));
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        return;
    }

    // layout() retruns the layout manager that is installed with setLayout(gridLayout)
    QGridLayout *grid = static_cast<QGridLayout*>(layout());

    // to retrieve the selected card from the grid, type cast the returned widget into card
    Card *curCard = static_cast<Card*>(grid->itemAtPosition((row), (column))->widget());
    curCard->setCardMode(Card::SELECTED);

    // if this is the first selected card, then save its coordinates
    if(!oneCardSelected){
        first_selected_row = row;
        first_selected_column = column;
        oneCardSelected = true;
    }
    // if two cards are selected enter else
    else{
        Card *prevCard = static_cast<Card*>(grid->itemAtPosition((first_selected_row),
                                                                 (first_selected_column))->widget());

        // if two animal names are the same, update the labels and modes of the cards
        if(prevCard->getName().compare(curCard->getName()) == 0){
            score++;
            numberOfTries++;
            scoreLabel->setText("Score: " + QString::number(score));
            triesLabel->setText("No. of Tries Remaining: " + QString::number(50-numberOfTries));

            // twoCardsSelected and qWait prevents clicking any other buttons
            twoCardsSelected = true;
            QTest::qWait(500);
            prevCard->setCardMode(Card::FOUND);
            curCard->setCardMode(Card::FOUND);
            twoCardsSelected = false;
            oneCardSelected = false;

            if(score == 15){

                msgBox.setText("You won in " + QString::number(numberOfTries)
                               + " tries!");
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.exec();
            }

        }
        // if the two animal names are not the same, update the labels and make the cards hidden
        else{
            numberOfTries++;
            triesLabel->setText("No. of Tries Remaining: " + QString::number(50-numberOfTries));

            // twoCardsSelected and qWait prevents clicking any other buttons
            twoCardsSelected = true;
            QTest::qWait(1000);
            prevCard->setCardMode(Card::HIDDEN);
            curCard->setCardMode(Card::HIDDEN);
            twoCardsSelected = false;
            oneCardSelected = false;

            if(numberOfTries == 50){

                msgBox.setText("You lost! Your score: " + QString::number(score));
                msgBox.setStandardButtons(QMessageBox::Cancel);
                msgBox.exec();
                return;
            }
        }

    }

}

// reset the values of the members and randomly assign the animal names to the cards
void GridLayout::newGameSlot(){

    if(twoCardsSelected)
        return;

    numberOfTries = 0;
    score = 0;
    oneCardSelected = false;
    twoCardsSelected = false;
    Card::numberOfCards = 0;
    scoreLabel->setText("Score: 0");
    triesLabel->setText("No. of Tries Remaining: 50");

    QStringList tempList;
    for( QString s : animalNames)
           tempList.append(s);

    for(int i=1; i<6; i++){ // first row does not include any card objects
        for(int j=0; j<6; j++){

            QGridLayout *grid = static_cast<QGridLayout*>(layout());
            Card *card = static_cast<Card*>(grid->itemAtPosition((i), (j))->widget());
            card->setCardMode(Card::HIDDEN);

            srand((unsigned) time(NULL));
            int rand_index = rand() % (30 - Card::numberOfCards);
            QString nameOfCard = tempList[rand_index];
            tempList.removeAt(rand_index);
            Card::numberOfCards++;
            card->setCardName(nameOfCard);
        }
    }
}

// it is a flag for the cases when two cards are selected.
// it prevents clicking another card for a determined time
bool GridLayout::twoCardsSelected = false;

// it is a flag for saving the card's coordinates on the grid's properties.
// if only one card is selected, its coordinates are saved
bool GridLayout::oneCardSelected = false;

// when the newGame button is clicked, the names of the cards on the playing grid
// are randomly assigned from this list
QStringList GridLayout::animalNames = {
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
