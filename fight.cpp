//�ļ�����fight.cpp
//ս��ϵͳ
#include "structs.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>      
#include <stdio.h>
#include <windows.h>			
#include <math.h>
#include <string.h>
#include <ctime>
#include <string>
using namespace std;
#pragma comment( lib, "MSIMG32.LIB")
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define BACK 1
#define DIE 2
#define MAX_PEAS 180
#define MAX_ZOMBIES 10
#define MAX_COINS 5
#define SLEEPTIME 50
#define COIN_WAIT_TIME 4000
#define PUT_BOOM_WAIT_TIME 20000
#define BOOM_WAIT_TIME 2000
#define DIE_WAIT_TIME 5000
#define W 0x57
#define S 0x53
#define A 0x41
#define D 0x44
#define J 0x4A
#define BASICAWARD "1"
#define HD_BASICAWARD "3"
#define SILVER "10"
#define HD_SILVER "30"
#define GOLD "50"
#define HD_GOLD "80"
#define DIAMOND "1000"
#define HD_DIAMOND "2195"
#define GET_BASICAWARD 0
#define GET_SILVER 1
#define GET_GOLD 2
#define GET_DIAMOND 3
#define EASY 1
#define HARD 2
//���ļ����庯��
void fight(save& player,int level_);
void ctrlPlant(int& x, int& y, int& go, int plantSpeed, save& player);
void peaFly(int v);
void shoot(int x, int y, save player);
void createZombie(int x, int y);
void zombieMove(int zombieSpeed, int& go);
void hitZombies(int damage, int peaSpeed, save& player, int x);
void die(save& player);
void createCoinFromZombies(save& player, int x, int y);
void initializeTheFight();
void createBoom(save player, int x, int y);
void boomKillZombies(save& player);
int chooseCoinKind(lucks luck);
void getCoins(save& player);
//������tool.cpp���庯��
void home(save& player);
//tool.cpp�еĺ���
void outPutTimeNow();
void backImage(IMAGE image1, IMAGE image2, IMAGE image3, string money);
int randNum(int maxNum, int minNum);
void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void initializeTheWindows(IMAGE image1, IMAGE image2, IMAGE image3);
bool areaCheck(int xLeft, int xRight, int yHigh, int yLow, int x, int y);
string add(string str1, string str2);
string sub(string str1, string str2);
string mul(string str1, string str2);
void div(string str1, string str2, string& quotient, string& residue);
//����ṹ��
struct peas {
	int x;
	int y;
	bool free = true;/*�Ƿ������ڷ���*/
	bool cactus = false;
};
struct zombies {
	int x = 800;
	int y;
	int hp = -1;
};
struct coins {
	int x;
	int y;
	bool free = true;/*�Ƿ������ڳ����ڳ���*/
	int kind;
};
struct booms {
	int x = 0;
	int y = 0;
	bool free = true;/*�Ƿ�Ϊ׼����Ͽ���״̬*/
	bool big = false;
	clock_t lastTimePut;/*�ϴη���ը��ʱ��*/
};
//�����й�����
peas pea[MAX_PEAS];
zombies zombie[MAX_ZOMBIES];
coins coin[MAX_COINS];
//�����й�ȫ�ֱ���
booms boom;
int kill;
int level;
//ս������������
void fight(save& player,int level_) {
	//����ͼƬ
	IMAGE zombie233;
	IMAGE fight1;
	IMAGE fight2;
	IMAGE fight3;
	IMAGE pea0;
	IMAGE cactus;
	IMAGE plant;
	IMAGE silverCoin;
	IMAGE goldCoin;
	IMAGE diamond;
	IMAGE boom0;
	IMAGE bigBoom;
	IMAGE smallBoom;
	//��ȡ�Ѷ�
	level = level_;
	//��ʼ��ս��״̬
	int go = 0;
	//��ʼ���㶹����λ��
	int x = 48;
	int y = 80;
	//��ʼ����ʬλ��
	initializeTheFight();
	// ��ʼ��ʱ���
	clock_t lastShootingTime = clock();/*�ϴ��㶹����ʱ��*/
	clock_t lastCreateZombieTime = lastShootingTime;/*�ϴν�ʬ����ʱ��*/
	clock_t coinLastShowTime = lastShootingTime;/*�ϴ�Ӳ�ҳ���ʱ��*/
	clock_t lastBoomTime = lastShootingTime;/*�ϴ�ը������ʱ��*/
	clock_t currentTime;/*ʵʱ���µ�ʱ���*/
	kill = 0;/*��ʬ��ɱ����ʼ��*/
	//����ͼƬ
	if (level == EASY) {
		loadimage(&fight1, ".\\fight1.png", WIN_WIDTH, WIN_HEIGHT / 3);
		loadimage(&fight2, ".\\fight2.png", WIN_WIDTH, WIN_HEIGHT / 3);
		loadimage(&fight3, ".\\fight3.png", WIN_WIDTH, WIN_HEIGHT / 3);
	}
	else {
		loadimage(&fight1, ".\\hd_fight1.png", WIN_WIDTH, WIN_HEIGHT / 3);
		loadimage(&fight2, ".\\hd_fight2.png", WIN_WIDTH, WIN_HEIGHT / 3);
		loadimage(&fight3, ".\\hd_fight3.png", WIN_WIDTH, WIN_HEIGHT / 3);
	}
	loadimage(&zombie233, ".\\zombie.png", 85, 135);
	loadimage(&pea0, ".\\pea.png", 28, 28);
	loadimage(&plant, ".\\peashooter.png", 85, 85);
	loadimage(&silverCoin, ".\\coin_silver_dollar.png", 43, 40);
	loadimage(&goldCoin, ".\\coin_gold_dollar.png", 45, 45);
	loadimage(&diamond, ".\\Diamond.png", 68, 52);
	loadimage(&cactus, ".\\cactus.png", 30, 16);
	loadimage(&boom0, ".\\boom1.png", 128, 128);
	loadimage(&bigBoom, ".\\boom2.png", 128, 128);
	loadimage(&smallBoom, ".\\boom1.png", 32, 32);
	//��ʼ������
	initializeTheWindows(fight1, fight2, fight3);
	outtextxy(690, 25, "BACK");
	//�����Ѷ�ѡ��ѭ���ı�������
	if (level == EASY) {
		mciSendString("open lawnbgm(8).mp3 alias m7", NULL, 0, NULL);
		mciSendString("play m7 repeat", NULL, 0, NULL);
	}
	else {
		mciSendString("open lawnbgm(5).mp3 alias m8", NULL, 0, NULL);
		mciSendString("play m8 repeat", NULL, 0, NULL);
	}
	//���ų�ʼ��ʬ���
	mciSendString("open awooga.mp3 alias m5", NULL, 0, NULL);
	mciSendString("play m5", NULL, 0, NULL);
	while (go == 0) {//������ս��ʱ����ѭ��
		BeginBatchDraw();/*��ʼ������ͼ*/
		backImage(fight1, fight2, fight3, player.money);/*���Ʊ���*/
		// ��ÿһ֡�����м�鵱ǰʱ��
		currentTime = clock();
		if (currentTime - lastShootingTime >= player.timeBetweenShoot) {
			// ����һ���㶹
			shoot(x, y, player);
			// �����㶹������һ�η����㶹��ʱ��
			lastShootingTime = currentTime;
		}
		if (currentTime - lastCreateZombieTime >= randNum(player.maxTimeBetweenCreateZombie, player.minTimeBetweenCreateZombie)) {
			// ����һ����ʬ
			createZombie(x, y);
			// ������һ�����ɽ�ʬ��ʱ��
			lastCreateZombieTime = currentTime;
		}
		if (currentTime - coinLastShowTime >= COIN_WAIT_TIME) {
			//�ڽ�ҳ���һ��ʱ����Զ���ȡ
			getCoins(player);
			//�����ϴν�ҳ���ʱ��
			coinLastShowTime = currentTime;
		}
		//������ҿ��Ƶ��㶹����
		transparentImage(NULL, x, y, &plant);
		//�㶹����
		peaFly(player.peaSpeed);
		//��ʬǰ��
		zombieMove(player.zombieSpeed, go);
		//��ʬ�ܻ��жϽ���
		hitZombies(player.peaDamage, player.plantSpeed, player, x);
		//����ֲ���ƶ�
		ctrlPlant(x, y, go, player.plantSpeed, player);
		//���Ƴ����㶹
		for (int i = 1; i <= MAX_PEAS; i++) {
			if (pea[i].free == false) {
				if (pea[i].cactus == true) {
					transparentImage(NULL, pea[i].x, pea[i].y, &cactus);
				}
				else {
					transparentImage(NULL, pea[i].x, pea[i].y, &pea0);
				}
			}
		}
		//����Ǯ��
		for (int i = 1; i <= MAX_COINS; i++) {
			switch (coin[i].kind) {
			case GET_SILVER:
				mciSendString("open coin.mp3 alias m3", NULL, 0, NULL);
				mciSendString("play m3", NULL, 0, NULL);
				transparentImage(NULL, coin[i].x, coin[i].y, &silverCoin);
				break;
			case GET_GOLD:
				transparentImage(NULL, coin[i].x, coin[i].y, &goldCoin);
				mciSendString("open coin.mp3 alias m3", NULL, 0, NULL);
				mciSendString("play m3", NULL, 0, NULL);
				break;
			case GET_DIAMOND:
				transparentImage(NULL, coin[i].x, coin[i].y, &diamond);
				break;
			}
		}
		//����ը��
		if (boom.free == false) {
			if (boom.big == true) {
				transparentImage(NULL, boom.x, boom.y, &bigBoom);
			}
			else {
				transparentImage(NULL, boom.x, boom.y, &boom0);
			}
		}
		else {
			//׼������״̬�����Ͻ�ը��ͼ�����ʾ����J���ͷ�ը��
			if (currentTime - boom.lastTimePut > PUT_BOOM_WAIT_TIME) {
				transparentImage(NULL, 0, 0, &smallBoom);
				outtextxy(40, 0, "J");
			}
		}
		//ը����ɱ��ʬ�ж�
		boomKillZombies(player);
		//��ʬ����
		for (int i = 1; i <= MAX_ZOMBIES; i++) {
			if (zombie[i].hp > 0) {
				transparentImage(NULL, zombie[i].x, zombie[i].y, &zombie233);
			}
		}
		EndBatchDraw();/*����������ͼ*/
		Sleep(SLEEPTIME);
	}
	//�����̨���ڸ���ս��״̬�����ʱ��
	switch (go) {
	case BACK:
		printf("ѡ���˷���ս��");
		break;
	case DIE:
		printf("����ʬ�Ե�������");
		break;
	}
	outPutTimeNow();
	//ս����������
	switch (go) {
	case BACK:
		//�����˳���Ч
		mciSendString("open gravebutton.mp3 alias m1", NULL, 0, NULL);
		mciSendString("play m1", NULL, 0, NULL);
		Sleep(500);
		mciSendString(_T("close all"), NULL, 0, NULL);
		//�رմ��ڣ��ص�������
		closegraph();
		home(player);
		break;
	case DIE:
		//ֹͣ���ű�������
		mciSendString(_T("close all"), NULL, 0, NULL);
		//��������
		die(player);
		//ֹͣ������Ч
		mciSendString(_T("close all"), NULL, 0, NULL);
		closegraph();
		home(player);
		break;
	}
}
//����ֲ��
void ctrlPlant(int& x, int& y, int& go, int plantSpeed, save& player) {
	//��ü��������Ϣ
	ExMessage m;
	peekmessage(&m, EX_MOUSE | EX_KEY);
	//�ֱ�����������ƶ�
	if (m.vkcode == W && (y - plantSpeed) >= 50) {
		y = y - plantSpeed;
	}
	if (m.vkcode == A && (x - plantSpeed) >= 40) {
		x = x - plantSpeed;
	}
	if (m.vkcode == S && (y + plantSpeed) <= 500) {
		y = y + plantSpeed;
	}
	if (m.vkcode == D && (x + plantSpeed) <= 700) {
		x = x + plantSpeed;
	}
	//��ը��
	if (m.vkcode == J) {
		createBoom(player, x, y);
	}
	//��ESC���˳���ť�˳�
	if (m.vkcode == VK_ESCAPE) {
		go = BACK;
	}
	if (m.lbutton&&areaCheck(670, 780, 15, 60, m.x, m.y)) {
		go = BACK;
	}
}
//�����㶹
void shoot(int x,int y,save player) {
	//���������ĵ�y��ƫ����
	int deltaY;
	for (int j = 1; j <= player.linesOfPea;j++) {
		//��������ȷ��ƫ����
		deltaY = 30*((2 * j - 1) * int(pow(-1, j)) + 1) / 4;
		for (int i = 1; i <= MAX_PEAS; i++) {
			if (pea[i].free && y + 12 + deltaY > 0 && y + 12 + deltaY < 600) {
				//���㶹���Ϊ������
				pea[i].free = false;
				//��ʼ���㶹λ��
				pea[i].x = x + 69;
				pea[i].y = y + 12 + deltaY;
				pea[i].cactus = (randNum(player.luck.cactus + player.luck.pea, 1) > player.luck.pea);/*������㶹����*/
				break;
			}
		}
	}
}
//�����㶹����
void peaFly(int peaSpeed) {
	for (int i = 1; i < MAX_PEAS; i++) {
		if (!pea[i].free && pea[i].x< WIN_WIDTH) {
			pea[i].x = pea[i].x + peaSpeed;/*���ҷ�*/
		}
		if (pea[i].x >= WIN_WIDTH) {
			pea[i].free = true;/*�ɳ�����*/
		}
	}
}
//���ɽ�ʬ
void createZombie(int x, int y) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		if (zombie[i].hp <= 0) {//ѡ���ڳ���ʬ
			zombie[i].hp = 150 * level;//�Ѷȸ���Ѫ����
			zombie[i].x = 800;//ˢ������Ļ���Ҷ�
			zombie[i].y = randNum(400, 50);//���ˢ��yֵ
			return;
		}
	}
}
//��ʬ���ƶ�
void zombieMove(int zombieSpeed, int& go) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		if (zombie[i].hp > 0) {//�Իʬ
			zombie[i].x = zombie[i].x - zombieSpeed;/*������*/
			if (zombie[i].x == 40 && zombie[i].y < 400 && zombie[i].y>0) {
				go = DIE;/*�ߵ�����ʱ��ʬ�Ե�������Դ�*/
				return;
			}
		}
	}
}
//��ʬ�ж�
void hitZombies(int damage,int peaSpeed, save& player,int x) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		for (int j = 1; j <= MAX_PEAS; j++) {
			//�жϽ�ʬ�Ƿ񱻸����㶹����
			bool area = areaCheck(zombie[i].x - peaSpeed, zombie[i].x + peaSpeed, zombie[i].y-20, zombie[i].y + 135, pea[j].x, pea[j].y);
			if (zombie[i].hp > 0 && area&&(!pea[j].free)) {
				if (zombie[i].hp - damage <= 0) {
					kill++;/*������*/
					std::cout << "�����˵�" << kill << "����ʬ";
					//������Ч
					mciSendString("open tap.mp3 alias m4", NULL, 0, NULL);
					mciSendString("play m4", NULL, 0, NULL);
					//�����Ѷȸ���������
					if (level == EASY) {
						player.money = add(player.money, BASICAWARD);
					}
					else {
						player.money = add(player.money, HD_BASICAWARD);
					}
					//�и��ʱ����
					createCoinFromZombies(player, zombie[i].x, zombie[i].y);
					//�ڿ���̨�����ʱ��
					outPutTimeNow();
				}
				//û��������Ѫ
				zombie[i].hp = zombie[i].hp - damage;
				if (pea[j].cactus == true) {
					zombie[i].hp = zombie[i].hp - damage;
				}
				if (abs(zombie[i].x - x) <= 150) {
					zombie[i].hp = zombie[i].hp - damage;
				}
				pea[j].free = true;/*�����н�ʬ���㶹���Ϊ����*/
			}
		}
	}
}
//�����������
void die(save& player) {
	//���壬���룬�ų���������
	IMAGE ZombiesWon;
	loadimage(&ZombiesWon, "./ZombiesWon.jpg", 800, 600);
	putimage(0, 0, &ZombiesWon);
	//����ǰ��Ǯ�����������ͷ�ϵ���ٳ��������ͷ�ϵ����ȥ�Ѷ�ϵ��
	string temp1, temp2;
	div(player.money, player.lostAfterDie, temp1, temp2);
	player.money = temp1;
	if (level == EASY) {
		player.money = mul(player.money, sub(player.lostAfterDie, "1"));
	}
	else {
		player.money = mul(player.money, sub(player.lostAfterDie, "2"));
	}
	//����������Ч
	mciSendString("open losemusic.mp3 alias m7", NULL, 0, NULL);
	mciSendString("play m7", NULL, 0, NULL);
	Sleep(DIE_WAIT_TIME);
}
//�����
void createCoinFromZombies(save& player, int x, int y) {
	for (int i = 1; i <= MAX_COINS; i++) {
		if (coin[i].free = true) {
			int kind;
			//ѡ������
			kind = chooseCoinKind(player.luck);
			if (kind == GET_BASICAWARD) {
				//û������
				coin[i].kind = kind;
			}
			else {
				//�����λ���뽩ʬ����λ����ͬ
				coin[i].kind = kind;
				coin[i].free = false;/*����ұ��Ϊ������*/
				coin[i].x = x;
				coin[i].y = y;
			}
			return;
		}
	}
}
//����
void getCoins(save& player) {
	for (int i = 1; i <= MAX_COINS; i++) {
		if (coin[i].free == false) {
			coin[i].free = true;/*���������Ľ�ұ��Ϊ����*/
			//�����ѶȽ��㲻ͬ�ֻ��Ҽ�ֵ
			if (level == EASY) {
				switch (coin[i].kind) {
				case GET_SILVER:
					player.money = add(player.money, SILVER);
					break;
				case GET_GOLD:
					player.money = add(player.money, GOLD);
					break;
				case GET_DIAMOND:
					player.money = add(player.money, DIAMOND);
					break;
				}
			}
			else {
				switch (coin[i].kind) {
				case GET_SILVER:
					player.money = add(player.money, HD_SILVER);
					break;
				case GET_GOLD:
					player.money = add(player.money, HD_GOLD);
					break;
				case GET_DIAMOND:
					player.money = add(player.money, HD_DIAMOND);
					break;
				}
			}
		}
	}
}
//��ʼ��ս����ʼʱ��ʬ״̬
void initializeTheFight() {
	for (int i = 1; i <= MAX_ZOMBIES;i++) {
		zombie[i].x = 800;
		zombie[i].hp = -1;
	}
}
//��ը��
void createBoom(save player, int x, int y) {
	clock_t currentTime = clock();
	if (currentTime - boom.lastTimePut > PUT_BOOM_WAIT_TIME/level) {
		boom.free = false;
		//����ը��λ����ֲ��λ����ͬ
		boom.x = x;
		boom.y = y;
		//ȷ��ը������
		boom.big = (randNum(player.luck.boom + player.luck.bigBoom, 1) > player.luck.boom);
		//����ը������ʱ��
		boom.lastTimePut = currentTime;
	}
}
void boomKillZombies(save& player) {
	clock_t currentTime = clock();
	if (currentTime - boom.lastTimePut >= BOOM_WAIT_TIME && boom.free == false) {
		//��ը�����Ϊ����
		boom.free = true;
		//����ը����ը��Ч
		mciSendString("open jalapeno.mp3 alias m2", NULL, 0, NULL);
		mciSendString("play m2", NULL, 0, NULL);
		//����ը�������жϽ�ʬ��ը�����
		for (int i = 1; i <= MAX_ZOMBIES; i++) {
			if (zombie[i].hp >= 0) {
				if (boom.big == true) {
					if (areaCheck(boom.x - 350, boom.x + 350, boom.y - 350, boom.y + 350, zombie[i].x, zombie[i].y)) {
						zombie[i].hp = -1;
					}
				}
				else {
					if (areaCheck(boom.x - 200, boom.x + 200, boom.y - 200, boom.y + 200, zombie[i].x, zombie[i].y)) {
						zombie[i].hp = -1;
					}
				}
				player.money = add(player.money, BASICAWARD);/*�����������*/
			}
		}
	}
}