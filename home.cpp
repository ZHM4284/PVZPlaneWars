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
#pragma comment(lib,"Winmm.lib")
void home(save& player);
void homeScreen(string& money);
void homeButton(int& go);
void fight(save& player, int level_);
void shop(save& player);
void outPutTimeNow();
void initializeTheWindows(IMAGE titlesreen);
bool areaCheck(int xLeft, int xRight, int yHigh, int yLow, int x, int y);
void backImage(IMAGE image1, int level_, string money);
int level_ = 1;
IMAGE home0;
void home(save& player) {
	int go = NULL;
	homeScreen(player.money);
	mciSendString("open lawnbgm(14).mp3 alias BGM", NULL, 0, NULL);
	mciSendString("play BGM repeat", NULL, 0, NULL);
	Sleep(2000);
	while (go == NULL) {
		homeButton(go);
		BeginBatchDraw();
		backImage(home0, level_, player.money);
		EndBatchDraw();
		Sleep(20);
	}
	switch (go) {
	case 2:
		printf("选择了开始战斗");
		break;
	case 1:
		printf("选择了购买物品");
		break;
	}
	outPutTimeNow();
	closegraph();
	mciSendString("close all", NULL, 0, NULL);
	switch (go) {
	case 2:
		fight(player, level_);
		break;
	case 1:
		shop(player);
		break;
	case 3:
		return;
	}
}
void homeScreen(string& money) {
	loadimage(&home0, ".\\home.png", 800, 600);
	initializeTheWindows(home0);
	outtextxy(30, 20, "开始战斗！");
	outtextxy(200, 540, "tips:按esc存档后退出,否则你会永久失去你的存档(真的很久)!");
	outtextxy(65, 550, money.c_str());
}
void homeButton(int& go) {
	ExMessage m;
	m = getmessage(EX_MOUSE | EX_KEY);
	if (areaCheck(14, 144, 15, 60, m.x, m.y) && m.lbutton) {
		go = 2;
		return;
	}
	if (areaCheck(650, 800, 14, 80, m.x, m.y) && m.lbutton) {
		go = 1;
		return;
	}
	if (areaCheck(120, 320, 115, 315, m.x, m.y) && m.lbutton) {
		level_ = 1;
		return;
	}
	if (areaCheck(475, 677, 115, 312, m.x, m.y) && m.lbutton) {
		level_ = 2;
		return;
	}
	if (m.vkcode == VK_ESCAPE) {
		go = 3;
		return;
	}
}

