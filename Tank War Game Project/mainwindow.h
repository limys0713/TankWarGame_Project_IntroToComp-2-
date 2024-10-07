#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <fstream>
#include <QPushButton>
#include <string>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include <QPropertyAnimation>
#include <iostream>
#include <cstdlib>
#include <QTimer>
#include <ctime>
#include <unistd.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set(int s);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void tankup(int p);
    void tankdown(int p);
    void tankleft(int p);
    void tankright(int p);
    void EnemyMove();
    int FindEnemyAmount();
    void BulletJudgment(int s);
    void BulletStop(int b);
    void BulletLoad(int b);
    int FindTankx(int j);
    int FindTanky(int j);
    void buffcheck();
    void bulletHide(int b);
private:
    static bool shootlock_1P;
    static bool shootlock_2P; 
    int state;
    int time;
    int regtime;
    int timerID;
    bool lock;
    int start;
    static int noise;
    int bomb [28][28];
    char Map [28][28];
    int tankPosition [28][28];
    int buffPosition [28][28];
    int EnemyTankTotal;
    int EnemyTankDirection [50];
    int BulletDirection [50];
    int bulletVisible [50];
    int counter_hp [50];
    int buff [4];
    QImage img_base;
    QImage img_ourtank;
    QImage img_ourtank90;
    QImage img_ourtank180;
    QImage img_ourtank270;
    QImage img_black;
    QImage img_bullet;
    QImage img_grass;
    QImage img_river;
    QImage img_wall;
    QImage img_iron;
    QImage img_enemy_tank;
    QImage img_enemy_tank90;
    QImage img_enemy_tank180;
    QImage img_enemy_tank270;
    QImage img_small_enemy;
    QImage img_stronger_enemy_tank;
    QImage img_stronger_enemy_tank90;
    QImage img_stronger_enemy_tank180;
    QImage img_stronger_enemy_tank270;
    QImage img_small_stronger_enemy;
    QImage img_bullet_bomb;
    QImage img_tank_bomb;
    QImage img_heart;
    QImage img_background;
    QImage img_boundary;
    QImage img_frozen;
    QImage img_weapon;
    QImage img_explode;
    QImage img_win;
    QImage img_lose;
    QString key;
    QString key_2P;
    QString key_mouse;
    QPropertyAnimation *animation[50];
    QImage img_1P;
    QImage img_2P;
    QPixmap move_pic;
    QLabel *bullet[50];
    QPixmap rotate;
    QTransform trans_up;
	QTransform trans_right;	
	QTransform trans_left;
	QTransform trans_down;
};


#endif
