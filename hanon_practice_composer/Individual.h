#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controllerのぽいんた
	data_controller* data;

	//変数
	int productNum;
	std::string chrom[128];


	//関数
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
private:
	int point;
};