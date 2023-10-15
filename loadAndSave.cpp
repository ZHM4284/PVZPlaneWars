#include "structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
//定义读写存档函数
void readSaveFile(const string& filename, map<string, string>& saveData, save& player);
void writeSaveFile(const string& filename, map<string, string>& saveData, save& player);
// 读取存档文件并将值存储在map中
void readSaveFile(const string& filename, map<string, string>& saveData,save& player) {
    // 以只读方式打开文件
    ifstream file(filename);
    // 如果文件打开成功
    if (file.is_open()) {
        string line;
        // 逐行读取文件内容
        while (getline(file, line)) {
            // 查找等号的位置
            size_t pos = line.find('=');
            // 如果找到等号
            if (pos != string::npos) {
                // 将等号左侧的字符串作为键，右侧的字符串作为值，存储在map中
                saveData[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
        // 关闭文件
        file.close();
        //导入map中的数据
        player.luck.gold = stoi(saveData["gold"]);
        player.luck.diamond = stoi(saveData["diamond"]);
        player.luck.cactus = stoi(saveData["cactus"]);
        player.price.moreCactus = saveData["moreCactus"];
        player.price.morePea = saveData["morePea"];
        player.money = saveData["money"];
        player.plantSpeed = stoi(saveData["plantSpeed"]);
        player.maxTimeBetweenCreateZombie = stoi(saveData["maxTimeBetweenCreateZombie"]);
        player.minTimeBetweenCreateZombie = stoi(saveData["minTimeBetweenCreateZombie"]);
        player.linesOfPea = stoi(saveData["linesOfPea"]);
        player.lostAfterDie = saveData["lostAfterDie"];
        player.luck.bigBoom = stoi(saveData["bigBoom"]);
    }
}
// 将游戏数据写回存档文件
void writeSaveFile(const string& filename, map<string, string>& saveData,save& player) {
    // 以写入方式打开文件
    ofstream file(filename);
    //将游戏数据写回map中
    saveData["gold"] = to_string(player.luck.gold);
    saveData["diamond"] = to_string(player.luck.diamond);
    saveData["cactus"] = to_string(player.luck.cactus);
    saveData["moreCactus"] = player.price.moreCactus;
    saveData["morePea"] = player.price.morePea;
    saveData["money"] = player.money;
    saveData["plantSpeed"] = to_string(player.plantSpeed);
    saveData["maxTimeBetweenCreateZombie"] = to_string(player.maxTimeBetweenCreateZombie);
    saveData["minTimeBetweenCreateZombie"] = to_string(player.minTimeBetweenCreateZombie);
    saveData["linesOfPea"] = to_string(player.linesOfPea);
    saveData["lostAfterDie"] = player.lostAfterDie;
    saveData["bigBoom"] = to_string(player.luck.bigBoom);
    // 如果文件打开成功
    if (file.is_open()) {
        // 遍历map中的所有元素
        for (const auto& item : saveData) {
            // 将键和值写入文件
            const string& key = item.first;
            const string& value = item.second;
            file << key << "=" << value << endl;
        }
        // 关闭文件
        file.close();
    }
}
