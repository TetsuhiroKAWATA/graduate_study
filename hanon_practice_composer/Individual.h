#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controllerのぽいんた
	data_controller* data;

	//変数
	int productNum;
	std::string chrom[128];
	int point;


	//関数
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
	int decideNoteNum(int lower, int upper);//lower以上upper以下(以下！)の乱数を出すだけなので使いまわしはきくかも
private:
	int seekTP(std::string tmpS, int num);//名前はseekTPだけど、TPではないchromの添え字を返す関数
	int defNoteNum(std::string tmpS, int num);//対象のC4等の要素を数値に変換する 引数：変換したい文字、その文字の添え字(chrom上)
};