#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow menu;
    menu.set(0);

    QPushButton one("one player",&menu);
    one.resize(120,60);
    one.move (330,250);
    one.setStyleSheet("QPushButton{font:20px;}");

    QPushButton two("two players",&menu);
    two.resize(120,60);
    two.move (330,350);
    two.setStyleSheet("QPushButton{font:20px;}");

    QPushButton exit("exit",&menu);
    exit.resize(120,60);
    exit.move (330,450);
    exit.setStyleSheet("QPushButton{font:20px;}");

    MainWindow FirstStage;
    FirstStage.set(1);

    QPushButton exita("exit",&FirstStage);
    exita.resize(120,60);
    exita.move (830,100);
    exita.setStyleSheet("QPushButton{font:20px;}");

    QPushButton nextb("next",&FirstStage);
    nextb.resize(120,60);
    nextb.move (830,200);
    nextb.setStyleSheet("QPushButton{font:20px;}");

    MainWindow FirstStage_2P;
    FirstStage_2P.set(4);

    QPushButton exitaa("exit",&FirstStage_2P);
    exitaa.resize(120,60);
    exitaa.move (830,100);
    exitaa.setStyleSheet("QPushButton{font:20px;}");

    QPushButton nextbb("next",&FirstStage_2P);
    nextbb.resize(120,60);
    nextbb.move (830,200);
    nextbb.setStyleSheet("QPushButton{font:20px;}");

    MainWindow Secondstage;
    Secondstage.set(2);

    QPushButton next("next",&Secondstage);
    next.resize(120,60);
    next.move (830,200);
    next.setStyleSheet("QPushButton{font:20px;}");

    QPushButton exitb("exit",&Secondstage);
    exitb.resize(120,60);
    exitb.move (830,100);
    exitb.setStyleSheet("QPushButton{font:20px;}");

    MainWindow Secondstage_2P;
    Secondstage_2P.set(5);

    QPushButton nextt("next",&Secondstage_2P);
    nextt.resize(120,60);
    nextt.move (830,200);
    nextt.setStyleSheet("QPushButton{font:20px;}");

    QPushButton exitbb("exit",&Secondstage_2P);
    exitbb.resize(120,60);
    exitbb.move (830,100);
    exitbb.setStyleSheet("QPushButton{font:20px;}");

    MainWindow Thirdstage;
    Thirdstage.set(3);

    QPushButton nextc("next",&Thirdstage);
    nextc.resize(120,60);
    nextc.move (830,200);
    nextc.setStyleSheet("QPushButton{font:20px;}");

    QPushButton exitc("exit",&Thirdstage);
    exitc.resize(120,60);
    exitc.move (830,100);
    exitc.setStyleSheet("QPushButton{font:20px;}"); 

    MainWindow Thirdstage_2P;
    Thirdstage_2P.set(6);

    QPushButton nextcc("next",&Thirdstage_2P);
    nextcc.resize(120,60);
    nextcc.move (830,200);
    nextcc.setStyleSheet("QPushButton{font:20px;}");

    QPushButton exitcc("exit",&Thirdstage_2P);
    exitcc.resize(120,60);
    exitcc.move (830,100);
    exitcc.setStyleSheet("QPushButton{font:20px;}"); 

    MainWindow youwin;
    youwin.set(7);
    MainWindow youlose;
    youlose.set(8);

    QObject::connect(&one,&QPushButton::clicked,&menu,&MainWindow::close);
    QObject::connect(&one,&QPushButton::clicked,&FirstStage,&MainWindow::show);
    QObject::connect(&two,&QPushButton::clicked,&menu,&MainWindow::close);
    QObject::connect(&two,&QPushButton::clicked,&FirstStage_2P,&MainWindow::show);
    QObject::connect(&exit,&QPushButton::clicked,&menu,&MainWindow::close);

    QObject::connect(&exita,&QPushButton::clicked,&FirstStage,&MainWindow::close);
    QObject::connect(&exitb,&QPushButton::clicked,&Secondstage,&MainWindow::close);
    QObject::connect(&exitc,&QPushButton::clicked,&Thirdstage,&MainWindow::close);
    QObject::connect(&exitaa,&QPushButton::clicked,&FirstStage_2P,&MainWindow::close);
    QObject::connect(&exitbb,&QPushButton::clicked,&Secondstage_2P,&MainWindow::close);
    QObject::connect(&exitcc,&QPushButton::clicked,&Thirdstage_2P,&MainWindow::close);

    
    QObject::connect(&nextb,&QPushButton::clicked,&FirstStage,&MainWindow::close);
    QObject::connect(&nextb,&QPushButton::clicked,&Secondstage,&MainWindow::show);      
    QObject::connect(&next,&QPushButton::clicked,&Secondstage,&MainWindow::close);
    QObject::connect(&next,&QPushButton::clicked,&Thirdstage,&MainWindow::show);

    QObject::connect(&nextbb,&QPushButton::clicked,&FirstStage_2P,&MainWindow::close);
    QObject::connect(&nextbb,&QPushButton::clicked,&Secondstage_2P,&MainWindow::show);
    QObject::connect(&nextt,&QPushButton::clicked,&Secondstage_2P,&MainWindow::close);
    QObject::connect(&nextt,&QPushButton::clicked,&Thirdstage_2P,&MainWindow::show);
    
    menu.show();

    return a.exec();
}
