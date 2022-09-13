#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controllerのぽいんた
	data_controller* data;

	//変数
	//int productNum;
	std::string chrom[128];
	int point;//評価点
	int points[crossNum];//交差点を保存する場所


	//関数
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
	int decideNoteNum(int lower, int upper);//lower以上upper以下(以下！)の乱数を出すだけなので使いまわしはきくかも
	void cross(Individual* p1, Individual* p2);
	void sort(int lb, int ub);
	void printResult();
	void printMusic(int Num);
	void print(std::string fileName);

	void printChrom();
private:
	int seekTP(std::string tmpS, int num);//名前はseekTPだけど、TPではないchromの添え字を返す関数
	int defNoteNum(std::string tmpS, int num);//対象のC4等の要素を数値に変換する 引数：変換したい文字、その文字の添え字(chrom上)

	void printMelody(std::string fileName, int i, int j, std::ofstream& fout);
	void printAccom(std::string fileName, int i, std::ofstream& fout);
};