#include <gridlayout.h>
#include <card.h>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char **argv){
    QApplication app(argc, argv);

    QMainWindow *mw = new QMainWindow;
    GridLayout *gl = new GridLayout;

    mw->setCentralWidget(gl);
    mw->resize(640, 540);
    mw->setWindowTitle("Pairs Game");
    mw->show();
    return app.exec();
}
