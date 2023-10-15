//文件名：shop.cpp
//本文件实现了商店的图象构建与相关功能
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
#include <vector>
using namespace std;
#pragma comment( lib, "MSIMG32.LIB")
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SLEEPTIME 40
#define BACK 1
//本文件定义函数
void shop(save& player);
void shopScreen(save& player);
void shopButton(int& go, save& player);
//非tool.cpp的其他文件定义函数
void home(save& player);
//使用的tool.cpp中的函数
void outPutTimeNow();
void initializeTheWindows(IMAGE titlesreen);
bool areaCheck(int xLeft, int xRight, int yHigh, int yLow, int x, int y);
int compare(string str1, string str2);
string add(string str1, string str2);
string sub(string str1, string str2);
string mul(string str1, string str2);
void div(string str1, string str2, string& quotient, string& residue);
void backImage(IMAGE image1, string money);
int sgn(double x);
int randNum(int maxNum, int minNum);
//本文件用到的全局变量
IMAGE shop1;
//本文件主要函数
void shop(save& player) {
	//开始循环播放背景音乐
	mciSendString("open lawnbgm(6).mp3 alias m9", NULL, 0, NULL);
	mciSendString("play m9 repeat", NULL, 0, NULL);
	int go = NULL;/*初始化界面选择状态*/
	shopScreen(player);/*初始化窗体及背景图片*/
	while (go == NULL) {//在未选择进入下一个画面前循环
		BeginBatchDraw();/*开始批量绘图*/
		backImage(shop1,player.money);
		shopButton(go, player);
		//显示玩家现金
		outtextxy(100, 530, player.money.c_str());
		//显示价格
		outtextxy(120, 20, player.price.luckyBox.c_str());
		outtextxy(120, 55, player.price.coffeeBean.c_str());
		outtextxy(120, 90, player.price.morePea.c_str());
		outtextxy(120, 120, player.price.moreCactus.c_str());
		outtextxy(160, 160, player.price.moreLuck.c_str());
		EndBatchDraw();/*结束批量绘图*/
		Sleep(SLEEPTIME);
	}
	switch (go) {
	//退出购物，向控制台记录时间，停止播放背景音乐，关闭窗口
	case BACK:
		printf("选择了结束购物");
		mciSendString(_T("close all"), NULL, 0, NULL);
		home(player);
		break;
	}
	outPutTimeNow();
	closegraph();
}
void shopScreen(save& player) {
	//初始化窗体
	loadimage(&shop1, ".\\shop1.png", WIN_WIDTH, WIN_HEIGHT);
	initializeTheWindows(shop1);
	outtextxy(690, 25, "BACK");
}
void shopButton(int& go, save& player) {
	//获取一个鼠标键盘消息
	ExMessage m;
	m = getmessage(EX_MOUSE | EX_KEY);
	//判断键盘消息
	if (m.vkcode == VK_ESCAPE) {
		//按ESC退出商店
		go = BACK;
		return;
	}
	//判断鼠标消息
	if (m.lbutton) {
		//按退出键
		if (areaCheck(670, 780, 15, 60, m.x, m.y)) {
			go = BACK;
			return;
		}
		else {
			//选择了购买物品，若成功购买则播放钱减少音效
			if (areaCheck(220, 320, 200, 310, m.x, m.y) && compare(player.money, player.price.luckyBox) != -1) {
				mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
				mciSendString("play m6", NULL, 0, NULL);
				//选择购买盲盒
				player.money = sub(player.money, player.price.luckyBox);/*扣除成本*/
				//产生奖金金额
				int temp = randNum(1000, 1);/*产生一个1到1000的随机数*/
				if (temp <= 995) {
					//小于等于995时奖金线性变化（temp=400时回收成本，综合中奖率60%）
					temp = int(4284 / 400 * temp);
				}
				else {
					//大于995时获得成指数变化的高额奖金
					temp = 4284 + 8 << (temp - 990);
				}
				player.money = add(player.money, to_string(temp));/*获得奖金*/
				return;
			}
			else {
				if (areaCheck(510, 610, 80, 165, m.x, m.y) && compare(player.money, player.price.moreLuck) != -1) {
					mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
					mciSendString("play m6", NULL, 0, NULL);
					//选择购买幸运鸡肉卷
					player.money = sub(player.money, player.price.moreLuck);/*扣钱*/
					//哇，爆率是真的高
					player.luck.gold += 100;
					player.luck.diamond += 20;
					player.luck.bigBoom += 200;
					//减少失败时惩罚
					player.lostAfterDie = add(player.lostAfterDie, "1");
					return;
				}
				else {
					if (areaCheck(320, 480, 50, 180, m.x, m.y) && compare(player.money, player.price.moreCactus) != -1) {
						mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
						mciSendString("play m6", NULL, 0, NULL);
						//选择了购买更多尖刺
						player.money = sub(player.money, player.price.moreCactus);/*扣钱*/
						player.luck.cactus += 300;/*高伤害的尖刺增加了*/
						player.price.moreCactus = mul(player.price.moreCactus, "2");/*下次价格翻倍*/
						return;
					}
					else {
						if (areaCheck(370, 460, 200, 320, m.x, m.y) && compare(player.money, player.price.coffeeBean) != -1) {
							mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
							mciSendString("play m6", NULL, 0, NULL);
							//选择了购买咖啡豆
							player.money = sub(player.money, player.price.coffeeBean);/*扣钱*/
							player.plantSpeed += 5;/*植物移动速度提升*/
							return;
						}
						else {
							if (areaCheck(520, 640, 210, 360, m.x, m.y) && compare(player.money, player.price.morePea) != -1) {
								mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
								mciSendString("play m6", NULL, 0, NULL);
								//选择了购买豌豆
								player.money = sub(player.money, player.price.morePea);/*扣钱*/
								player.linesOfPea++;/*多射一发豌豆*/
								player.price.morePea = mul(player.price.morePea, "5");/*价格超级加倍*/
								//僵尸生成间隔减少
								player.maxTimeBetweenCreateZombie /= 1.2;
								player.minTimeBetweenCreateZombie /= 1.2;
								return;
							}
						}
					}
				}
			}
		}
	}
}