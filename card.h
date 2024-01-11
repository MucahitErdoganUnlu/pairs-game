#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QWidget>

class Card : public QWidget
{
    Q_OBJECT
public:
    Card();
    enum Modes{
        HIDDEN,
        SELECTED,
        FOUND
    };
    QString getName();
    Modes getCardMode();
    void setCardMode(Card::Modes);
    static int numberOfCards;
    inline void setCardName(QString name){ nameOfCard = name; }

private:
    int row, column;
    QString nameOfCard;
    static QStringList animalNames;
    Modes modeOfCard;
    QPushButton *cardButton;

public slots:
    void clickSlot();

signals:
    void chosenSignal(int, int);
};

#endif // CARD_H
