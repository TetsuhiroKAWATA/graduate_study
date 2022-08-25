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
};