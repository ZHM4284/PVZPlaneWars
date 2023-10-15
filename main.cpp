#include "structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
//用到的存档数据
map<string, string> saveData;
//用到的函数
void readSaveFile(const string& filename, map<string, string>& saveData, save& player);
void writeSaveFile(const string& filename, map<string, string>& saveData, save& player);
void startGame();
void home(save& player);
//主函数
int main() {
	save player;/*定义存档*/
	readSaveFile("save.txt", saveData, player);/*读取存档*/
	startGame();/*开始界面*/
	home(player);/*主界面*/
	writeSaveFile("save.txt", saveData, player);/*保存存档*/
	return 0;
}