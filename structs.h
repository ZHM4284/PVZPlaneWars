//ͷ�ļ�structs.h
//�����������ڶ��ļ���ʹ�õĽṹ��
//ע�⣺���ݺ��С�//���ı�ʾ��Ϊ��������"save"�浵�ļ��ı���
#pragma once
#ifndef  structs
#define   structs
#include <iostream>      
#include <string.h>
#include <string>
using namespace std;
//lucks�ṹ��
//�������������ǩʱ�ĸ���Ȩ��
//silver gold diamond Ӱ����Ǳ���ҵ�����
//cactus pea Ӱ�����������ӵ�����
//bigBoom boom Ӱ����Ƿ��õ�ը������
struct lucks {
    int silver = 500;
    int gold = 200;//
    int diamond = 100;//
    int basic = 1000;
    int cactus = 0;//
    int pea = 1000;//
    int bigBoom = 200;//
    int boom = 1000;
};
//prices�ṹ��
//�������̵����Ʒ�۸�
struct prices {
    string luckyBox = "4284";
    string coffeeBean = "2195";
    string morePea = "8888";//
    string moreCactus = "6666";//
    string moreLuck = "2333";
};
//save�ṹ��
//�����˴浵�Ļ�����Ϣ
struct save {
    string money="0";///*���Ǯ�ܶ�*/
    lucks luck;
    int plantSpeed = 30;///*����ֲ����˶��ٶȣ�ָÿһ֡��������ƶ�������*/
    int timeBetweenShoot = 500;/*������������*/
    int maxTimeBetweenCreateZombie = 10000;///*���ʬ���ɼ��������*/
    int minTimeBetweenCreateZombie = 500;///*��̽�ʬ���ɼ��������*/
    int zombieSpeed = 2;/*���ƽ�ʬ���˶��ٶȣ�ָÿһ֡��������ƶ������أ�ֻ����ż��*/
    int peaSpeed = 20;/*�ӵ��ķ����ٶ�*/
    int peaDamage = 10;/*�㶹���˺�*/
    int linesOfPea = 1;///*ͬʱ������㶹����*/
    string lostAfterDie = "4";///*����ʱ��Ǯ�ͷ�ϵ��*/
    prices price;
};
#endif


