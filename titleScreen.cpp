//文件名：titleScreen.cpp
//绘制了开始界面
#include <graphics.h>
#include <conio.h>
#include <iostream>      
#include <stdio.h>
#include <windows.h>		
#include <mmsystem.h>
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
//本文件定义函数
void startGame();
//使用的tool.cpp中的函数
void initializeTheWindows(IMAGE titlesreen);
bool mouseCheck(int xLeft, int xRight, int yHigh, int yLow);
void outPutTimeNow();
//startGame 开始游戏（开始游戏界面的主函数）
void startGame() {
	//定义按键位置数据如下
	int xLeft;
	int xRight;
	int yHigh;
	int yLow;
	xLeft = 240;
	xRight = 560;
	yHigh = 500;
	yLow = 553;
	//导入并绘制背景图片
	IMAGE titlesreen;
	loadimage(&titlesreen, ".\\titlescreen.png", WIN_WIDTH, WIN_HEIGHT);
	initializeTheWindows(titlesreen);
	//书写“开始游戏”字样
	int xText = WIN_WIDTH / 2 - 50;
	int yText = yHigh + 10;
	outtextxy(xText, yText, "开始游戏！");
	//等待鼠标点击开始游戏
	while (mouseCheck(xLeft, xRight, yHigh, yLow) == false) {
		//空语句
	}
	//在控制台中记录开始游戏事件及时间
	printf("开始游戏");
	outPutTimeNow();
	//播放僵尸吼叫声
	mciSendString(_T("open evillaugh.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	Sleep(4000);
	//退出开始游戏界面
	closegraph();
}