#include "structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
//�����д�浵����
void readSaveFile(const string& filename, map<string, string>& saveData, save& player);
void writeSaveFile(const string& filename, map<string, string>& saveData, save& player);
// ��ȡ�浵�ļ�����ֵ�洢��map��
void readSaveFile(const string& filename, map<string, string>& saveData,save& player) {
    // ��ֻ����ʽ���ļ�
    ifstream file(filename);
    // ����ļ��򿪳ɹ�
    if (file.is_open()) {
        string line;
        // ���ж�ȡ�ļ�����
        while (getline(file, line)) {
            // ���ҵȺŵ�λ��
            size_t pos = line.find('=');
            // ����ҵ��Ⱥ�
            if (pos != string::npos) {
                // ���Ⱥ������ַ�����Ϊ�����Ҳ���ַ�����Ϊֵ���洢��map��
                saveData[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
        // �ر��ļ�
        file.close();
        //����map�е�����
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
// ����Ϸ����д�ش浵�ļ�
void writeSaveFile(const string& filename, map<string, string>& saveData,save& player) {
    // ��д�뷽ʽ���ļ�
    ofstream file(filename);
    //����Ϸ����д��map��
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
    // ����ļ��򿪳ɹ�
    if (file.is_open()) {
        // ����map�е�����Ԫ��
        for (const auto& item : saveData) {
            // ������ֵд���ļ�
            const string& key = item.first;
            const string& value = item.second;
            file << key << "=" << value << endl;
        }
        // �ر��ļ�
        file.close();
    }
}
