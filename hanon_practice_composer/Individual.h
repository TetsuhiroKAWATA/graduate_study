#pragma once
#include "data_controller.h"


class Individual {
public:
	//•Ï”
	int productNum;
	std::string chrom[128];


	//ŠÖ”
	Individual();
	~Individual();
	void firstTake(int selectNum);
private:
	int point;
};