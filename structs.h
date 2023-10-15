//头文件structs.h
//定义了若干在多文件中使用的结构体
//注意：数据后有“//”的表示其为被保存在"save"存档文件的变量
#pragma once
#ifndef  structs
#define   structs
#include <iostream>      
#include <string.h>
#include <string>
using namespace std;
//lucks结构体
//包含了在随机抽签时的概率权重
//silver gold diamond 影响的是爆金币的种类
//cactus pea 影响的是射出的子弹种类
//bigBoom boom 影响的是放置的炸弹种类
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
//prices结构体
//包含了商店的物品价格
struct prices {
    string luckyBox = "4284";
    string coffeeBean = "2195";
    string morePea = "8888";//
    string moreCactus = "6666";//
    string moreLuck = "2333";
};
//save结构体
//包含了存档的基本信息
struct save {
    string money="0";///*玩家钱总额*/
    lucks luck;
    int plantSpeed = 30;///*控制植物的运动速度，指每一帧画面最多移动的像素*/
    int timeBetweenShoot = 500;/*射击间隔毫秒数*/
    int maxTimeBetweenCreateZombie = 10000;///*最长僵尸生成间隔毫秒数*/
    int minTimeBetweenCreateZombie = 500;///*最短僵尸生成间隔毫秒数*/
    int zombieSpeed = 2;/*控制僵尸的运动速度，指每一帧画面最多移动的像素，只能是偶数*/
    int peaSpeed = 20;/*子弹的飞行速度*/
    int peaDamage = 10;/*豌豆的伤害*/
    int linesOfPea = 1;///*同时射出的豌豆个数*/
    string lostAfterDie = "4";///*死亡时扣钱惩罚系数*/
    prices price;
};
#endif


