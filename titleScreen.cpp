//�ļ�����titleScreen.cpp
//�����˿�ʼ����
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
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
//���ļ����庯��
void startGame();
//ʹ�õ�tool.cpp�еĺ���
void initializeTheWindows(IMAGE titlesreen);
bool mouseCheck(int xLeft, int xRight, int yHigh, int yLow);
void outPutTimeNow();
//startGame ��ʼ��Ϸ����ʼ��Ϸ�������������
void startGame() {
	//���尴��λ����������
	int xLeft;
	int xRight;
	int yHigh;
	int yLow;
	xLeft = 240;
	xRight = 560;
	yHigh = 500;
	yLow = 553;
	//���벢���Ʊ���ͼƬ
	IMAGE titlesreen;
	loadimage(&titlesreen, ".\\titlescreen.png", WIN_WIDTH, WIN_HEIGHT);
	initializeTheWindows(titlesreen);
	//��д����ʼ��Ϸ������
	int xText = WIN_WIDTH / 2 - 50;
	int yText = yHigh + 10;
	outtextxy(xText, yText, "��ʼ��Ϸ��");
	//�ȴ��������ʼ��Ϸ
	while (mouseCheck(xLeft, xRight, yHigh, yLow) == false) {
		//�����
	}
	//�ڿ���̨�м�¼��ʼ��Ϸ�¼���ʱ��
	printf("��ʼ��Ϸ");
	outPutTimeNow();
	//���Ž�ʬ�����
	mciSendString(_T("open evillaugh.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	Sleep(4000);
	//�˳���ʼ��Ϸ����
	closegraph();
}