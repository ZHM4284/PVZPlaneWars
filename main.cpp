#include "structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
//�õ��Ĵ浵����
map<string, string> saveData;
//�õ��ĺ���
void readSaveFile(const string& filename, map<string, string>& saveData, save& player);
void writeSaveFile(const string& filename, map<string, string>& saveData, save& player);
void startGame();
void home(save& player);
//������
int main() {
	save player;/*����浵*/
	readSaveFile("save.txt", saveData, player);/*��ȡ�浵*/
	startGame();/*��ʼ����*/
	home(player);/*������*/
	writeSaveFile("save.txt", saveData, player);/*����浵*/
	return 0;
}