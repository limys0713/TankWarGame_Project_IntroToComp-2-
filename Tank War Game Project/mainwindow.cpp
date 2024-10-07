#include"MainWindow.h"
#include<iostream>
#include<string>
using namespace std;

int MainWindow::noise = 0;
bool MainWindow::shootlock_1P = 1;
bool MainWindow::shootlock_2P = 1;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){			//constructor
    setFixedSize(1000, 1000);
	time=0;
	timerID = startTimer(10);
	srand(1);
    img_base.load("./midterm/base.jpg");
    img_wall.load("./midterm/wall.gif");
    img_iron.load("./midterm/iron.gif");
    img_river.load("./midterm/river.gif");
    img_grass.load("./midterm/grass.gif");
    img_black.load("./midterm/black.jpg");
    img_ourtank.load("./midterm/our_tank.jpg");
    img_ourtank90.load("./midterm/our_tank90.jpg");
    img_ourtank180.load("./midterm/our_tank180.jpg");
    img_ourtank270.load("./midterm/our_tank270.jpg");
	img_1P.load("./midterm/1P");
	img_2P.load("./midterm/2P");
	img_enemy_tank.load("./midterm/enemy_tank.jpg");
	img_enemy_tank90.load("./midterm/enemy_tank90.jpg");
	img_enemy_tank180.load("./midterm/enemy_tank180.jpg");
	img_enemy_tank270.load("./midterm/enemy_tank270.jpg");
	img_small_enemy.load("./midterm/small_enemy.jpg");
	img_stronger_enemy_tank.load("./midterm/stronger_enemy_tank.jpg");
	img_stronger_enemy_tank90.load("./midterm/stronger_enemy_tank90.jpg");
	img_stronger_enemy_tank180.load("./midterm/stronger_enemy_tank180.jpg");
	img_stronger_enemy_tank270.load("./midterm/stronger_enemy_tank270.jpg");
	img_small_stronger_enemy.load("./midterm/small_stronger_enemy.jpg");
	img_bullet_bomb.load("./midterm/bullet boom.gif");
	img_tank_bomb.load("./midterm/tank boom.gif");
	img_heart.load("./midterm/heart");
	move_pic.load("./midterm/bullet.jpg");
	rotate.load("./midterm/bullet.jpg");
	img_background.load("./midterm/background");
    img_boundary.load("./midterm/boundary");
	img_frozen.load("./midterm/frozen");
    img_weapon.load("./midterm/weapon");
    img_explode.load("./midterm/explode");
	img_win.load("./midterm/win");
	img_lose.load("./midterm/lose");
	
	trans_up.rotate(360);				//rotate the image
	trans_right.rotate(90);		
	trans_down.rotate(180);			
	trans_left.rotate(270);

	for(int i=1;i<50;i++){				//initialize the bullet array
		
		bullet[i]=new QLabel(this);		
		move_pic = move_pic.scaled(bullet[i]->size(),Qt::KeepAspectRatio);
		bullet[i]->setPixmap(move_pic);
		bullet[i]->setFixedHeight(60);
		bullet[i]->setFixedWidth(60);
		rotate = rotate.scaled(bullet[i]->size(),Qt::KeepAspectRatio);
		move_pic.fill(Qt::transparent);
		bullet[i]->setPixmap(move_pic);
	}
	key="NO MOVE";				//initialize the key
	state=-1;					//initialize the state //state is used for checking which stage it is
	start=-4;
	lock=1;
	for(int i=0;i<4;i++){
		buff [i]=0;
	}
	for(int i=0;i<28;i++){			//initialize tank position, buff position, bomb
		for(int j=0;j<28;j++){
			tankPosition[i][j]=0;
			buffPosition[i][j]=0;
			bomb[i][j]=0;
		}
	}
	
	for(int i=0;i<50;i++){
		EnemyTankDirection[i]=1+rand()%4;		
		counter_hp[i]=0;
		bulletVisible[i]=0;	
	}
}
void MainWindow::keyPressEvent(QKeyEvent *event){	
	if(event->key() == Qt:: Key_O){		//when press 'O', all of the sound effects will be displayed		
		noise=0;
		update();		
	}
	if(event->key() == Qt:: Key_M){		//when press 'M', all of the sound effects will be muted	
		noise=1;
		update();		
	}
	if(event->key() == Qt:: Key_1){		//when press number pad 1 in stage 1(1P/2P), the game will start(need to press to start the game)
		start=1;		
	}
	if(event->key() == Qt:: Key_2){		 //when press number pad 2 in stage 2(1P/2P), the game will start(need to press to start the game)		
		start=2;		
	}
	if(event->key() == Qt:: Key_3){		//when press number pad 3 in stage 3(1P/2P), the game will start(need to press to start the game)			
		start=3;		
	}
	if(event->key() == Qt:: Key_0){		//press to pause the game		
		start=20;		
	}
	if(start==state||start==state-3){		//if you have pressed the start button, then you can move our tank
		if(event->key() == Qt:: Key_A){				//movement of our tank
			key = "left arrow key";		
			tankleft(1);		
			update();
		}
		else if(event->key() == Qt:: Key_D){
			key = "right arrow key";
			tankright(1);
			update();
		}
		else if(event->key() == Qt:: Key_W){
			key = "up arrow key";		
			tankup(1);		
			update();
		}
		else if(event->key() == Qt:: Key_S){
			key = "down arrow key";
			tankdown(1);
			update();
		}
		else if(event->key() == Qt:: Key_F){		//bullet shooting of our tank
			if(shootlock_1P){
			if(key=="NO MOVE"){
				BulletLoad(1);
				animation[1]=new QPropertyAnimation(bullet[1],"pos");
				bullet[1]->setPixmap(rotate.transformed(trans_up));
				animation[1]->setDuration(50000);
				animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
				animation[1]->setEndValue(QPoint(FindTankx(1)*30,-10000));
				animation[1]->start();
				update();
				BulletDirection[1]=1;
			}

			if(key=="up arrow key"){
				BulletLoad(1);
				animation[1]=new QPropertyAnimation(bullet[1],"pos");
				bullet[1]->setPixmap(rotate.transformed(trans_up));
				animation[1]->setDuration(50000);
				animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
				animation[1]->setEndValue(QPoint(FindTankx(1)*30,-10000));
				animation[1]->start();
				update();
				BulletDirection[1]=1;
			}

			if(key=="down arrow key"){
				BulletLoad(1);
				animation[1]=new QPropertyAnimation(bullet[1],"pos");
				bullet[1]->setPixmap(rotate.transformed(trans_down));
				animation[1]->setDuration(50000);
				animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
				animation[1]->setEndValue(QPoint(FindTankx(1)*30,10000));
				animation[1]->start();
				update();
				BulletDirection[1]=3;
			}

			if(key=="left arrow key"){
				BulletLoad(1);
				animation[1]=new QPropertyAnimation(bullet[1],"pos");
				bullet[1]->setPixmap(rotate.transformed(trans_left));
				animation[1]->setDuration(50000);
				animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
				animation[1]->setEndValue(QPoint(-10000,FindTanky(1)*30));
				animation[1]->start();
				update();
				BulletDirection[1]=4;
			}

			if(key=="right arrow key"){
				BulletLoad(1);
				animation[1]=new QPropertyAnimation(bullet[1],"pos");
				bullet[1]->setPixmap(rotate.transformed(trans_right));
				animation[1]->setDuration(50000);
				animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
				animation[1]->setEndValue(QPoint(10000,FindTanky(1)*30));
				animation[1]->start();
				update();
				BulletDirection[1]=2;
			}
			if(buff[2]>=1){						//if you have taken the weapon upgrade buff for the first time, the bullet speed will be faster
				if(key=="up arrow key"){
					BulletLoad(1);
					animation[1]=new QPropertyAnimation(bullet[1],"pos");
					bullet[1]->setPixmap(rotate.transformed(trans_up));
					animation[1]->setDuration(25000);
					animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
					animation[1]->setEndValue(QPoint(FindTankx(1)*30,-10000));
					animation[1]->start();
					update();
					BulletDirection[1]=1;
				}

				if(key=="down arrow key"){
					BulletLoad(1);
					animation[1]=new QPropertyAnimation(bullet[1],"pos");
					bullet[1]->setPixmap(rotate.transformed(trans_down));
					animation[1]->setDuration(25000);
					animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
					animation[1]->setEndValue(QPoint(FindTankx(1)*30,10000));
					animation[1]->start();
					update();
					BulletDirection[1]=3;
				}

				if(key=="left arrow key"){
					BulletLoad(1);
					animation[1]=new QPropertyAnimation(bullet[1],"pos");
					bullet[1]->setPixmap(rotate.transformed(trans_left));
					animation[1]->setDuration(25000);
					animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
					animation[1]->setEndValue(QPoint(-10000,FindTanky(1)*30));
					animation[1]->start();
					update();
					BulletDirection[1]=4;
				}

				if(key=="right arrow key"){
					BulletLoad(1);
					animation[1]=new QPropertyAnimation(bullet[1],"pos");
					bullet[1]->setPixmap(rotate.transformed(trans_right));
					animation[1]->setDuration(25000);
					animation[1]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30));
					animation[1]->setEndValue(QPoint(10000,FindTanky(1)*30));
					animation[1]->start();
					update();
					BulletDirection[1]=2;
				}
				if(buff[2]>=2){					//if you have taken the weapon upgrade buff for the second time, the bullet speed will be faster and the bullet will be two
					if(key=="up arrow key"){
						BulletLoad(36);
						animation[36]=new QPropertyAnimation(bullet[36],"pos");
						bullet[36]->setPixmap(rotate.transformed(trans_up));
						animation[36]->setDuration(25000);
						animation[36]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30+60));
						animation[36]->setEndValue(QPoint(FindTankx(1)*30,-10000+60));
						animation[36]->start();
						update();
						BulletDirection[36]=1;
					}

					if(key=="down arrow key"){
						BulletLoad(36);
						animation[36]=new QPropertyAnimation(bullet[36],"pos");
						bullet[36]->setPixmap(rotate.transformed(trans_down));
						animation[36]->setDuration(25000);
						animation[36]->setStartValue(QPoint(FindTankx(1)*30,FindTanky(1)*30-60));
						animation[36]->setEndValue(QPoint(FindTankx(1)*30,10000-60));
						animation[36]->start();
						update();
						BulletDirection[36]=3;
					}

					if(key=="left arrow key"){
						BulletLoad(36);
						animation[36]=new QPropertyAnimation(bullet[36],"pos");
						bullet[36]->setPixmap(rotate.transformed(trans_left));
						animation[36]->setDuration(25000);
						animation[36]->setStartValue(QPoint(FindTankx(1)*30+60,FindTanky(1)*30));
						animation[36]->setEndValue(QPoint(-10000+60,FindTanky(1)*30));
						animation[36]->start();
						update();
						BulletDirection[36]=4;
					}

					if(key=="right arrow key"){
						BulletLoad(36);
						animation[36]=new QPropertyAnimation(bullet[36],"pos");
						bullet[36]->setPixmap(rotate.transformed(trans_right));
						animation[36]->setDuration(25000);
						animation[36]->setStartValue(QPoint(FindTankx(1)*30-60,FindTanky(1)*30));
						animation[36]->setEndValue(QPoint(10000-60,FindTanky(1)*30));
						animation[36]->start();
						update();
						BulletDirection[36]=2;
					}
				}
			}
			shootlock_1P = 0;
		}
		}
		if(state==4||state==5||state==6){				//In every stages of 2P mode //tank movement controls of 2P
			if(event->key() == Qt:: Key_4){
				key_2P = "left arrow key_2P";		
				tankleft(2);		
				update();
			}
			else if(event->key() == Qt:: Key_6){
				key_2P = "right arrow key_2P";		
				tankright(2);				
				update();
			}
			else if(event->key() == Qt:: Key_8){
				key_2P = "up arrow key_2P";		
				tankup(2);		
				update();
			}
			else if(event->key() == Qt:: Key_5){
				key_2P = "down arrow key_2P";
				tankdown(2);
				update();
			}
			else if(event->key() == Qt:: Key_7){			//bullet shooting of 2P
				if(key_2P=="NO MOVE"){
					BulletLoad(2);
					animation[2]=new QPropertyAnimation(bullet[2],"pos");
					bullet[2]->setPixmap(rotate.transformed(trans_up));
					animation[2]->setDuration(50000);
					animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
					animation[2]->setEndValue(QPoint(FindTankx(2)*30,-10000));
					animation[2]->start();
					update();
					BulletDirection[2]=1;
				}

				if(key_2P=="up arrow key_2P"){
					BulletLoad(2);
					animation[2]=new QPropertyAnimation(bullet[2],"pos");
					bullet[2]->setPixmap(rotate.transformed(trans_up));
					animation[2]->setDuration(50000);
					animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
					animation[2]->setEndValue(QPoint(FindTankx(2)*30,-10000));
					animation[2]->start();
					update();
					BulletDirection[2]=1;
				}

				if(key_2P=="down arrow key_2P"){
					BulletLoad(2);
					animation[2]=new QPropertyAnimation(bullet[2],"pos");
					bullet[2]->setPixmap(rotate.transformed(trans_down));
					animation[2]->setDuration(50000);
					animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
					animation[2]->setEndValue(QPoint(FindTankx(2)*30,10000));
					animation[2]->start();
					update();
					BulletDirection[2]=3;
				}

				if(key_2P=="left arrow key_2P"){
					BulletLoad(2);
					animation[2]=new QPropertyAnimation(bullet[2],"pos");
					bullet[2]->setPixmap(rotate.transformed(trans_left));
					animation[2]->setDuration(50000);
					animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
					animation[2]->setEndValue(QPoint(-10000,FindTanky(2)*30));
					animation[2]->start();
					update();
					BulletDirection[2]=4;
				}

				if(key_2P=="right arrow key_2P"){
					BulletLoad(2);
					animation[2]=new QPropertyAnimation(bullet[2],"pos");
					bullet[2]->setPixmap(rotate.transformed(trans_right));
					animation[2]->setDuration(50000);
					animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
					animation[2]->setEndValue(QPoint(10000,FindTanky(2)*30));
					animation[2]->start();
					update();
					BulletDirection[2]=2;
				}
				if(buff[2]>=1){					//weapon upgrade buff
					if(key_2P=="up arrow key_2P"){
						BulletLoad(2);
						animation[2]=new QPropertyAnimation(bullet[2],"pos");
						bullet[2]->setPixmap(rotate.transformed(trans_up));
						animation[2]->setDuration(25000);
						animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
						animation[2]->setEndValue(QPoint(FindTankx(2)*30,-10000));
						animation[2]->start();
						update();
						BulletDirection[2]=1;
					}

					if(key_2P=="down arrow key_2P"){
						BulletLoad(2);
						animation[2]=new QPropertyAnimation(bullet[2],"pos");
						bullet[2]->setPixmap(rotate.transformed(trans_down));
						animation[2]->setDuration(25000);
						animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
						animation[2]->setEndValue(QPoint(FindTankx(2)*30,10000));
						animation[2]->start();
						update();
						BulletDirection[2]=3;
					}

					if(key_2P=="left arrow key_2P"){
						BulletLoad(2);
						animation[2]=new QPropertyAnimation(bullet[2],"pos");
						bullet[2]->setPixmap(rotate.transformed(trans_left));
						animation[2]->setDuration(25000);
						animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
						animation[2]->setEndValue(QPoint(-10000,FindTanky(2)*30));
						animation[2]->start();
						update();
						BulletDirection[2]=4;
					}

					if(key_2P=="right arrow key_2P"){
						BulletLoad(2);
						animation[2]=new QPropertyAnimation(bullet[2],"pos");
						bullet[2]->setPixmap(rotate.transformed(trans_right));
						animation[2]->setDuration(25000);
						animation[2]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30));
						animation[2]->setEndValue(QPoint(10000,FindTanky(2)*30));
						animation[2]->start();
						update();
						BulletDirection[2]=2;
					}
					if(buff[2]>=2){			//weapon upgrade buff
						if(key_2P=="up arrow key_2P"){
							BulletLoad(37);
							animation[37]=new QPropertyAnimation(bullet[37],"pos");
							bullet[37]->setPixmap(rotate.transformed(trans_up));
							animation[37]->setDuration(25000);
							animation[37]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30+60));
							animation[37]->setEndValue(QPoint(FindTankx(2)*30,-10000+60));
							animation[37]->start();
							update();
							BulletDirection[37]=1;
						}

						if(key_2P=="down arrow key_2P"){
							BulletLoad(37);
							animation[37]=new QPropertyAnimation(bullet[37],"pos");
							bullet[37]->setPixmap(rotate.transformed(trans_down));
							animation[37]->setDuration(25000);
							animation[37]->setStartValue(QPoint(FindTankx(2)*30,FindTanky(2)*30-60));
							animation[37]->setEndValue(QPoint(FindTankx(2)*30,10000-60));
							animation[37]->start();
							update();
							BulletDirection[37]=3;
						}

						if(key_2P=="left arrow key_2P"){
							BulletLoad(37);
							animation[37]=new QPropertyAnimation(bullet[37],"pos");
							bullet[37]->setPixmap(rotate.transformed(trans_left));
							animation[37]->setDuration(25000);
							animation[37]->setStartValue(QPoint(FindTankx(2)*30+60,FindTanky(2)*30));
							animation[37]->setEndValue(QPoint(-10000+60,FindTanky(2)*30));
							animation[37]->start();
							update();
							BulletDirection[37]=4;
						}

						if(key_2P=="right arrow key_2P"){
							BulletLoad(37);
							animation[37]=new QPropertyAnimation(bullet[37],"pos");
							bullet[37]->setPixmap(rotate.transformed(trans_right));
							animation[37]->setDuration(25000);
							animation[37]->setStartValue(QPoint(FindTankx(2)*30-60,FindTanky(2)*30));
							animation[37]->setEndValue(QPoint(10000-60,FindTanky(2)*30));
							animation[37]->start();
							update();
							BulletDirection[37]=2;
						}
					}
				}
			}
		}
		
		if(buff[1]!=1){			//when frozen buff is taken, enemy tanks cannot move
			EnemyMove();		// when our tank moves one step, enemy tank will also move one step, this will let the game will be more difficult to kill the enemies
		}
	}		
}
void MainWindow::EnemyMove(){
	int direction;
	int turnchance;
	for(int k=11;k<=35;k++){			
		direction=1+rand()%4;			// to random the direction
		turnchance=rand()%5;			//20% for turn the direction
		if(turnchance==0){		
			EnemyTankDirection[k]=direction;		//turn the direction
		}
		if(EnemyTankDirection[k]==1 ){					
			tankup(k);
			update();
		}
		if(EnemyTankDirection[k]==2 ){
			tankright(k);
			update();					
		}
		if(EnemyTankDirection[k]==3 ){
			tankdown(k);
			update();					
		}
		if(EnemyTankDirection[k]==4 ){
			tankleft(k);
			update();			
		}		
	}
}
void MainWindow::tankup(int p){
	int regi=-1,regj=-1;		
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(tankPosition[i][j]==p){
				regi=i;
				regj=j;
			}
		}
	}
	if(regi != -1 ){	
		if((Map[regi-1][regj]=='b' || Map[regi-1][regj] == 'g') && (Map[regi-1][regj+1]=='b'|| Map[regi-1][regj+1]=='g')
			&&tankPosition[regi-2][regj-1]==0&&tankPosition[regi-2][regj]==0&&tankPosition[regi-2][regj+1]==0
			&&Map[regi-2][regj-1]!='q'&&Map[regi-2][regj]!='q'&&Map[regi-2][regj+1]!='q'){		//b:background, g:grass, q:base camp
			tankPosition[regi][regj]=0;
			tankPosition[regi-1][regj]=p;
		}	
	}	
}
void MainWindow::tankleft(int p){
	int regi = -1,regj = -1;
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(tankPosition[i][j]==p){
				regi=i;
				regj=j;
			}
		}
	}
	if(regi != -1){
		if((Map[regi][regj-1]=='b' || Map[regi][regj-1] == 'g')&& (Map[regi+1][regj-1]=='b'|| Map[regi+1][regj-1]=='g')
			&&tankPosition[regi-1][regj-2]==0&&tankPosition[regi][regj-2]==0&&tankPosition[regi+1][regj-2]==0
			&&Map[regi-1][regj-2]!='q'&&Map[regi][regj-2]!='q'&&Map[regi+1][regj-2]!='q'){			
			tankPosition[regi][regj]=0;
			tankPosition[regi][regj-1]=p;
		}	
	}
}
void MainWindow::tankright(int p){
	int regi = -1,regj = -1;
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(tankPosition[i][j]==p){
				regi=i;
				regj=j;
			}
		}
	}
	if(regi != -1){
		if((Map[regi+1][regj+2]=='b' || Map[regi+1][regj+2] == 'g') && (Map[regi][regj+2]=='b'|| Map[regi][regj+2]=='g')
			&&tankPosition[regi-1][regj+2]==0&&tankPosition[regi][regj+2]==0&&tankPosition[regi+1][regj+2]==0
			&&Map[regi-1][regj+2]!='q'&&Map[regi][regj+2]!='q'&&Map[regi+1][regj+2]!='q'){		
			tankPosition[regi][regj]=0;
			tankPosition[regi][regj+1]=p;
		}	
	}	
}
void MainWindow::tankdown(int p){
	int regi = -1,regj = -1;
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
			if(tankPosition[i][j]==p){
				regi=i;
				regj=j;
			}
		}
	}
	if(regi != -1){
		if((Map[regi+2][regj]=='b' || Map[regi+2][regj] == 'g') && (Map[regi+2][regj+1]=='b'|| Map[regi+2][regj+1]=='g')
			&&tankPosition[regi+2][regj-1]==0&&tankPosition[regi+2][regj]==0&&tankPosition[regi+2][regj+1]==0
			&&Map[regi+2][regj-1]!='q'&&Map[regi+2][regj]!='q'&&Map[regi+2][regj+1]!='q'){		
			tankPosition[regi][regj]=0;
			tankPosition[regi+1][regj]=p;			
		}
	}
}
int MainWindow::FindTankx(int j){		
	if(j==1||j==2){
		for(int y=0;y<28;y++){
			for(int x=0;x<28;x++){
				if(tankPosition[y][x]==j){
					return x;
				}				
			}
		}
		return -1;
	}
	else{
		for(int y=0;y<28;y++){
			for(int x=0;x<28;x++){
				if(tankPosition[y][x]==j){
					return x;
				}								
			}
		}
		return -1;
	}
}
int MainWindow::FindTanky(int j){
	if(j==1||j==2){
		for(int y=0;y<28;y++){
			for(int x=0;x<28;x++){
				if(tankPosition[y][x]==j){
					return y;
				}				
			}
		}
		return -1;
	}
	else{
		for(int y=0;y<28;y++){
			for(int x=0;x<28;x++){
				if(tankPosition[y][x]==j){
					return y;
				}								
			}			
		}
		return -1;
	}
}
void MainWindow::set(int s){
	state = s;
	ifstream setMap;
	if(state==0){
		setMap.open("setmap0.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		EnemyTankTotal=50;
	}
	if(state==1){
		setMap.open("setmap1.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[5][5]=11;
		tankPosition[5][21]=12;
		tankPosition[2][13]=13;
		EnemyTankTotal=13;
	}
	if(state==2){
		setMap.open("setmap2.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[6][2]=11;
		tankPosition[6][24]=12;
		tankPosition[16][5]=13;
		tankPosition[16][13]=14;
		tankPosition[16][21]=15;
		EnemyTankTotal=15;
	}
	if(state==3){
		setMap.open("setmap3.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[2][5]=11;
		tankPosition[2][13]=12;
		tankPosition[2][21]=13;
		tankPosition[5][2]=14;
		tankPosition[5][24]=15;
		tankPosition[10][2]=16;
		tankPosition[10][24]=17;
		tankPosition[15][2]=18;
		tankPosition[15][24]=19;
		tankPosition[10][13]=20;
		EnemyTankTotal=20;
	}
	if(state==4){
		setMap.open("setmap4.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[24][17]=2;
		tankPosition[5][5]=11;
		tankPosition[5][21]=12;
		tankPosition[2][13]=13;
		EnemyTankTotal=13;
	}
	if(state==5){
		setMap.open("setmap5.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[24][17]=2;
		tankPosition[6][2]=11;
		tankPosition[6][24]=12;
		tankPosition[16][5]=13;
		tankPosition[16][13]=14;
		tankPosition[16][21]=15;
		EnemyTankTotal=15;
	}
	if(state==6){
		setMap.open("setmap6.in");
		if(!setMap.is_open()){
			cerr<<"Failed opening"<<endl;
		}
		tankPosition[24][9]=1;
		tankPosition[24][17]=2;
		tankPosition[2][5]=11;
		tankPosition[2][13]=12;
		tankPosition[2][21]=13;
		tankPosition[5][2]=14;
		tankPosition[5][24]=15;
		tankPosition[10][2]=16;
		tankPosition[10][24]=17;
		tankPosition[15][2]=18;
		tankPosition[15][24]=19;
		tankPosition[10][13]=20;
		EnemyTankTotal=20;
	}
	for(int row=0;row<28;row++){
		for(int line=0;line<28;line++){
			setMap>>Map[row][line];
		}
	}
}
void MainWindow::BulletJudgment(int s){		//bullet checking
	int x[50];
	int y[50];
	for(int j=1;j<=2;j++){			//bullet of our tank
		for(int i = j; i <= j+35 ; i+=35){
			x[i] = bullet[i]->x();
			y[i] = bullet[i]->y();
			if(x[i] >810){
				x[i] = 810;
			}
			if(y[i] >810){
				y[i] = 810;
			}
			if(BulletDirection[i]==1||BulletDirection[i]==3){			//1:up, 3:down, 2:right, 4:left
				for(int p=11;p<=25;p++){			//when the bullet hit the enemy tanks
					if(tankPosition[y[i]/30][x[i]/30] == p ){
						tankPosition[y[i]/30][x[i]/30]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30-1][x[i]/30-1] == p ){
						tankPosition[y[i]/30-1][x[i]/30-1]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30][x[i]/30+1] == p ){
						tankPosition[y[i]/30][x[i]/30+1]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30-1][x[i]/30] == p ){
						tankPosition[y[i]/30-1][x[i]/30]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
				}
				for(int p=26;p<=35;p++){			//when the bullet hit the stronger enemy
					if((tankPosition[y[i]/30][x[i]/30+1] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] < 3)
					||(tankPosition[y[i]/30-1][x[i]/30] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] < 3)){
						counter_hp[p]++;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}			
					if(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30][x[i]/30]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}
					if(tankPosition[y[i]/30][x[i]/30+1] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30][x[i]/30+1]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}
					if(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30-1][x[i]/30-1]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}
					if(tankPosition[y[i]/30-1][x[i]/30] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30-1][x[i]/30]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}
				}
				if(buff[2]<3){			//when we have taken the weapon upgrade buff below three times, we cannot destroy the iron bricks
					if(Map[y[i]/30][x[i]/30] == 'i'){
						bomb[y[i]/30][x[i]/30]=2;
						BulletStop(i);
					}													
					if(Map[y[i]/30][x[i]/30+1] == 'i'){
						bomb[y[i]/30][x[i]/30+1]=2;
						BulletStop(i);
					}
				}
				if(buff[2]>=3){			//when we have taken the weapon upgrade buff for three times, we can destroy the iron bricks
					if(Map[y[i]/30][x[i]/30] == 'i'){
						bomb[y[i]/30][x[i]/30]=1;
						BulletStop(i);
					}													
					if(Map[y[i]/30][x[i]/30+1] == 'i'){
						bomb[y[i]/30][x[i]/30+1]=1;
						BulletStop(i);
					}
				}																					
			}																		
			if(BulletDirection[i]==2||BulletDirection[i]==4){				
				for(int p=11;p<=25;p++){
					if(tankPosition[y[i]/30][x[i]/30] == p ){
						tankPosition[y[i]/30][x[i]/30]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30-1][x[i]/30-1] == p ){
						tankPosition[y[i]/30-1][x[i]/30-1]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30+1][x[i]/30] == p ){
						tankPosition[y[i]/30+1][x[i]/30]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
						}
					}
					if(tankPosition[y[i]/30][x[i]/30-1] == p ){
						tankPosition[y[i]/30][x[i]/30-1]=3;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){QSound::play("./midterm/tankdestroy.wav");
						}
					}
				}
				for(int p=26;p<=35;p++){
					if((tankPosition[y[i]/30+1][x[i]/30] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] < 3)
					||(tankPosition[y[i]/30][x[i]/30-1] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] < 3)){
						counter_hp[p]++;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
					}			
					if(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30][x[i]/30]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");}
					}
					if(tankPosition[y[i]/30+1][x[i]/30] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30+1][x[i]/30]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
							}
					}
					if(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30-1][x[i]/30-1]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
							}
					}
					if(tankPosition[y[i]/30][x[i]/30-1] == p && counter_hp[p] >= 3){					
						tankPosition[y[i]/30][x[i]/30-1]=4;
						BulletStop(i);
						bomb[y[i]/30][x[i]/30]==2;
						if(noise==0){
							QSound::play("./midterm/tankdestroy.wav");
							}
					}
				}
				if(buff[2]<3){
					if(Map[y[i]/30][x[i]/30] == 'i'){
						bomb[y[i]/30][x[i]/30]=2;
						BulletStop(i);
					}
					if(Map[y[i]/30+1][x[i]/30] == 'i'){
						bomb[y[i]/30+1][x[i]/30]=2;
						BulletStop(i);
					}				
				}
				if(buff[2]>=3){
					if(Map[y[i]/30][x[i]/30] == 'i'){
						bomb[y[i]/30][x[i]/30]=1;
						BulletStop(i);
					}
					if(Map[y[i]/30+1][x[i]/30] == 'i'){
						bomb[y[i]/30+1][x[i]/30]=1;
						BulletStop(i);
					}
				}		
			}
		}
	}
	for(int i = 11; i <= 35 ; i++){			//the bullet checking of all enemy tanks
		x[i] = bullet[i]->x();
		y[i] = bullet[i]->y();
		if(x[i] >810){
			x[i] = 810;
		}
		if(y[i] >810){
			y[i] = 810;
		}
		if(BulletDirection[i]==1||BulletDirection[i]==3){
			for(int p=1;p<=2;p++){
				if((tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30][x[i]/30+1] == p && counter_hp[p] < 3)
				||(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30-1][x[i]/30] == p && counter_hp[p] < 3)){
					counter_hp[p]++;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}					
				if(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30][x[i]/30]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
					if(noise==0){
						QSound::play("./midterm/tankdestroy.wav");
						}	
				}
				if(tankPosition[y[i]/30][x[i]/30+1] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30][x[i]/30+1]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
					if(noise==0){
						QSound::play("./midterm/tankdestroy.wav");
						}
				}
				if(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30-1][x[i]/30-1]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
					if(noise==0){
						QSound::play("./midterm/tankdestroy.wav");
						}
				}
				if(tankPosition[y[i]/30-1][x[i]/30] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30-1][x[i]/30]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
					if(noise==0){
						QSound::play("./midterm/tankdestroy.wav");
						}
				}				
			}
			if(Map[y[i]/30][x[i]/30] == 'i'){
				bomb[y[i]/30][x[i]/30]=2;
				BulletStop(i);
			}													
			if(Map[y[i]/30][x[i]/30+1] == 'i'){
				bomb[y[i]/30][x[i]/30+1]=2;
				BulletStop(i);
			}																			  
		}
		if(BulletDirection[i]==2||BulletDirection[i]==4){
			for(int p=1;p<=2;p++){
				if((tankPosition[y[i]/30+1][x[i]/30] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] < 3)
				||(tankPosition[y[i]/30][x[i]/30-1] == p && counter_hp[p] < 3)||(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] < 3)){
					counter_hp[p]++;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}			
				if(tankPosition[y[i]/30][x[i]/30] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30][x[i]/30]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}
				if(tankPosition[y[i]/30+1][x[i]/30] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30+1][x[i]/30]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}
				if(tankPosition[y[i]/30-1][x[i]/30-1] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30-1][x[i]/30-1]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}
				if(tankPosition[y[i]/30][x[i]/30-1] == p && counter_hp[p] >= 3){					
					tankPosition[y[i]/30][x[i]/30-1]=3;
					BulletStop(i);
					bomb[y[i]/30][x[i]/30]==2;
				}																			 
			}	
			if(Map[y[i]/30][x[i]/30] == 'i'){
				bomb[y[i]/30][x[i]/30]=2;
				BulletStop(i);
			}													
			if(Map[y[i]/30+1][x[i]/30] == 'i'){
				bomb[y[i]/30+1][x[i]/30]=2;
				BulletStop(i);
			}
		}		
	}
	for(int i=1;i<=37;i++){
		if(BulletDirection[i]==1||BulletDirection[i]==3){
			if(Map[y[i]/30][x[i]/30] == 'q'||Map[y[i]/30-1][x[i]/30-1]=='q'||Map[y[i]/30][x[i]/30+1]=='q'||Map[y[i]/30-1][x[i]/30]=='q'){					
				bomb[y[i]/30][x[i]/30]=1;
				BulletStop(i);
			}
			if(Map[y[i]/30][x[i]/30] == 'g'||Map[y[i]/30][x[i]/30+1]=='g'){					
				bulletHide(i);				//let the bullet be invisible and yet still moving
			}
			if(Map[y[i]/30][x[i]/30] != 'g'&&Map[y[i]/30][x[i]/30+1]!='g'&&bulletVisible[i]==1){
				BulletLoad(i);
			}
			
			if(Map[y[i]/30][x[i]/30] == 'd'){
				BulletStop(i);
			}
			if(Map[y[i]/30][x[i]/30] == 'w'){	//w:bricks, d:boundary, q:base camp, g:grass				
				bomb[y[i]/30][x[i]/30]=1;
				BulletStop(i);
			}
			if(Map[y[i]/30][x[i]/30+1] == 'w'){					
				bomb[y[i]/30][x[i]/30+1]=1;
				BulletStop(i);
			}	
		}
		if(BulletDirection[i]==2||BulletDirection[i]==4){
			if(Map[y[i]/30][x[i]/30] == 'q'||Map[y[i]/30-1][x[i]/30-1]=='q'||Map[y[i]/30+1][x[i]/30]=='q'||Map[y[i]/30][x[i]/30-1]=='q'){					
				bomb[y[i]/30][x[i]/30]=3;
				BulletStop(i);
			}
			if(Map[y[i]/30][x[i]/30] == 'g'||Map[y[i]/30+1][x[i]/30]=='g'){					
				bulletHide(i);				
			}
			if(Map[y[i]/30][x[i]/30] != 'g'&&Map[y[i]/30+1][x[i]/30]!='g'&&bulletVisible[i]==1){
				BulletLoad(i);
			}
			
			if(Map[y[i]/30][x[i]/30] == 'd'){
				BulletStop(i);
				}
			if(Map[y[i]/30][x[i]/30] == 'w'){					
				bomb[y[i]/30][x[i]/30]=1;
				BulletStop(i);
			}
			if(Map[y[i]/30+1][x[i]/30] == 'w'){					
				bomb[y[i]/30+1][x[i]/30]=1;
				BulletStop(i);
			}	
		}
	}
}
void MainWindow::BulletStop(int b){			//function use to let the bullet be transparent and transfer the picture to (0,0)
	if(b>=0&&b<=49){
		//animation[b]->stop();
		move_pic.fill(Qt::transparent);
		bullet[b]->setPixmap(move_pic);
		animation[b]=new QPropertyAnimation(bullet[b],"pos");					
		animation[b]->setDuration(500);
		animation[b]->setStartValue(QPoint(0,0));
		animation[b]->setEndValue(QPoint(0,0));
		animation[b]->start();
		if(b == 1 || b == 36){
			shootlock_1P = 1;
		}
		if(b == 2 || b == 37){
			shootlock_2P = 1;
		}
	}
}
void MainWindow::BulletLoad(int b){				//load the image of bullet
	if(b>=0&&b<=49){
		move_pic.load("./midterm/bullet.jpg");
		move_pic = move_pic.scaled(bullet[b]->size(),Qt::KeepAspectRatio);
		bullet[b]->setPixmap(move_pic);		
		bullet[b]->setFixedHeight(60);
		bullet[b]->setFixedWidth(60);
		if(BulletDirection[b]==1){
			bullet[b]->setPixmap(rotate.transformed(trans_up));
		}
		if(BulletDirection[b]==2){
			bullet[b]->setPixmap(rotate.transformed(trans_right));
		}
		if(BulletDirection[b]==3){
			bullet[b]->setPixmap(rotate.transformed(trans_down));
		}
		if(BulletDirection[b]==4){
			bullet[b]->setPixmap(rotate.transformed(trans_left));
		}
		bulletVisible[b]=0;
	}
}
void MainWindow::bulletHide(int b){				//let the bullet be transparent
	move_pic.fill(Qt::transparent);
	bullet[b]->setPixmap(move_pic);
	bulletVisible[b]=1;
}
int MainWindow::FindEnemyAmount(){
	int eamount=0;
	for(int y=0;y<28;y++){
		for(int x=0;x<28;x++){
			for(int k=11;k<=35;k++){
				if(tankPosition[y][x]==k){
					eamount++;
				}
			}
		}
	}
	return eamount;
}
void MainWindow::buffcheck(){
	for(int y=0;y<28;y++){
		for(int x=0;x<28;x++){
			if((tankPosition[y][x]==1||tankPosition[y][x]==2)&&buffPosition[y][x]==1){
				buff[1]=1;
				buffPosition[y][x]=0;
				if(noise==0){
				QSound::play("./midterm/buff.wav");
				}
			}
			if((tankPosition[y][x]==1||tankPosition[y][x]==2)&&buffPosition[y][x]==2){
				buff[2]++;
				buffPosition[y][x]=0;
				if(noise==0){
				QSound::play("./midterm/buff.wav");
				}
			}
			if((tankPosition[y][x]==1||tankPosition[y][x]==2)&&buffPosition[y][x]==3){
				buff[3]=1;
				buffPosition[y][x]=0;
				if(noise==0){
				QSound::play("./midterm/buff.wav");
				}
			}
		}
	}
}
void MainWindow::paintEvent(QPaintEvent *event){	
	int bx = 0;
	int by = 0;
	
	QPainter painter(this);
	QFont font;
	QPen pen;
	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.drawImage(0,0,img_background);
	if(state<=3&&state!=0){
		painter.drawImage(860,300,img_1P);
	}
	if(state>3){
		painter.drawImage(860,300,img_1P);
		painter.drawImage(860,375,img_2P);
	}
	if(state>0&&state<7){
		for(int h=3;h>counter_hp[1];h--){
			painter.drawImage(830+h*34,345,img_heart);
		}
	}
	if(state>3){
		for(int h=3;h>counter_hp[2];h--){
			painter.drawImage(830+h*34,415,img_heart);
		}
	}
	if(35-EnemyTankTotal+FindEnemyAmount()>0){
		if(EnemyTankTotal==36){
			for(int a=0;a<35-EnemyTankTotal+FindEnemyAmount()+1;a++){
				painter.drawImage(30+a*30,840,img_small_enemy);
			}
		}
		for(int a=0;a<35-EnemyTankTotal+FindEnemyAmount();a++){
			painter.drawImage(30+a*30,840,img_small_enemy);

		}
	}
		
	for(int row=0 ; row<28 ; row++){
		for(int line = 0; line < 28; line++){
			if(Map[row][line] == 'b'){
				painter.drawImage(line*30, row*30, img_black);
			}
			if(Map[row][line] == 'w'){
				painter.drawImage(line*30, row*30, img_wall);
			}
			if(Map[row][line] == 'r'){
				painter.drawImage(line*30, row*30, img_river);
			}
			if(Map[row][line] == 'g'){
				painter.drawImage(line*30, row*30, img_grass);
			}
			if(Map[row][line] == 'i'){
				painter.drawImage(line*30, row*30, img_iron);
			}
			if(Map[row][line] == 'd'){
				painter.drawImage(line*30, row*30, img_boundary);
			}
			if(Map[row][line] == 'q'){
				painter.drawImage(line*30, row*30, img_black);
				bx=line*30;
				by=row*30;
			}
			if(Map[row][line] == 'd'){
				painter.drawImage(line*30, row*30, img_boundary);
			}
		}
	}	
	if(bx != 0 && by != 0){
		painter.drawImage(bx, by, img_base);
	}
	for(int y=0; y<25; y++){
		for(int x=0; x<25; x++){
			if(buffPosition[y][x]==1){
				painter.drawImage(x*30,y*30,img_frozen);
			}
			if(buffPosition[y][x]==2){
				painter.drawImage(x*30,y*30,img_weapon);
			}
			if(buffPosition[y][x]==3){
				painter.drawImage(x*30,y*30,img_explode);
			}
		}
	}
	for(int y=0; y<28; y++){
		for(int x=0; x<28; x++){
			if(tankPosition[y][x]==1){
				if(key!="NULL"){
					painter.drawImage(x*30,y*30,img_ourtank);
				}
				if(key=="up arrow key"){
					painter.drawImage(x*30,y*30,img_ourtank);
				}
				if(key=="down arrow key"){
					painter.drawImage(x*30,y*30,img_ourtank180);
				}
				if(key=="left arrow key"){
					painter.drawImage(x*30,y*30,img_ourtank270);
				}
				if(key=="right arrow key"){
					painter.drawImage(x*30,y*30,img_ourtank90);
				}
			}
			if(tankPosition[y][x]==2){
				if(key_2P!="NULL"){
					painter.drawImage(x*30,y*30,img_ourtank);
				}
				if(key_2P=="up arrow key_2P"){
					painter.drawImage(x*30,y*30,img_ourtank);
				}
				if(key_2P=="down arrow key_2P"){
					painter.drawImage(x*30,y*30,img_ourtank180);
				}
				if(key_2P=="left arrow key_2P"){
					painter.drawImage(x*30,y*30,img_ourtank270);
				}
				if(key_2P=="right arrow key_2P"){
					painter.drawImage(x*30,y*30,img_ourtank90);
				}
			}
		}
	}
	//EnemyMove();
	for(int y=0; y<25; y++){
		for(int x=0; x<25; x++){
	 		for(int k=11;k<=25;k++){
	 			if(tankPosition[y][x]==k){
					if(EnemyTankDirection[k]==1){
						painter.drawImage(x*30,y*30,img_enemy_tank);
						update();
					}
					if(EnemyTankDirection[k]==2){
						painter.drawImage(x*30,y*30,img_enemy_tank90);
						update();
					}
					if(EnemyTankDirection[k]==3){
						painter.drawImage(x*30,y*30,img_enemy_tank180);
						update();
					}
					if(EnemyTankDirection[k]==4){
						painter.drawImage(x*30,y*30,img_enemy_tank270);
						update();
					}
	 			}
	 		}
		}
	}
	for(int y=0; y<=27; y++){
		for(int x=0; x<=27; x++){
	 		for(int k=26;k<=35;k++){
	 			if(tankPosition[y][x]==k){
					if(EnemyTankDirection[k]==1){
						painter.drawImage(x*30,y*30,img_stronger_enemy_tank);
						update();
					}
					if(EnemyTankDirection[k]==2){
						painter.drawImage(x*30,y*30,img_stronger_enemy_tank90);
						update();
					}
					if(EnemyTankDirection[k]==3){
						painter.drawImage(x*30,y*30,img_stronger_enemy_tank180);
						update();
					}
					if(EnemyTankDirection[k]==4){
						painter.drawImage(x*30,y*30,img_stronger_enemy_tank270);
						update();
					}
	 			}
	 		}
			if(bomb[y][x]==1||bomb[y][x]==2||bomb[y][x]==3){
				painter.drawImage(x*30,y*30,img_bullet_bomb);
			}
			if(tankPosition[y][x]==3||tankPosition[y][x]==4){
				painter.drawImage(x*30,y*30,img_tank_bomb);
			} 
		}
	}
	font.setPointSize(20);
	painter.setFont(font);
	pen.setColor(Qt::black);
	painter.setPen(pen);
	painter.drawText(780,840,QString("time: %1").arg(time));
	painter.drawText(780,870,QString("1P HP: %1/300").arg(300-100*counter_hp[1]));
	if(state==4||state==5||state==6){
		painter.drawText(780,900,QString("2P HP: %1/300").arg(300-100*counter_hp[2]));
	}
	if(state==1||state==4){
		painter.drawText(780,960,QString("stage: %1").arg(1));
	}
	if(state==2||state==5){
		painter.drawText(780,960,QString("stage: %1").arg(1));
	}
	if(state==3||state==6){
		painter.drawText(780,960,QString("stage: %1").arg(1));
	}
	if(state==7){
		painter.drawImage(0, 0, img_win);
	}	
	if(state == 8){
		painter.drawImage(0,0,img_lose);
	}
}
void MainWindow::timerEvent(QTimerEvent *event){	
	if(start==state||start==state-3){
		if(event -> timerId() == timerID && timerID != 0){
			time++;
			if(noise==0){
				if(time%350==0||(time==10)){
					QSound::play("./midterm/bgm.wav");
				}
			}
			if(time%3==0){
				BulletJudgment(state);
				update();
				buffcheck();
				if(buff[1]==1){
					if(lock){
						regtime=time;
						lock=0;
					}					
					if(regtime<time-1000){
						buff[1]=0;
						lock=1;
					}
				}				
			}
			if(time%30==15){
				if(buff[3]==1){
					for(int k=11;k<=25;k++){
						if(FindTankx(k)!=-1){
							tankPosition[FindTanky(k)][FindTankx(k)]=3;
						}
					}
					for(int k=26;k<=35;k++){
						if(FindTankx(k)!=-1){
							tankPosition[FindTanky(k)][FindTankx(k)]=4;
						}
					}
					buff[3]=0;
				}
				/*int bx[50];
				int by[50];
				for(int y=0;y<28;y++){
					for(int y=0;y<28;y++){
						for(int k=1;k<=37;k++){
							bx[i] = bullet[i]->x();
							by[i] = bullet[i]->y();
							if(Map[y][x]=='g'){
								bulletHide(k)
							}
						}
					}
				}*/
			}
			if(time%30==0){				
				for(int i=0;i<=27;i++){
					for(int j=0;j<=27;j++){
						if(bomb[i][j]==1){
							Map[i][j]='b';
						}
						if(bomb[i][j]==1||bomb[i][j]==2){
							bomb[i][j]=0;
						}
						if(tankPosition[i][j]==3){
							tankPosition[i][j]=0;
						}
						if(tankPosition[i][j]==4){
							int bu=1+rand()%10;
							if(bu>=1&bu<=4){
								buffPosition[i][j]=1;
								tankPosition[i][j]=0;
							}
							if(bu>=4&&bu<=9){
								buffPosition[i][j]=2;
								tankPosition[i][j]=0;
							}
							if(bu==10){
								buffPosition[i][j]=3;
								tankPosition[i][j]=0;
							} 
						}
					}
				}
			}
			if(time%50==0){
				if(buff[1]!=1){
					EnemyMove();
				}
				if(state==1||state==4){
					if(FindEnemyAmount()<3&&EnemyTankTotal<=35){
						int spawnpoint=1+rand()%3;
						if(spawnpoint==1&&tankPosition[2][13]==0&&tankPosition[3][13]==0&&tankPosition[2][14]==0&&tankPosition[3][14]==0){
							EnemyTankTotal++;
							tankPosition[2][13]=EnemyTankTotal;								
						}
						if(spawnpoint==2&&tankPosition[11][5]==0&&tankPosition[11][6]==0&&tankPosition[12][5]==0&&tankPosition[12][6]==0){
							EnemyTankTotal++;
							tankPosition[11][5]=EnemyTankTotal;								
						}
						if(spawnpoint==3&&tankPosition[11][21]==0&&tankPosition[11][22]==0&&tankPosition[12][21]==0&&tankPosition[12][22]==0){
							EnemyTankTotal++;
							tankPosition[11][21]=EnemyTankTotal;								
						}
					}
				}
				if(state==2||state==5){
					if(FindEnemyAmount()<5&&EnemyTankTotal<=35){
						int spawnpoint=1+rand()%3;
						if(spawnpoint==1&&tankPosition[5][4]==0&&tankPosition[5][5]==0&&tankPosition[6][4]==0&&tankPosition[6][5]==0){
							EnemyTankTotal++;
							tankPosition[5][4]=EnemyTankTotal;								
						}
						if(spawnpoint==2&&tankPosition[22][22]==0&&tankPosition[22][23]==0&&tankPosition[23][22]==0&&tankPosition[23][23]==0){
							EnemyTankTotal++;
							tankPosition[22][22]=EnemyTankTotal;								
						}
						if(spawnpoint==3&&tankPosition[14][13]==0&&tankPosition[14][14]==0&&tankPosition[15][13]==0&&tankPosition[15][14]==0){
							EnemyTankTotal++;
							tankPosition[14][13]=EnemyTankTotal;								
						}
					}
				}
				if(state==3||state==6){
					if(FindEnemyAmount()<10&&EnemyTankTotal<=35){
						int spawnpoint=1+rand()%5;
						if(spawnpoint==1&&tankPosition[4][2]==0&&tankPosition[5][2]==0&&tankPosition[4][3]==0&&tankPosition[5][3]==0){
							EnemyTankTotal++;
							tankPosition[4][2]=EnemyTankTotal;						
						}
						if(spawnpoint==2&&tankPosition[4][23]==0&&tankPosition[4][24]==0&&tankPosition[5][23]==0&&tankPosition[5][24]==0){
							EnemyTankTotal++;
							tankPosition[4][23]=EnemyTankTotal;								
						}
						if(spawnpoint==3&&tankPosition[2][13]==0&&tankPosition[2][14]==0&&tankPosition[3][13]==0&&tankPosition[3][14]==0){
							EnemyTankTotal++;
							tankPosition[2][13]=EnemyTankTotal;								
						}
						if(spawnpoint==4&&tankPosition[16][2]==0&&tankPosition[17][2]==0&&tankPosition[16][3]==0&&tankPosition[17][3]==0){
							EnemyTankTotal++;
							tankPosition[16][2]=EnemyTankTotal;								
						}
						if(spawnpoint==5&&tankPosition[16][24]==0&&tankPosition[17][24]==0&&tankPosition[16][25]==0&&tankPosition[17][25]==0){
							EnemyTankTotal++;
							tankPosition[16][24]=EnemyTankTotal;								
						}							
					}
				}
			}
			if(time%200==0){
				for(int k=11;k<=35;k++){
					if(FindTankx(k) != -1){
						if(EnemyTankDirection[k]==1){
							BulletLoad(k);
							animation[k]=new QPropertyAnimation(bullet[k],"pos");
							bullet[k]->setPixmap(rotate.transformed(trans_up));
							animation[k]->setDuration(50000);
							animation[k]->setStartValue(QPoint(FindTankx(k)*30,FindTanky(k)*30));
							animation[k]->setEndValue(QPoint(FindTankx(k)*30,-10000));
							animation[k]->start();
							update();
							BulletDirection[k]=EnemyTankDirection[k];
						}
						if(EnemyTankDirection[k]==2){
							BulletLoad(k);
							animation[k]=new QPropertyAnimation(bullet[k],"pos");
							bullet[k]->setPixmap(rotate.transformed(trans_right));
							animation[k]->setDuration(50000);
							animation[k]->setStartValue(QPoint(FindTankx(k)*30,FindTanky(k)*30));
							animation[k]->setEndValue(QPoint(10000,FindTanky(k)*30));
							animation[k]->start();
							update();
							BulletDirection[k]=EnemyTankDirection[k];
						}

						if(EnemyTankDirection[k]==3){
							BulletLoad(k);
							animation[k]=new QPropertyAnimation(bullet[k],"pos");
							bullet[k]->setPixmap(rotate.transformed(trans_down));
							animation[k]->setDuration(50000);
							animation[k]->setStartValue(QPoint(FindTankx(k)*30,FindTanky(k)*30));
							animation[k]->setEndValue(QPoint(FindTankx(k)*30,10000));
							animation[k]->start();
							update();
							BulletDirection[k]=EnemyTankDirection[k];
						}

						if(EnemyTankDirection[k]==4){
							BulletLoad(k);
							animation[k]=new QPropertyAnimation(bullet[k],"pos");
							bullet[k]->setPixmap(rotate.transformed(trans_left));
							animation[k]->setDuration(50000);
							animation[k]->setStartValue(QPoint(FindTankx(k)*30,FindTanky(k)*30));
							animation[k]->setEndValue(QPoint(-10000,FindTanky(k)*30));
							animation[k]->start();
							update();
							BulletDirection[k]=EnemyTankDirection[k];						
						}
					}
				}
				if(EnemyTankTotal>35&&FindEnemyAmount()==0){
					set(7);
					update();
					if(noise==0){
						QSound::play("./midterm/victory.wav");
					}
				}
				for(int y=0;y<=27;y++){
					for(int x=0;x<=27;x++){
						if(bomb[y][x]==3){
							set(8);
							update();
							if(noise==0){
								QSound::play("./midterm/end.wav");
							}
						}
					}
				}				
				if(state==1||state==2||state==3){
					if(counter_hp[1]>=3){
						set(8);
						if(noise==0){
								QSound::play("./midterm/end.wav");
							}
						update();
					}
				}
				if(state==4||state==5||state==6){
					if(counter_hp[1]>=3&&counter_hp[2]>=3){
						set(8);
						if(noise==0){
								QSound::play("./midterm/end.wav");
							}
						update();
					}
				}		
			}
		}	 
	}
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
}
void MainWindow::mousePressEvent(QMouseEvent *event){
	if(event -> button() == Qt::RightButton){
		//start++;
	}
}
MainWindow::~MainWindow(){		//destructor
}



