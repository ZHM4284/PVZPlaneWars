//�ļ�����tool.cpp
//���������ɹ����Եĺ���
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

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define BUFFERSIZE 1024
#define GET_BASICAWARD 0
#define GET_SILVER 1
#define GET_GOLD 2
#define GET_DIAMOND 3
#define EASY 1
#define HARD 2

bool areaCheck(int xLeft, int xRight, int High, int yLow, int x, int y);
bool mouseCheck(int xLeft, int xRight, int yHigh, int yLow);
void outPutTimeNow();
void initializeTheWindows(IMAGE titlesreen);
void initializeTheWindows(IMAGE image1, IMAGE image2, IMAGE image3);
void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void backImage(IMAGE image1, IMAGE image2, IMAGE image3, string money);
void backImage(IMAGE image1, string money);
int randNum(int maxNum, int minNum);
int compare(string str1, string str2);
string add(string str1, string str2);
string sub(string str1, string str2);
string mul(string str1, string str2);
void div(string str1, string str2, string& quotient, string& residue);
int sgn(double x);

//outPutTimeNow�����̨�����ǰʱ��
void outPutTimeNow() {
	struct tm t;    //tm�ṹָ��
	char stTmp[32];
	time_t now;        //����time_t���ͱ���
	time(&now);        //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);    //��ȡ�������ں�ʱ��
	asctime_s(stTmp, &t);
	std::cout <<"\t\t"<<stTmp << std::endl;
}
//areaCheck:
//���룺
//xLeft,xRight,yHigh,yLow �������±߽��Ķ�Ӧ����
//x,y ���жϵ������
//���ܣ�
//�жϴ��жϵ��Ƿ��ڸ����������򣨲����߽磩��
//����ֵ��
//�ڷ�Χ�ڷ���true,���򷵻�false
bool areaCheck(int xLeft, int xRight, int yHigh, int yLow, int x, int y) {
	return (x > xLeft && x<xRight&& y>yHigh && y < yLow);
}
//mouseCheck:
//���룺
//xLeft,xRight,yHigh,yLow �������±߽��Ķ�Ӧ����
//���ܣ�
//�ȴ�һ�������������Ϣ���жϵ��λ���Ƿ��ڸ����ľ������򣨲����߽磩��
//����ֵ��
//�ڷ�Χ�ڷ���true,���򷵻�false
bool mouseCheck(int xLeft, int xRight, int yHigh, int yLow) {
	ExMessage m;
	m = getmessage(EX_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN:
		return (areaCheck(xLeft, xRight, yHigh, yLow, m.x, m.y));
		break;
	}
}
//initializeTheWindows
//����
//IMAGE image ����ͼƬ��������������imageΪ����ͼƬ���ϵ��µ������֣��ֱ���أ�
//���
//�½��ҳ�ʼ�����ڲ���ʾ����ͼƬ
void initializeTheWindows(IMAGE image) {
	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(LIGHTGRAY);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	putimage(0, 0, &image);
}
void initializeTheWindows(IMAGE image1, IMAGE image2 ,IMAGE image3) {
	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(LIGHTGRAY);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	putimage(0, 0, &image1);
	putimage(0, 200, &image2);
	putimage(0, 400, &image3);
}
//transparentImage
//������csdn,��ԭ����
//����
//IMAGE* dstimg �������룬����NULL����
//x,y ͼƬ�����Ͻ�����
//IMAGE* srcimg ͼƬ
//���
//����ָ��λ��͸������ͼƬ���ް�ɫ�߿�
void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
//backImage
//����
//image1(23)����ͼƬ��123Ϊ���ϵ��·ָ��˵�ԭ����ͼƬ��
//string money ��ҵ�ǰ�Ľ�Ǯ����
//(level_) ��ҵ�ǰѡ����Ѷ� ���������棩
void backImage(IMAGE image1, IMAGE image2, IMAGE image3, string money) {
	putimage(0, 0, &image1);
	putimage(0, 200, &image2);
	putimage(0, 400, &image3);
	outtextxy(690, 25, "BACK");
    outtextxy(65, 550, money.c_str());
}
void backImage(IMAGE image1, string money) {
    putimage(0, 0, &image1);
    outtextxy(690, 25, "BACK");
    outtextxy(100, 530, money.c_str());
}
void backImage(IMAGE image1, int level_, string money) {
    setlinestyle(PS_SOLID, 10);
    putimage(0, 0, &image1);
    outtextxy(30, 20, "��ʼս����");
    outtextxy(200, 540, "tips:��esc�浵���˳�,�����������ʧȥ��Ĵ浵(��ĺܾ�)!");
    outtextxy(65, 550, money.c_str());
    if (level_ == EASY) {
        rectangle(120, 115, 320, 315);
    }
    else {
        rectangle(475, 115, 677, 312);
    }
}
//randNum ��������ɺ���
//����
//��������ֵmaxNum,��СֵminNum
//����ֵ 
//������Χ�ڵȿ��ܵĸ���һ���������
int randNum(int maxNum, int minNum) {
	srand(clock());
	return (rand() % (maxNum - minNum)) + minNum;
}
//compare �ȽϺ�����
//����
//�������ַ�����ʽ������������
//����ֵ
//��ȷ���0�����ڷ���1��С�ڷ���-1
int compare(string str1, string str2)
{
    if (str1.length() > str2.length()) return 1;
    else if (str1.length() < str2.length())  return -1;
    else return str1.compare(str2);
}
//add �߾��ȼӷ�
//����
//�������ַ�����ʽ������������
//����ֵ
//���ַ�����ʽ�����ĺ�
string add(string str1, string str2)//�߾��ȼӷ�
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    //ǰ�油0��Ū�ɳ�����ͬ
    if (len1 < len2)
    {
        for (int i = 1; i <= len2 - len1; i++)
            str1 = "0" + str1;
    }
    else
    {
        for (int i = 1; i <= len1 - len2; i++)
            str2 = "0" + str2;
    }
    len1 = str1.length();
    int cf = 0;
    int temp;
    for (int i = len1 - 1; i >= 0; i--)
    {
        temp = str1[i] - '0' + str2[i] - '0' + cf;
        cf = temp / 10;
        temp %= 10;
        str = char(temp + '0') + str;
    }
    if (cf != 0)  str = char(cf + '0') + str;
    return str;
}
//sub �߾��ȼ���
//����
//�������ַ�����ʽ�������������ҵ�һ���ȵڶ�����
//����ֵ
//���ַ�����ʽ�����Ĳ�
string sub(string str1, string str2)
{
    string str;
    int tmp = str1.length() - str2.length();
    int cf = 0;
    for (int i = str2.length() - 1; i >= 0; i--)
    {
        if (str1[tmp + i] < str2[i] + cf)
        {
            str = char(str1[tmp + i] - str2[i] - cf + '0' + 10) + str;
            cf = 1;
        }
        else
        {
            str = char(str1[tmp + i] - str2[i] - cf + '0') + str;
            cf = 0;
        }
    }
    for (int i = tmp - 1; i >= 0; i--)
    {
        if (str1[i] - cf >= '0')
        {
            str = char(str1[i] - cf) + str;
            cf = 0;
        }
        else
        {
            str = char(str1[i] - cf + 10) + str;
            cf = 1;
        }
    }
    str.erase(0, str.find_first_not_of('0'));
    return str;
}
//mul �߾��ȳ˷�
//����
//�������ַ�����ʽ������������
//����ֵ
//���ַ�����ʽ�����Ļ�
string mul(string str1, string str2)
{
    string str;
    int len1 = str1.length();
    int len2 = str2.length();
    string tempstr;
    for (int i = len2 - 1; i >= 0; i--)
    {
        tempstr = "";
        int temp = str2[i] - '0';
        int t = 0;
        int cf = 0;
        if (temp != 0)
        {
            for (int j = 1; j <= len2 - 1 - i; j++)
                tempstr += "0";
            for (int j = len1 - 1; j >= 0; j--)
            {
                t = (temp * (str1[j] - '0') + cf) % 10;
                cf = (temp * (str1[j] - '0') + cf) / 10;
                tempstr = char(t + '0') + tempstr;
            }
            if (cf != 0) tempstr = char(cf + '0') + tempstr;
        }
        str = add(str, tempstr);
    }
    str.erase(0, str.find_first_not_of('0'));
    return str;
}
//div �߾��ȳ���
//����
//�������ҷֱ�Ϊ�����������������̡�����
void div(string str1, string str2, string& quotient, string& residue)
{
    quotient = residue = "";
    if (str2 == "0")
    {
        quotient = residue = "ERROR";
        return;
    }
    if (str1 == "0")
    {
        quotient = residue = "0";
        return;
    }
    int res = compare(str1, str2);
    if (res < 0)
    {
        quotient = "0";
        residue = str1;
        return;
    }
    else if (res == 0)
    {
        quotient = "1";
        residue = "0";
        return;
    }
    else
    {
        int len1 = str1.length();
        int len2 = str2.length();
        string tempstr;
        tempstr.append(str1, 0, len2 - 1);
        for (int i = len2 - 1; i < len1; i++)
        {
            tempstr = tempstr + str1[i];
            tempstr.erase(0, tempstr.find_first_not_of('0'));
            if (tempstr.empty())
                tempstr = "0";
            for (char ch = '9'; ch >= '0'; ch--)
            {
                string str, tmp;
                str = str + ch;
                tmp = mul(str2, str);
                if (compare(tmp, tempstr) <= 0)
                {
                    quotient = quotient + ch;
                    tempstr = sub(tempstr, tmp);
                    break;
                }
            }
        }
        residue = tempstr;
    }
    quotient.erase(0, quotient.find_first_not_of('0'));
    if (quotient.empty()) quotient = "0";
}
//chooseCoinKind ����Һ���
//����
//��ҵ�lucks����ֵ����
//���
//��������Ľ������
int chooseCoinKind(lucks luck) {
    int luckTotal;
    luckTotal = luck.silver + luck.gold + luck.diamond + luck.basic;
    int result;
    result = randNum(luckTotal, 1);
    if (result <= luck.basic) {
        result = GET_BASICAWARD;
    }
    else {
        if (result <= luck.basic + luck.silver) {
            result = GET_SILVER;
        }
        else {
            if (result <= luck.basic + luck.silver + luck.gold) {
                result = GET_GOLD;
            }
            else {
                result = GET_DIAMOND;
            }
        }
    }
    return result;
}
//sgn ���ź���
//����
//double x
//����ֵ
//����0����1��С��0����-1��"����0"���������Ϊ1e-6��ʱ����0
int sgn(double x) {
    if (x > 0) {
        return 1;
    }
    else {
        if (fabs(x) < 1e-6) {
            return 0;
        }
        else {
            return -1;
        }
    }
}