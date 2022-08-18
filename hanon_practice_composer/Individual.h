#pragma once
#include "data_controller.h"


class Individual {
public:
	//data_controller‚Ì‚Û‚¢‚ñ‚½
	data_controller* data;

	//•Ï”
	int productNum;
	std::string chrom[128];


	//ŠÖ”
	Individual(data_controller* d);
	~Individual();
	void firstTake(int selectNum);
private:
	int point;
};