//�ļ�����shop.cpp
//���ļ�ʵ�����̵��ͼ�󹹽�����ع���
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
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SLEEPTIME 40
#define BACK 1
//���ļ����庯��
void shop(save& player);
void shopScreen(save& player);
void shopButton(int& go, save& player);
//��tool.cpp�������ļ����庯��
void home(save& player);
//ʹ�õ�tool.cpp�еĺ���
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
//���ļ��õ���ȫ�ֱ���
IMAGE shop1;
//���ļ���Ҫ����
void shop(save& player) {
	//��ʼѭ�����ű�������
	mciSendString("open lawnbgm(6).mp3 alias m9", NULL, 0, NULL);
	mciSendString("play m9 repeat", NULL, 0, NULL);
	int go = NULL;/*��ʼ������ѡ��״̬*/
	shopScreen(player);/*��ʼ�����弰����ͼƬ*/
	while (go == NULL) {//��δѡ�������һ������ǰѭ��
		BeginBatchDraw();/*��ʼ������ͼ*/
		backImage(shop1,player.money);
		shopButton(go, player);
		//��ʾ����ֽ�
		outtextxy(100, 530, player.money.c_str());
		//��ʾ�۸�
		outtextxy(120, 20, player.price.luckyBox.c_str());
		outtextxy(120, 55, player.price.coffeeBean.c_str());
		outtextxy(120, 90, player.price.morePea.c_str());
		outtextxy(120, 120, player.price.moreCactus.c_str());
		outtextxy(160, 160, player.price.moreLuck.c_str());
		EndBatchDraw();/*����������ͼ*/
		Sleep(SLEEPTIME);
	}
	switch (go) {
	//�˳���������̨��¼ʱ�䣬ֹͣ���ű������֣��رմ���
	case BACK:
		printf("ѡ���˽�������");
		mciSendString(_T("close all"), NULL, 0, NULL);
		home(player);
		break;
	}
	outPutTimeNow();
	closegraph();
}
void shopScreen(save& player) {
	//��ʼ������
	loadimage(&shop1, ".\\shop1.png", WIN_WIDTH, WIN_HEIGHT);
	initializeTheWindows(shop1);
	outtextxy(690, 25, "BACK");
}
void shopButton(int& go, save& player) {
	//��ȡһ����������Ϣ
	ExMessage m;
	m = getmessage(EX_MOUSE | EX_KEY);
	//�жϼ�����Ϣ
	if (m.vkcode == VK_ESCAPE) {
		//��ESC�˳��̵�
		go = BACK;
		return;
	}
	//�ж������Ϣ
	if (m.lbutton) {
		//���˳���
		if (areaCheck(670, 780, 15, 60, m.x, m.y)) {
			go = BACK;
			return;
		}
		else {
			//ѡ���˹�����Ʒ�����ɹ������򲥷�Ǯ������Ч
			if (areaCheck(220, 320, 200, 310, m.x, m.y) && compare(player.money, player.price.luckyBox) != -1) {
				mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
				mciSendString("play m6", NULL, 0, NULL);
				//ѡ����ä��
				player.money = sub(player.money, player.price.luckyBox);/*�۳��ɱ�*/
				//����������
				int temp = randNum(1000, 1);/*����һ��1��1000�������*/
				if (temp <= 995) {
					//С�ڵ���995ʱ�������Ա仯��temp=400ʱ���ճɱ����ۺ��н���60%��
					temp = int(4284 / 400 * temp);
				}
				else {
					//����995ʱ��ó�ָ���仯�ĸ߶��
					temp = 4284 + 8 << (temp - 990);
				}
				player.money = add(player.money, to_string(temp));/*��ý���*/
				return;
			}
			else {
				if (areaCheck(510, 610, 80, 165, m.x, m.y) && compare(player.money, player.price.moreLuck) != -1) {
					mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
					mciSendString("play m6", NULL, 0, NULL);
					//ѡ�������˼����
					player.money = sub(player.money, player.price.moreLuck);/*��Ǯ*/
					//�ۣ���������ĸ�
					player.luck.gold += 100;
					player.luck.diamond += 20;
					player.luck.bigBoom += 200;
					//����ʧ��ʱ�ͷ�
					player.lostAfterDie = add(player.lostAfterDie, "1");
					return;
				}
				else {
					if (areaCheck(320, 480, 50, 180, m.x, m.y) && compare(player.money, player.price.moreCactus) != -1) {
						mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
						mciSendString("play m6", NULL, 0, NULL);
						//ѡ���˹��������
						player.money = sub(player.money, player.price.moreCactus);/*��Ǯ*/
						player.luck.cactus += 300;/*���˺��ļ��������*/
						player.price.moreCactus = mul(player.price.moreCactus, "2");/*�´μ۸񷭱�*/
						return;
					}
					else {
						if (areaCheck(370, 460, 200, 320, m.x, m.y) && compare(player.money, player.price.coffeeBean) != -1) {
							mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
							mciSendString("play m6", NULL, 0, NULL);
							//ѡ���˹��򿧷ȶ�
							player.money = sub(player.money, player.price.coffeeBean);/*��Ǯ*/
							player.plantSpeed += 5;/*ֲ���ƶ��ٶ�����*/
							return;
						}
						else {
							if (areaCheck(520, 640, 210, 360, m.x, m.y) && compare(player.money, player.price.morePea) != -1) {
								mciSendString("open moneyfalls.mp3 alias m6", NULL, 0, NULL);
								mciSendString("play m6", NULL, 0, NULL);
								//ѡ���˹����㶹
								player.money = sub(player.money, player.price.morePea);/*��Ǯ*/
								player.linesOfPea++;/*����һ���㶹*/
								player.price.morePea = mul(player.price.morePea, "5");/*�۸񳬼��ӱ�*/
								//��ʬ���ɼ������
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