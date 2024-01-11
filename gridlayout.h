#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class GridLayout : public QWidget
{
    Q_OBJECT
public:
    GridLayout();
private:
    int first_selected_row, first_selected_column;
    int numberOfTries;
    int score;
    static bool twoCardsSelected;
    static bool oneCardSelected;
    QLabel *scoreLabel;
    QLabel *triesLabel;
    QPushButton *newGameButton;
    static QStringList animalNames;
    QGridLayout *gridLayout;
public slots:
    void cardChosen(int, int);
    void newGameSlot();

};

#endif // GRIDLAYOUT_H
