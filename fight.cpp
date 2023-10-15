//文件名：fight.cpp
//战斗系统
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
// 引用 Windows Multimedia API
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
//本文件定义函数
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
//其他非tool.cpp定义函数
void home(save& player);
//tool.cpp中的函数
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
//定义结构体
struct peas {
	int x;
	int y;
	bool free = true;/*是否能用于发射*/
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
	bool free = true;/*是否能用于出现在场上*/
	int kind;
};
struct booms {
	int x = 0;
	int y = 0;
	bool free = true;/*是否为准备完毕可用状态*/
	bool big = false;
	clock_t lastTimePut;/*上次放下炸弹时间*/
};
//定义有关数组
peas pea[MAX_PEAS];
zombies zombie[MAX_ZOMBIES];
coins coin[MAX_COINS];
//定义有关全局变量
booms boom;
int kill;
int level;
//战斗界面主函数
void fight(save& player,int level_) {
	//定义图片
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
	//读取难度
	level = level_;
	//初始化战斗状态
	int go = 0;
	//初始化豌豆射手位置
	int x = 48;
	int y = 80;
	//初始化僵尸位置
	initializeTheFight();
	// 初始化时间戳
	clock_t lastShootingTime = clock();/*上次豌豆发射时间*/
	clock_t lastCreateZombieTime = lastShootingTime;/*上次僵尸生成时间*/
	clock_t coinLastShowTime = lastShootingTime;/*上次硬币出现时间*/
	clock_t lastBoomTime = lastShootingTime;/*上次炸弹安放时间*/
	clock_t currentTime;/*实时更新的时间戳*/
	kill = 0;/*僵尸击杀数初始化*/
	//加载图片
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
	//初始化背景
	initializeTheWindows(fight1, fight2, fight3);
	outtextxy(690, 25, "BACK");
	//根据难度选择循环的背景音乐
	if (level == EASY) {
		mciSendString("open lawnbgm(8).mp3 alias m7", NULL, 0, NULL);
		mciSendString("play m7 repeat", NULL, 0, NULL);
	}
	else {
		mciSendString("open lawnbgm(5).mp3 alias m8", NULL, 0, NULL);
		mciSendString("play m8 repeat", NULL, 0, NULL);
	}
	//播放初始僵尸吼叫
	mciSendString("open awooga.mp3 alias m5", NULL, 0, NULL);
	mciSendString("play m5", NULL, 0, NULL);
	while (go == 0) {//在正常战斗时保持循环
		BeginBatchDraw();/*开始批量绘图*/
		backImage(fight1, fight2, fight3, player.money);/*绘制背景*/
		// 在每一帧画面中检查当前时间
		currentTime = clock();
		if (currentTime - lastShootingTime >= player.timeBetweenShoot) {
			// 发射一个豌豆
			shoot(x, y, player);
			// 更新豌豆射手上一次发射豌豆的时间
			lastShootingTime = currentTime;
		}
		if (currentTime - lastCreateZombieTime >= randNum(player.maxTimeBetweenCreateZombie, player.minTimeBetweenCreateZombie)) {
			// 生成一个僵尸
			createZombie(x, y);
			// 更新上一次生成僵尸的时间
			lastCreateZombieTime = currentTime;
		}
		if (currentTime - coinLastShowTime >= COIN_WAIT_TIME) {
			//在金币出现一段时间后自动收取
			getCoins(player);
			//更新上次金币出现时间
			coinLastShowTime = currentTime;
		}
		//绘制玩家控制的豌豆射手
		transparentImage(NULL, x, y, &plant);
		//豌豆飞行
		peaFly(player.peaSpeed);
		//僵尸前进
		zombieMove(player.zombieSpeed, go);
		//僵尸受击判断结算
		hitZombies(player.peaDamage, player.plantSpeed, player, x);
		//控制植物移动
		ctrlPlant(x, y, go, player.plantSpeed, player);
		//绘制场上豌豆
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
		//绘制钱币
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
		//绘制炸弹
		if (boom.free == false) {
			if (boom.big == true) {
				transparentImage(NULL, boom.x, boom.y, &bigBoom);
			}
			else {
				transparentImage(NULL, boom.x, boom.y, &boom0);
			}
		}
		else {
			//准备可用状态：坐上交炸弹图标加提示按“J”释放炸弹
			if (currentTime - boom.lastTimePut > PUT_BOOM_WAIT_TIME) {
				transparentImage(NULL, 0, 0, &smallBoom);
				outtextxy(40, 0, "J");
			}
		}
		//炸弹击杀僵尸判断
		boomKillZombies(player);
		//僵尸绘制
		for (int i = 1; i <= MAX_ZOMBIES; i++) {
			if (zombie[i].hp > 0) {
				transparentImage(NULL, zombie[i].x, zombie[i].y, &zombie233);
			}
		}
		EndBatchDraw();/*结束批量绘图*/
		Sleep(SLEEPTIME);
	}
	//向控制台窗口更新战斗状态并输出时间
	switch (go) {
	case BACK:
		printf("选择了放弃战斗");
		break;
	case DIE:
		printf("被僵尸吃掉了脑子");
		break;
	}
	outPutTimeNow();
	//战斗结束结算
	switch (go) {
	case BACK:
		//播放退出音效
		mciSendString("open gravebutton.mp3 alias m1", NULL, 0, NULL);
		mciSendString("play m1", NULL, 0, NULL);
		Sleep(500);
		mciSendString(_T("close all"), NULL, 0, NULL);
		//关闭窗口，回到主界面
		closegraph();
		home(player);
		break;
	case DIE:
		//停止播放背景音乐
		mciSendString(_T("close all"), NULL, 0, NULL);
		//死亡结算
		die(player);
		//停止播放音效
		mciSendString(_T("close all"), NULL, 0, NULL);
		closegraph();
		home(player);
		break;
	}
}
//控制植物
void ctrlPlant(int& x, int& y, int& go, int plantSpeed, save& player) {
	//获得键盘鼠标消息
	ExMessage m;
	peekmessage(&m, EX_MOUSE | EX_KEY);
	//分别向各个方向移动
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
	//放炸弹
	if (m.vkcode == J) {
		createBoom(player, x, y);
	}
	//按ESC或按退出按钮退出
	if (m.vkcode == VK_ESCAPE) {
		go = BACK;
	}
	if (m.lbutton&&areaCheck(670, 780, 15, 60, m.x, m.y)) {
		go = BACK;
	}
}
//发射豌豆
void shoot(int x,int y,save player) {
	//发射点对中心的y轴偏移量
	int deltaY;
	for (int j = 1; j <= player.linesOfPea;j++) {
		//根据行数确定偏移量
		deltaY = 30*((2 * j - 1) * int(pow(-1, j)) + 1) / 4;
		for (int i = 1; i <= MAX_PEAS; i++) {
			if (pea[i].free && y + 12 + deltaY > 0 && y + 12 + deltaY < 600) {
				//将豌豆标记为不可用
				pea[i].free = false;
				//初始化豌豆位置
				pea[i].x = x + 69;
				pea[i].y = y + 12 + deltaY;
				pea[i].cactus = (randNum(player.luck.cactus + player.luck.pea, 1) > player.luck.pea);/*随机出豌豆种类*/
				break;
			}
		}
	}
}
//控制豌豆飞行
void peaFly(int peaSpeed) {
	for (int i = 1; i < MAX_PEAS; i++) {
		if (!pea[i].free && pea[i].x< WIN_WIDTH) {
			pea[i].x = pea[i].x + peaSpeed;/*向右飞*/
		}
		if (pea[i].x >= WIN_WIDTH) {
			pea[i].free = true;/*飞出界了*/
		}
	}
}
//生成僵尸
void createZombie(int x, int y) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		if (zombie[i].hp <= 0) {//选择不在场僵尸
			zombie[i].hp = 150 * level;//难度高则血量高
			zombie[i].x = 800;//刷新在屏幕最右端
			zombie[i].y = randNum(400, 50);//随机刷新y值
			return;
		}
	}
}
//僵尸的移动
void zombieMove(int zombieSpeed, int& go) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		if (zombie[i].hp > 0) {//对活僵尸
			zombie[i].x = zombie[i].x - zombieSpeed;/*向左走*/
			if (zombie[i].x == 40 && zombie[i].y < 400 && zombie[i].y>0) {
				go = DIE;/*走到最左时僵尸吃掉了你的脑袋*/
				return;
			}
		}
	}
}
//打僵尸判断
void hitZombies(int damage,int peaSpeed, save& player,int x) {
	for (int i = 1; i <= MAX_ZOMBIES; i++) {
		for (int j = 1; j <= MAX_PEAS; j++) {
			//判断僵尸是否被附近豌豆打中
			bool area = areaCheck(zombie[i].x - peaSpeed, zombie[i].x + peaSpeed, zombie[i].y-20, zombie[i].y + 135, pea[j].x, pea[j].y);
			if (zombie[i].hp > 0 && area&&(!pea[j].free)) {
				if (zombie[i].hp - damage <= 0) {
					kill++;/*打死了*/
					std::cout << "打死了第" << kill << "个僵尸";
					//播放音效
					mciSendString("open tap.mp3 alias m4", NULL, 0, NULL);
					mciSendString("play m4", NULL, 0, NULL);
					//根据难度给基本奖励
					if (level == EASY) {
						player.money = add(player.money, BASICAWARD);
					}
					else {
						player.money = add(player.money, HD_BASICAWARD);
					}
					//有概率爆金币
					createCoinFromZombies(player, zombie[i].x, zombie[i].y);
					//在控制台中输出时间
					outPutTimeNow();
				}
				//没打死，扣血
				zombie[i].hp = zombie[i].hp - damage;
				if (pea[j].cactus == true) {
					zombie[i].hp = zombie[i].hp - damage;
				}
				if (abs(zombie[i].x - x) <= 150) {
					zombie[i].hp = zombie[i].hp - damage;
				}
				pea[j].free = true;/*将击中僵尸的豌豆标记为可用*/
			}
		}
	}
}
//玩家死亡结算
void die(save& player) {
	//定义，载入，放出死亡画面
	IMAGE ZombiesWon;
	loadimage(&ZombiesWon, "./ZombiesWon.jpg", 800, 600);
	putimage(0, 0, &ZombiesWon);
	//将当前的钱数除以死亡惩罚系数再乘上死亡惩罚系数减去难度系数
	string temp1, temp2;
	div(player.money, player.lostAfterDie, temp1, temp2);
	player.money = temp1;
	if (level == EASY) {
		player.money = mul(player.money, sub(player.lostAfterDie, "1"));
	}
	else {
		player.money = mul(player.money, sub(player.lostAfterDie, "2"));
	}
	//播放死亡音效
	mciSendString("open losemusic.mp3 alias m7", NULL, 0, NULL);
	mciSendString("play m7", NULL, 0, NULL);
	Sleep(DIE_WAIT_TIME);
}
//爆金币
void createCoinFromZombies(save& player, int x, int y) {
	for (int i = 1; i <= MAX_COINS; i++) {
		if (coin[i].free = true) {
			int kind;
			//选择种类
			kind = chooseCoinKind(player.luck);
			if (kind == GET_BASICAWARD) {
				//没爆出来
				coin[i].kind = kind;
			}
			else {
				//爆金币位置与僵尸死亡位置相同
				coin[i].kind = kind;
				coin[i].free = false;/*将金币标记为不可用*/
				coin[i].x = x;
				coin[i].y = y;
			}
			return;
		}
	}
}
//捡金币
void getCoins(save& player) {
	for (int i = 1; i <= MAX_COINS; i++) {
		if (coin[i].free == false) {
			coin[i].free = true;/*将捡起来的金币标记为可用*/
			//根据难度结算不同种货币价值
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
//初始化战斗开始时僵尸状态
void initializeTheFight() {
	for (int i = 1; i <= MAX_ZOMBIES;i++) {
		zombie[i].x = 800;
		zombie[i].hp = -1;
	}
}
//放炸弹
void createBoom(save player, int x, int y) {
	clock_t currentTime = clock();
	if (currentTime - boom.lastTimePut > PUT_BOOM_WAIT_TIME/level) {
		boom.free = false;
		//放下炸弹位置与植物位置相同
		boom.x = x;
		boom.y = y;
		//确定炸弹种类
		boom.big = (randNum(player.luck.boom + player.luck.bigBoom, 1) > player.luck.boom);
		//更新炸弹安放时间
		boom.lastTimePut = currentTime;
	}
}
void boomKillZombies(save& player) {
	clock_t currentTime = clock();
	if (currentTime - boom.lastTimePut >= BOOM_WAIT_TIME && boom.free == false) {
		//将炸弹标记为可用
		boom.free = true;
		//播放炸弹爆炸音效
		mciSendString("open jalapeno.mp3 alias m2", NULL, 0, NULL);
		mciSendString("play m2", NULL, 0, NULL);
		//根据炸弹种类判断僵尸被炸死情况
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
				player.money = add(player.money, BASICAWARD);/*结算基本奖励*/
			}
		}
	}
}